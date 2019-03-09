#ifndef _MECH_LIB_HPP_
#define _MECH_LIB_HPP_

void catapultControl(void * ignore);
void liftControl(void * ignore);
void intakeControl(void * ignore);

void setIntake(int dir);
void setLift(int height);

#endif
