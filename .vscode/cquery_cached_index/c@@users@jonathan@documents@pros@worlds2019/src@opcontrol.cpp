#include "main.h"
#include "mech_lib.hpp"
#include "base_lib.hpp"

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

#define liftScorePosition 570
#define liftUpPosition 60
#define liftDownPosition 0
#define liftPushPosition 100

#define poleAlignPower 50
#define lowerLiftDelay 200
#define backOutTime 300
#define backOutPower 100

#define pushInTime 300
#define pushInPower 80
#define backOutTime2 300
#define backOutDelay 300
#define backOutPower2 80

void opcontrol() {
  Motor FL (FLport);
  Motor BL (BLport);
  Motor FR (FRport);
  Motor BR (BRport);
  Motor intake(intakePort);
  Motor lift(liftPort);

  Controller master(E_CONTROLLER_MASTER);

  ADIAnalogIn cataPot(1);
  master.clear();

  Task lifControl(liftControl);
  Task cataControl(catapultControl);
  Task basOdom(baseOdometry);

  int targetIntakeSpd = 0;
  int intakeSpd = 0;

  setLift(liftDownPosition);

	while (true) {
    //master.print(2, 0, "Auton: %2d", autonNum);
    //master.print(2, 0, "Pot: %4d", cataPot.get_value());
    //master.print(2, 0, "Pow: %7d", catapult.get_power());

		int left = master.get_analog(ANALOG_LEFT_Y);
		int right = master.get_analog(ANALOG_RIGHT_Y);

    if(master.get_digital(DIGITAL_B) == 1) clearScreen();

    if(master.get_digital_new_press(DIGITAL_L2) == 1) catapultActivated = true;

    if(master.get_digital_new_press(DIGITAL_L1) == 1) {
      if(getLift()==liftDownPosition) setLift(liftUpPosition);
      else setLift(liftDownPosition);
    }
    if(master.get_digital_new_press(DIGITAL_A) == 1) {
      setLift(liftScorePosition);
      while(fabs(liftScorePosition - lift.get_position()) > 5){
        master.print(2,0,"%3f",lift.get_position());
        FL.move(poleAlignPower);
        BL.move(poleAlignPower);
        FR.move(poleAlignPower);
        BR.move(poleAlignPower);
      }
      int startBackOut = millis();
      while(millis() - startBackOut < backOutTime){
        master.print(2,0,"%3f",lift.get_position());
        if(millis() - startBackOut >= lowerLiftDelay){
          setLift(0);
        }
        FL.move(-backOutPower);
        BL.move(-backOutPower);
        FR.move(-backOutPower);
        BR.move(-backOutPower);
      }
      setLift(0);
    }
    if(master.get_digital_new_press(DIGITAL_B) == 1) {
      setLift(liftScorePosition);
      while(fabs(liftScorePosition - lift.get_position()) > 5){
        master.print(2,0,"%3f",lift.get_position());
        FL.move(0);
        BL.move(0);
        FR.move(0);
        BR.move(0);
      }
      int startPushIn = millis();
      while(millis() - startPushIn < pushInTime){
        FL.move(pushInPower);
        BL.move(pushInPower);
        FR.move(pushInPower);
        BR.move(pushInPower);
      }
      setLift(0);
      delay(backOutDelay);
      int startBackOut = millis();
      while(millis() - startBackOut < backOutTime2){
        master.print(2,0,"%3f",lift.get_position());
        FL.move(-backOutPower2);
        BL.move(-backOutPower2);
        FR.move(-backOutPower2);
        BR.move(-backOutPower2);
      }
    };

    //L1: small up down
    //A: scoring motion
    //B: descore

    if(master.get_digital_new_press(DIGITAL_LEFT)) autonomous();

    targetIntakeSpd = master.get_digital(DIGITAL_R1)*100-master.get_digital(DIGITAL_R2)*100;
    //targetIntakeSpd*=-1;

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
