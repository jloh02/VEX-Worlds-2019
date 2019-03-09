#include "main.h"
#include "mech_lib.hpp"

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

#define liftScorePosition 250
#define liftUpPosition 30
#define liftDownPosition 0
#define liftPushPosition 100

#define poleAlignPower 50
#define backOutPower 50
#define backOutTime 200
#define lowerLiftDelay 200

void opcontrol() {
  Motor FL (FLport);
  Motor BL (BLport);
  Motor FR (FRport);
  Motor BR (BRport);
  Motor intake(intakePort);

  Controller master(E_CONTROLLER_MASTER);

  ADIAnalogIn cataPot(1);
  master.clear();

  Task cataControl(catapultControl);

  int liftState = 0;
  int targetIntakeSpd = 0;
  int intakeSpd = 0;

	while (true) {
    //master.print(2, 0, "Auton: %2d", autonNum);
    //master.print(2, 0, "Pot: %4d", cataPot.get_value());
    //master.print(2, 0, "Pow: %7d", catapult.get_power());

		int left = master.get_analog(ANALOG_LEFT_Y);
		int right = master.get_analog(ANALOG_RIGHT_Y);

    if(master.get_digital(DIGITAL_B) == 1) clearScreen();

    //master.print(2,0,"%3f",liftL.get_position());
    /*
    if(master.get_digital_new_press(DIGITAL_A) == 1) {
      liftL.move_absolute(liftScorePosition, 200);
      liftR.move_absolute(liftScorePosition, 200);
      while(fabs(liftScorePosition - liftL.get_position()) > 5){
        master.print(2,0,"%3f",liftL.get_position());
        FL.move(poleAlignPower);
    		BL.move(poleAlignPower);
    		FR.move(poleAlignPower);
    		BR.move(poleAlignPower);
      }
      int startBackOut = millis();
      while(millis() - startBackOut < backOutTime){
        master.print(2,0,"%3f",liftL.get_position());
        if(millis() - startBackOut >= lowerLiftDelay){
          liftL.move_absolute(liftDownPosition, 200);
          liftR.move_absolute(liftDownPosition, 200);
        }
        FL.move(-backOutPower);
    		BL.move(-backOutPower);
    		FR.move(-backOutPower);
    		BR.move(-backOutPower);
      }
      liftState = 0;
    }*/

    if(master.get_digital_new_press(DIGITAL_L1) == 1) catapultActivated = true;
    if(master.get_digital_new_press(DIGITAL_L2) == 1) liftState = liftState==0?1:0;
    if(master.get_digital_new_press(DIGITAL_B) == 1) liftState = liftState==2?0:2;


    /*if(liftState == 1){
      liftL.move_absolute(liftUpPosition, 10);
      liftR.move_absolute(liftUpPosition, 10);
    }
    else if(liftState == 2){
      liftL.move_absolute(liftPushPosition, 80);
      liftR.move_absolute(liftPushPosition, 80);
    }
    else {
      liftL.move_absolute(liftDownPosition, 50);
      liftR.move_absolute(liftDownPosition, 50);
    }*/
    //liftL.move((master.get_digital(DIGITAL_UP)-master.get_digital(DIGITAL_DOWN))*127);

    targetIntakeSpd = (master.get_digital(DIGITAL_R1)-master.get_digital(DIGITAL_R2))*127;
    int diff = targetIntakeSpd - intakeSpd;
    if(abs(diff) > 3)intakeSpd += diff>0?3:-3;
    else intakeSpd = targetIntakeSpd;

    intake.move(intakeSpd);

		FL.move(left);
		BL.move(left);
		FR.move(right);
		BR.move(right);

		delay(5);
	}
}
