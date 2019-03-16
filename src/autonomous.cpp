#include "main.h"
#include "base_lib.hpp"
#include "mech_lib.hpp"

/*
prosv5 b
prosv5 u
*/

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */

void autonomous() {
  Motor intake(intakePort);

  double start = millis();
  Task cataControl(catapultControl);
  Task basControl(baseControl);
  Task basOdometry(baseOdometry);
  Task basMotorControl(baseMotorControl);
  Task lifControl(liftControl);
  
  baseMove(300,0.28,1.4);
  waitBase(1100);
  delay(500);
  intake.move(-42);
  baseMove(-90,0.9,0.8);
  waitBase(1000);
  //delay(150);
  intake.move(0);
  delay(350);
  intake.move(100);
  baseMove(-150,0.63,1.4);
  //delay(100);
  //intake.move(100);
  waitBase(1000);
  delay(1000);
  intake.move(0);
}
