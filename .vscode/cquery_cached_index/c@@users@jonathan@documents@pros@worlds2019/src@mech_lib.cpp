#include "main.h"
#include "mech_lib.hpp"

//Inertia after power: ____

double intakeVelTarget = 0;
int liftTarget = 0;

#define catapultReadyAngle 1600
#define catapultShootAngle 2450

#define liftP 2.5
#define liftD 0.7

#define intakeP 0.35

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
		if(master.get_digital(DIGITAL_Y) == 1) catapult.move(-70);//, catapultR.move(-70);
		else if(cataPot.get_value() > catapultReadyAngle){
			//master.print(2, 0, "%4d Readying...", cataPot.get_value());
			catapult.move(100);
			//catapultR.move(100);
			catapultReady = false;
		}
		else {
			catapultReady = true;
			//master.print(2, 0, "%4d Ready Set Go", cataPot.get_value());
			if(catapultActivated){
        while(cataPot.get_value() < catapultReadyAngle) {
					//master.print(2, 0, "%4d Firing...", cataPot.get_value());
					catapult.move(100);
					//catapultR.move(70);
          delay(25);
        }
        while(cataPot.get_value() < catapultShootAngle) {
					//master.print(2, 0, "%4d Waiting...", cataPot.get_value());
          catapult.move_relative(0,100);
					//catapultR.move_relative(0,100);
          delay(25);
        }
				delay(150);
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
	Motor lift (liftPort);

	int oldErr = 0;

  lift.tare_position();

	while(true){
		int error = liftTarget - lift.get_position();
		int power = error*liftP + (error-oldErr)*liftD;
		oldErr = error;

		lift.move(power);

		delay(25);
	}
}
/*
void intakeControl(void * ignore){
	Motor intake (intakePort);
	intake.tare_position();
	double intakePower = 0;
	double prevPos = 0;
	while(true){
		double pos = intake.get_position();
		double vel = (pos-prevPos)/360/50*1000*60;
		prevPos = pos;
		intakePower += (intakeVelTarget-vel)*intakeP;

		if(intakePower > 127) intakePower = 127;
		else if(intakePower < -127) intakePower = -127;

		intake.move(intakePower);

		//printf("Targ Velocity %f, ",intakeVelTarget);
		//printf("Velocity %f, ",vel);
		//printf("Power %f\n",intakePower);

		Task::delay(50);
	}
}*/

void setLift(int height){
	liftTarget = height;
}

int getLift(){
	return liftTarget;
}
