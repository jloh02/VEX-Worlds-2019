#include "main.h"
#include "mech_lib.hpp"

//Inertia after power: ____

int intakeVelTarget = 0;
int liftTarget = 0;

#define catapultReadyAngle 1625
#define catapultShootAngle 2500

#define liftP 0.7
#define liftD 0.4

#define intakeP 0.5

/*
Motor liftL (liftLPort);
Motor liftR (liftRPort);
Motor intake(intakePort);
*/
void catapultControl(void * ignore){
	Controller master(E_CONTROLLER_MASTER);
	Motor catapultL(catapultLPort);
	Motor catapultR(catapultRPort);
	ADIAnalogIn cataPot(catapultPotPort);
	//double kP = 0.4;
	while(true){
		if(master.get_digital(DIGITAL_Y) == 1) catapultL.move(-70), catapultR.move(-70);
		else if(cataPot.get_value() > catapultReadyAngle){
			master.print(2, 0, "%4d Readying...", cataPot.get_value());
			catapultL.move(100);
			catapultR.move(100);
			catapultReady = false;
		}
		else {
			catapultReady = true;
			master.print(2, 0, "%4d Ready Set Go", cataPot.get_value());
			if(catapultActivated){
        while(cataPot.get_value() < catapultReadyAngle) {
					master.print(2, 0, "%4d Firing...", cataPot.get_value());
					catapultL.move(70);
					catapultR.move(70);
          delay(25);
        }
        while(cataPot.get_value() < catapultShootAngle) {
					master.print(2, 0, "%4d Waiting...", cataPot.get_value());
          catapultL.move_relative(0,100);
					catapultR.move_relative(0,100);
          delay(25);
        }
				delay(150);
  			catapultActivated = false;
			}
			else{
				//4(80%?)-7(55)
				catapultL.move(0);
				catapultR.move(0);
				//catapultL.move_relative(0,100);
				//catapultL.move_relative(0,100);
			}
		}
		delay(25);
	}
}

void liftControl(void * ignore){
	Motor liftL (liftLPort);
  Motor liftR (liftRPort);
	int oldErr = 0;

  liftL.tare_position();
  liftR.tare_position();

	while(true){
		int error = liftTarget - liftL.get_position();
		int power = error*liftP + (error-oldErr)*liftD;
		oldErr = error;

		liftL.move(power);
		liftR.move(power);

		delay(25);
	}
}

void intakeControl(void * ignore){
	Motor intake (intakePort);
	int intakePower = 0;
	while(true){
		double vel = intake.get_actual_velocity();
		intakePower += (vel-intakeVelTarget)*intakeP;
		intake.move(intakePower);
	}
}

void setIntake(int dir){
	if(dir == 1){
		intakeVelTarget = 600;
	}
	else if(dir == 2 || dir == -1){
		intakeVelTarget = -100;
	}
	else if(dir == 0){
		intakeVelTarget = 0;
	}
}

void setLift(int height){
	liftTarget = height;
}
