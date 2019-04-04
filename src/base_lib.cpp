#include "main.h"
#include "base_lib.hpp"

Motor FL (FLport);
Motor BL (BLport);
Motor FR (FRport);
Motor BR (BRport);

#define COMPETITION_MODE true //Set to false to test odometry during driver

/*-----------------------------------------USER INPUT-----------------------------------------*/
#define baseRPM 200									//Enter RPM of base motors
#define UNLIMITED_POWER 100         //Enter maximum power of base motors
#define rampingPow 7              	//Increase in power / 25 millis

#define autoStraightP 0.5
#define autoStraightD 0.7

#define PI      3.141592653589793238462643383279			//CONST PI VALUE
#define halfPI  1.570796326794896619231321691639 			//CONST PI/2 VALUE
#define twoPI	  6.283185307179586476925286766559			//CONST 2*PI VALUE

#define DISTANCE_LEEWAY   3.0				//Enter Distance Leeway in Degrees

#define baseWidth 12.52198690477777	//Enter distance in inches between side encoders
#define inPerDeg 0.0354472057977424 //Determine empirically using at least 1 rotation
/*--------------------------------------------------------------------------------------------*/

typedef struct{
	double x,y,angle;
} Coordinates;

Coordinates position;

double targetL=0,targetR=0,targetAngle=0;
double kP=0,kI=0,kD=0,angleP=0,angleD=0;
double lastResetAngle=0; //IN RADIANS

double encdL=0,encdR=0;

double motorTargetL=0,motorTargetR=0;

void baseOdometry(void * ignore){
	Controller master(E_CONTROLLER_MASTER);

  FL.tare_position();
	FR.tare_position();
	BL.tare_position();
	BR.tare_position();

  double prevEncdL = 0;
	double prevEncdR = 0;
	double prevAngle = 0;
	int count = 0;
	while(!COMPETITION_MODE || competition::is_autonomous()){
    encdL = BL.get_position();
    encdR = BR.get_position();
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

		//master.print(2,0,"%2.1f %2.1f %3f",position.x,position.y,position.angle/PI*180.0);
		//if(count++ % 10 == 0) printf("%2.1f \t %2.1f \t %3f\n",position.x,position.y,position.angle/PI*180.0);

    Task::delay(5);
	}
}

void baseMotorControl(void * ignore){
  double powerL=0,powerR=0;
	//printf("Left \t Right\n");
  while(competition::is_autonomous()){
    double diffL = motorTargetL - powerL;
    if(fabs(diffL) > rampingPow) powerL += diffL>0?rampingPow:-rampingPow;
    else powerL = motorTargetL;

    double diffR = motorTargetR - powerR;
    if(fabs(diffR) > rampingPow) powerR += diffR>0?rampingPow:-rampingPow;
    else powerR = motorTargetR;

    if(powerL > UNLIMITED_POWER) powerL = UNLIMITED_POWER;
    else if(powerL < -UNLIMITED_POWER) powerL = -UNLIMITED_POWER;
    if(powerR > UNLIMITED_POWER) powerR = UNLIMITED_POWER;
    else if(powerR < -UNLIMITED_POWER) powerR = -UNLIMITED_POWER;

		FL.move(powerL);
		BL.move(powerL);
		FR.move(powerR);
		BR.move(powerR);

		//printf("%4.0f \t %4.0f\n",powerL,powerR);

    Task::delay(25);
  }
}

void baseControl(void * ignore){
  double prevErrorL = 0, prevErrorR = 0, prevErrorAngle = 0;
	int count = 0;
  while(competition::is_autonomous()){
		double leftPos = BL.get_position();
		double rightPos = BR.get_position();

		double errorL = targetL - leftPos;
    double errorR = targetR - rightPos;

    double deltaErrorL = errorL - prevErrorL;
    double deltaErrorR = errorR - prevErrorR;

    prevErrorL = errorL;
    prevErrorR = errorR;

    motorTargetL = kP*errorL+kD*deltaErrorL;
    motorTargetR = kP*errorR+kD*deltaErrorR;

		double angleDiffErr = targetAngle-position.angle;
		if(angleDiffErr > PI) angleDiffErr -= PI;
		else if(angleDiffErr < -PI) angleDiffErr += PI;

		motorTargetL += angleP*angleDiffErr+angleD*(angleDiffErr-prevErrorAngle);
		motorTargetR -= angleP*angleDiffErr+angleD*(angleDiffErr-prevErrorAngle);

		prevErrorAngle = angleDiffErr;

		//printf("Motor controlling %f",motorTargetL);
		if(count++ % 3 == 0) printf("%f\t%f\n",errorL,errorR);

    Task::delay(25);
  }
}

void waitBase(double cutoff){
	double start = millis();
	while(fabs(targetL-BL.get_position())>DISTANCE_LEEWAY && fabs(targetR-BR.get_position())>DISTANCE_LEEWAY && millis()-start < cutoff){
		//printf("TL:%3f, FL:%3f, TR:%3f, FR:%3f\n",targetL,FL.get_position(),targetR,FR.get_position());
		//printf("~\t  \t%4.0f \t %4.0f\n",targetL-FL.get_position(),targetR-FR.get_position());
		delay(25);
	}
	FL.move_relative(0, 100);
	BL.move_relative(0, 100);
	FR.move_relative(0, 100);
	BR.move_relative(0, 100);
}

void baseMove(double dis, double p, double d){
  targetR += dis/inPerDeg;
	targetL += dis/inPerDeg;
	targetAngle = position.angle;

	angleP = autoStraightP;
	angleD = autoStraightD;

  kP = p;
  kD = d;
}

void baseMove(double dis){
  baseMove(dis,0.40,1.4);
}

void baseMove(double x, double y, double p, double d){
	double errY = y-position.y;
	double errX = x-position.x;
	double distance = sqrt(errY*errY + errX*errX);
	double targAngle = atan2(errX,errY);

	int negator = 1;
  if(fabs(targAngle-position.angle) >= PI/2) negator = -1;

	targetAngle = position.angle;
	angleP = autoStraightP;
	angleD = autoStraightD;

  targetL += distance/inPerDeg*negator;
  targetR += distance/inPerDeg*negator;

  kP = p;
  kD = d;
}

void baseMove(double x, double y){
	baseMove(x,y,0.5,1.3);
}

void baseTurn(double angle, double p, double d){
	double targetAngle = angle;
	angleP = p;
	angleD = d;
}

void baseTurn(double angle){
  baseTurn(angle, 0.4, 0.0);
}

void baseTurnRelative(double angle, double p, double d){
  targetAngle = position.angle + angle;
	angleP = p;
	angleD = d;
}

void baseTurnRelative(double angle){
  baseTurnRelative(angle, 0.7, 0.3);
}

void baseTurn(double x, double y, double p, double d){
	targetAngle = atan2((x-position.x),(y-position.y));
	angleP = p;
	angleD = d;
}

void baseTurn(double x, double y, double p, double d, bool inverted){
	targetAngle = atan2((x-position.x),(y-position.y));
	if(inverted) targetAngle *= -1;
	angleP = p;
	angleD = d;
}

void baseTurn(double x, double y){
  baseTurn(x,y,0.7,0.3);
}

void baseTurn(double x, double y, bool inverted){
  baseTurn(x,y,0.7,0.3,inverted);
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

	targetL = 0;
	targetR = 0;
	targetAngle = 0;
}
