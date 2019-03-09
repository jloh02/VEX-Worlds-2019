#include "main.h"
#include "base_lib.hpp"
#include "mech_lib.hpp"

#define RED true

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
  double start = millis();
  Task cataControl(catapultControl);
  Task basControl(baseControl);
  Task basOdometry(baseOdometry);
  Task basMotorControl(baseMotorControl);
  Task lifControl(liftControl);
  Task intControl(intakeControl);


  baseMove(3000,0.4,0.0);

}
