#include "main.h"
#include "mech_lib.hpp"
#include "base_lib.hpp"
#include "driver_func.hpp"

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
 // X: Auto Flip Cap
 // Y: Direct Climb
 // UP:
 // DOWN:
 // LEFT:
 // RIGHT:
 // L1: Cap intake up/down
 // L2: Catapult
 // R1/2: Intake

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
  bool pusherReadyToFlip = false;

  setPusher(80);
  setLift(liftDownPosition);
	while (true) {
    //master.print(2, 0, "Auton: %2d", autonNum);
    //master.print(2, 0, "Pot: %4d", cataPot.get_value());
    //master.print(2, 0, "Pow: %7d", catapult.get_power());
    //printf("Gyro value : %f\n", gyro.get_value());
    int left = master.get_analog(ANALOG_LEFT_Y);
		int right = master.get_analog(ANALOG_RIGHT_Y);

    if(master.get_digital_new_press(DIGITAL_L2) == 1) catapultActivated = true;

    if(master.get_digital_new_press(DIGITAL_L1) == 1) {
      if(getLift()==liftDownPosition) setLift(liftUpPosition);
      else setLift(liftDownPosition);
    }
    if(master.get_digital_new_press(DIGITAL_A) == 1) scoreCap();
    if(master.get_digital_new_press(DIGITAL_B) == 1) descoreCap();

    if(master.get_digital_new_press(DIGITAL_Y) == 1) directClimb();

    if(master.get_digital_new_press(DIGITAL_X) == 1) { //Auto getting balls from the cap
      if(!pusherReadyToFlip) {
        setPusher(300);
        pusherReadyToFlip = true;
      }
      else{
        Motor pusher (pusherPort);
        Motor intake (intakePort);
        setPusher(400);
        delay(400);
        pausePusher(true);

        FL.tare_position();
        FR.tare_position();
        BL.tare_position();
        BR.tare_position();
        double startReverse = millis();
        while(millis()-startReverse < 300){
          FL.move(-70);
          BL.move(-70);
          FR.move(-70);
          BR.move(-70);
          intake.move(100);
          delay(25);
        }
      /*  FL.move(0);
        BL.move(0);
        FR.move(0);
        BR.move(0);
        delay(1000);
        double startReverse2 = millis();
        while(millis()-startReverse2 < 300){
          FL.move(-70);
          BL.move(-70);
          FR.move(-70);
          BR.move(-70);
          intake.move(100);
          delay(25);
        }*/
        pausePusher(false);
        setPusher(80);
        intake.move(0);
        delay(200);
        pusherReadyToFlip = false;
      }
      FL.move_relative(0, 100);
      BL.move_relative(0, 100);
      FR.move_relative(0, 100);
      BR.move_relative(0, 100);
      intake.move(0);
      delay(200);
      pausePusher(false);
    };

if(master.get_digital_new_press(DIGITAL_LEFT) == 1) {
  double startreset = millis();
  while(millis()- startreset < 1000){
  pusher.move(80);
}
delay(200);
 pausePusher(true);
 delay(200);
  pusher.tare_position();
  delay(100);
  pausePusher(false);
  setPusher(80);
  delay(100);

}



    targetIntakeSpd = master.get_digital(DIGITAL_R1)*110-master.get_digital(DIGITAL_R2)*110;
    //targetIntakeSpd*=-1;

    int diff = targetIntakeSpd - intakeSpd;
    if(abs(diff) > 3)intakeSpd += diff>0?3:-3;
    else intakeSpd = targetIntakeSpd;

    intake.move(intakeSpd);

    FL.move(left-2);
    BL.move(left+2);
    FR.move(right-2);
    BR.move(right+2);

    pausePusher(false);
    setClimb(false);

    delay(5);

	}
}
