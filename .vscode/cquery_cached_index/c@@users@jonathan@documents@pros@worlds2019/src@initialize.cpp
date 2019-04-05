#include "main.h"

int autonNum;
bool catapultReady = false;
bool catapultActivated = false;

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	initSelector();

	Motor FL (FLport, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
	Motor BL (BLport, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
	Motor FR (FRport, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
	Motor BR (BRport, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
	Motor lift (liftPort, E_MOTOR_GEARSET_36, false, E_MOTOR_ENCODER_DEGREES);
	Motor intake(intakePort, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_DEGREES);
	Motor catapult(catapultPort, E_MOTOR_GEARSET_36, true, E_MOTOR_ENCODER_DEGREES);
	Motor pusher(pusherPort, E_MOTOR_GEARSET_36, true, E_MOTOR_ENCODER_DEGREES);
	//Motor catapultL(catapultLPort, E_MOTOR_GEARSET_36, false, E_MOTOR_ENCODER_DEGREES);
	//Motor catapultR(catapultRPort, E_MOTOR_GEARSET_36, true, E_MOTOR_ENCODER_DEGREES);
	lift.tare_position();
  pusher.tare_position();
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}
