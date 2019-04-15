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

 // CONTROL MANUAL //
 // Tank Drive
 // A: Auto cap score
 // B: Auto cap descore
 // X: Hold to stop lift
 // Y:
 // UP:
 // DOWN:
 // LEFT:
 // RIGHT:
 // L1: Cap intake up/down
 // L2: Catapult
 // R1/2: Intake

#define liftScorePosition 515
#define liftDescorePosition 544
#define liftUpPosition 120
#define liftDownPosition 0

#define poleAlignPower 50
#define lowerLiftDelay 200
#define backOutTime 300
#define backOutPower 100

#define pushInDelay 0
#define pushInTime 500
#define pushInPower 50
#define pushIn2Time 200
#define pushIn2Power 80
#define descoreDelay 80

void opcontrol() {
  Motor FL (FLport);
  Motor BL (BLport);
  Motor FR (FRport);
  Motor BR (BRport);
  Motor intake(intakePort);
  Motor lift(liftPort);
  Motor pusher(pusherPort);
  ADIGyro gyro(gyroPort);

  Controller master(E_CONTROLLER_MASTER);

  ADIAnalogIn cataPot(1);
  master.clear();

  Task lifControl(liftControl);
  Task cataControl(catapultControl);
  Task pushControl(pusherControl);

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

    if(master.get_digital_new_press(DIGITAL_L2) == 1) catapultActivated = true;

    if(master.get_digital_new_press(DIGITAL_L1) == 1) {
      if(getLift()==liftDownPosition) setLift(liftUpPosition);
      else setLift(liftDownPosition);
    }
    if(master.get_digital_new_press(DIGITAL_A) == 1) {
      pausePusher(true);
      setLift(liftScorePosition);
      double startScore = millis();
      while(fabs(liftScorePosition - lift.get_position()) > 5 && millis()-startScore<1300){
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
      setPusher(25);
      setLift(liftDescorePosition);
      while(fabs(liftDescorePosition - lift.get_position()) > 5){
        master.print(2,0,"%3f",lift.get_position());
        FL.move(0);
        BL.move(0);
        FR.move(0);
        BR.move(0);
      }
      delay(pushInDelay);
      int startPushIn = millis();
      while(millis() - startPushIn < pushInTime){
        FL.move(pushInPower);
        BL.move(pushInPower);
        FR.move(pushInPower);
        BR.move(pushInPower);
      }
      int startPushIn2 = millis();
      while(millis() - startPushIn2 < pushIn2Time){
        FL.move(pushIn2Power);
        BL.move(pushIn2Power);
        FR.move(pushIn2Power);
        BR.move(pushIn2Power);
      }
      setLift(0);
      delay(descoreDelay);
    };

    if(master.get_digital_new_press(DIGITAL_Y) == 1) {
    	Motor pusher (pusherPort);
      setLift(275);
      FL.tare_position();
    	FR.tare_position();
    	BL.tare_position();
    	BR.tare_position();
      while(BL.get_position()>-15 && BR.get_position()>-15){
        FL.move(-70);
        BL.move(-70);
        FR.move(-70);
        BR.move(-70);
        delay(25);
      }
      FL.move_relative(0, 100);
    	BL.move_relative(0, 100);
    	FR.move_relative(0, 100);
    	BR.move_relative(0, 100);

      setClimb(true);
      pauseLift(true);
      //printf("%f\n",pusher.get_position());
      while(pusher.get_position() > -670) {
        FL.move(0);
        BL.move(0);
        FR.move(0);
        BR.move(0);
        delay(25);
      }
      delay(200);
      FL.tare_position();
    	FR.tare_position();
    	BL.tare_position();
    	BR.tare_position();
      double startClimb = millis();
      while(gyro.get_value() < 45){
        if(millis()-startClimb< 2000){
          setClimb(false);
          pausePusher(true);
        }
        FL.move(120);
        BL.move(120);
        FR.move(120);
        BR.move(120);
        printf("%f \t %f\n",BL.get_actual_velocity(),FL.get_actual_velocity());
        delay(25);
      }
      while(gyro.get_value() > 5){
        FL.move(120);
        BL.move(120);
        FR.move(120);
        BR.move(120);
        printf("%f \t %f\n",BL.get_actual_velocity(),FL.get_actual_velocity());
        delay(25);
      }
      FL.move_relative(0, 100);
    	BL.move_relative(0, 100);
    	FR.move_relative(0, 100);
    	BR.move_relative(0, 100);
    };

    targetIntakeSpd = master.get_digital(DIGITAL_R1)*100-master.get_digital(DIGITAL_R2)*100;
    //targetIntakeSpd*=-1;

    int diff = targetIntakeSpd - intakeSpd;
    if(abs(diff) > 3)intakeSpd += diff>0?3:-3;
    else intakeSpd = targetIntakeSpd;

    intake.move(intakeSpd);

    //pusher.move((master.get_digital(DIGITAL_UP)-master.get_digital(DIGITAL_DOWN))*120);
		FL.move(left-2);
		BL.move(left+2);
		FR.move(right-2);
		BR.move(right+2);

    setPusher(80);
    pausePusher(false);
    setClimb(false);

		delay(5);
	}
}
