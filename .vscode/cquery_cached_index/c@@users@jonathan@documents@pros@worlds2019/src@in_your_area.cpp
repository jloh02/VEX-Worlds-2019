#include "main.h"
#include "base_lib.hpp"

Motor FL (FLport);
Motor BL (BLport);
Motor FR (FRport);
Motor BR (BRport);

/*-----------------------------------------USER INPUT-----------------------------------------*/
#define baseRPM 200									//Enter RPM of base motors
#define UNLIMITED_POWER 100         //Enter maximum power of base motors
#define rampingPow 15               //Increase in power / 25 millis

#define PI      3.141592653589793238462643383279			//CONST PI VALUE
#define halfPI  1.570796326794896619231321691639 			//CONST PI/2 VALUE
#define twoPI	  6.283185307179586476925286766559			//CONST 2*PI VALUE

#define DISTANCE_LEEWAY   5.0				//Enter Distance Leeway in Degrees

#define baseWidth 7.000 						//Enter distance in inches between side encoders
#define inPerDeg 0.02881944444444		//Determine empirically using at least 1 rotation
/*--------------------------------------------------------------------------------------------*/

typedef struct{
	double x,y,angle;
} Coordinates;

Coordinates position;

double targetL=0,targetR=0;
double kP=0,kI=0,kD=0;
double lastResetAngle=0; //IN RADIANS

double encdL=0,encdR=0;

double motorTargetL=0,motorTargetR=0;

void baseOdometry(void * ignore){
  FL.tare_position();
	FR.tare_position();
	BL.tare_position();
	BR.tare_position();

  double prevEncdL = 0;
	double prevEncdR = 0;
	double prevAngle = 0;
	while(true){
    encdL = FL.get_position();
    encdR = FR.get_position();
		double encdChangeL = (encdL - prevEncdL)*inPerDeg;
		double encdChangeR = (encdR - prevEncdR)*inPerDeg;
		position.angle = lastResetAngle + (encdL - encdR)*inPerDeg/baseWidth; //Theta = (s2-s1)/width
		double deltaAngle = position.angle - prevAngle;
		double sumEncdChange = encdChangeL+encdChangeR;

		if(deltaAngle == 0) //Cannot divide by 0
		{
			position.x += sumEncdChange/2*sin(position.angle);            	//Simple trigo
			position.y += sumEncdChange/2*cos(position.angle);
		}
		else                //Refer to formulas
		{
			double halfDeltaAngle = deltaAngle/2;
			double strDist = (sumEncdChange/deltaAngle)*sin(halfDeltaAngle);
			position.x += strDist * sin(prevAngle+halfDeltaAngle);
			position.y += strDist * cos(prevAngle+halfDeltaAngle);
		}

		prevEncdL = encdL;
		prevEncdR = encdR;
		prevAngle = position.angle;

    Task::delay(5);
	}
}

void base_power(double l, double r){
  FL.move(l);
	BL.move(l);
	FR.move(r);
	BR.move(r);
}

void baseMotorControl(void * ignore){
  double powerL=0,powerR=0;
  while(true){
    double diffL = motorTargetL - powerL;
    if(fabs(diffL) > rampingPow) powerL += diffL>0?rampingPow:-rampingPow;
    else powerL = motorTargetL;

    double diffR = motorTargetR - powerR;
    if(fabs(diffR) > rampingPow) powerR += diffR>0?rampingPow:-rampingPow;
    else powerR = motorTargetL;

    if(powerL > UNLIMITED_POWER) powerL = UNLIMITED_POWER;
    else if(powerL < -UNLIMITED_POWER) powerL = -UNLIMITED_POWER;
    if(powerR > UNLIMITED_POWER) powerR = UNLIMITED_POWER;
    else if(powerR < -UNLIMITED_POWER) powerR = -UNLIMITED_POWER;

    base_power(powerL,powerR);

    Task::delay(25);
  }
}

void baseControl(void * ignore){
  double prevErrorL = 0, prevErrorR = 0;
  while(true){
    double errorL = targetL - encdL;
    double errorR = targetR - encdR;

    double deltaErrorL = errorL - prevErrorL;
    double deltaErrorR = errorR - prevErrorR;

    prevErrorL = errorL;
    prevErrorR = errorR;

    motorTargetL = kP*errorL+kD*deltaErrorL;
    motorTargetR = kP*errorR+kD*deltaErrorR;

    Task::delay(25);
  }
}

bool baseFinished(){
	return(fabs(FL.get_target_position()-FL.get_position())<DISTANCE_LEEWAY && fabs(FR.get_target_position()-FR.get_position())<DISTANCE_LEEWAY);
}

void baseMove(double dis){
  motorTargetL += dis;
  motorTargetR += dis;

  kP = 0.8;
  kD = 0.4;
}

void baseMove(double dis, double p, double d){
  motorTargetL += dis;
  motorTargetR += dis;

  kP = p;
  kD = d;
}

void baseMove(double x, double y){
	double distance = sqrt((y-position.y)*(y-position.y) + (x-position.x)*(x-position.x));
  motorTargetL += distance;
  motorTargetR += distance;

  kP = 0.8;
  kD = 0.4;
}

void baseMove(double x, double y, double p, double d){
	double distance = sqrt((y-position.y)*(y-position.y) + (x-position.x)*(x-position.x));
  motorTargetL += distance;
  motorTargetR += distance;

  kP = p;
  kD = d;
}

void baseTurn(double angle){
  double diff = (angle/PI*180 - position.angle + lastResetAngle)*baseWidth/inPerDeg/2;
  motorTargetL += diff;
  motorTargetR += -diff;
}

void baseTurn(double angle, double p, double d){
  double diff = (angle/PI*180 - position.angle + lastResetAngle)*baseWidth/inPerDeg/2;
  motorTargetL += diff;
  motorTargetR += -diff;

  kP = p;
  kD = d;
}

void baseTurn(double x, double y){
  double targAngle = atan((x-position.x)/(y-position.y));
  double diff = (targAngle - position.angle + lastResetAngle)*baseWidth/inPerDeg/2;
  motorTargetL += diff;
  motorTargetR += -diff;
}

void baseTurn(double x, double y, double p, double d){
  double targAngle = atan((x-position.x)/(y-position.y));
  double diff = (targAngle - position.angle + lastResetAngle)*baseWidth/inPerDeg/2;
  motorTargetL += diff;
  motorTargetR += -diff;

  kP = p;
  kD = d;
}

void resetCoord(double x, double y, double angleInDeg){
	position.x = x;
	position.y = y;
	position.angle = angleInDeg/180*PI;
	lastResetAngle = position.angle;

	FL.tare_position();
	FR.tare_position();
	BL.tare_position();
	BR.tare_position();
}
