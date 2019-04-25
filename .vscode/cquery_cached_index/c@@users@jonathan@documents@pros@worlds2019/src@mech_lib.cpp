#include "main.h"
#include "mech_lib.hpp"

//int numBall = 0;
//int intakeBallTarget = 0;
int liftTarget = 0;
double pusherTarget = 0;
bool pusherPause = false;
bool pusherClimb = false;
bool liftPause = false;

#define catapultReadyAngle 1500
#define catapultShootAngle 2450
#define minFireTime 1000

#define liftP 1.0
#define liftD 0.0
#define pushP 2.3
#define pushD 0.2


/*
Motor liftL (liftLPort);
Motor liftR (liftRPort);
Motor intake(intakePort);
*/
void catapultControl(void * ignore){
	Controller master(E_CONTROLLER_MASTER);
	Motor catapult(catapultPort);
	//Motor catapultR(catapultRPort);
	ADIAnalogIn cataPot(catapultPotPort);
	//double kP = 0.4;
	while(true){
		//if(master.get_digital(DIGITAL_Y) == 1) catapult.move(-70);//, catapultR.move(-70);
		/*else*/
	 //printf("%d\n",cataPot.get_value());
		if(cataPot.get_value()==0) catapult.move(0);
		else if(cataPot.get_value() > catapultReadyAngle && !catapultReady){
			master.print(2, 0, "%4d Readying...", cataPot.get_value());
			catapult.move(100);
			//catapultR.move(100);
		}
		else {
			catapultReady = true;
			//master.print(2, 0, "%4d Ready Set Go", cataPot.get_value());
			if(catapultActivated){
				//printf("YEEEEEEEEEEEEEEEEEEET\n");
				double startFire = millis();
        while(cataPot.get_value() < catapultReadyAngle || millis()-startFire < minFireTime) {
					//master.print(2, 0, "%4d Firing...", cataPot.get_value());
					catapult.move(100);
					//catapultR.move(70);
          delay(25);
        }
				catapultReady = false;
        /*while(cataPot.get_value() < catapultShootAngle) {
					//master.print(2, 0, "%4d Waiting...", cataPot.get_value());
          catapult.move_relative(0,100);
					//catapultR.move_relative(0,100);
          delay(25);
        }
				delay(150);*/
  			catapultActivated = false;
			}
			else{
				catapult.move(0);
				//catapultR.move(0);
				//catapultL.move_relative(0,100);
				//catapultL.move_relative(0,100);
			}
		}
		delay(25);
	}
}

void liftControl(void * ignore){
	Controller master(E_CONTROLLER_MASTER);
	Motor lift (liftPort);
	int oldErr = 0;

	while(true){
		int error = liftTarget - lift.get_position();
		int power = error*liftP + (error-oldErr)*liftD;
		oldErr = error;

		if(abs(error) < 2 || liftPause) lift.move(0);
	else if (master.get_digital(DIGITAL_UP) )lift.move(50);
	else if (master.get_digital(DIGITAL_DOWN)) lift.move(-50);

		else lift.move(power);

		delay(25);
	}
}
void setLift(int height){
	liftTarget = height;
}

void pauseLift(bool pause){
	liftPause = pause;
}

int getLift(){
	return liftTarget;
}

void pusherControl(void * ignore){
	Motor pusher (pusherPort);
	int oldErr = 0;

	while(true){
		double error = pusherTarget - pusher.get_position();
		double power = error*pushP + (error-oldErr)*pushD;
		oldErr = error;

		if(pusherClimb) pusher.move((-680 - pusher.get_position())*20.0);
		else if(!pusherPause) pusher.move(power);
		else pusher.move(0);

		delay(25);
	}
}

void setPusher(double height){
	pusherTarget = -height;
}

void pausePusher(bool pause){
	pusherPause = pause;
}

void setClimb(bool climbing){
	pusherClimb = climbing;
}
