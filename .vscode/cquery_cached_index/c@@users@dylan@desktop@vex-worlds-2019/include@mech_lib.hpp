#ifndef _MECH_LIB_HPP_
#define _MECH_LIB_HPP_


void catapultControl(void * ignore);
void liftControl(void * ignore);
void pusherControl(void * ignore);
//void intakeControl(void * ignore);

//void setIntake(int targetBalls);
void setLift(int height);
int getLift();
void setPusher(double height);
void pausePusher(bool pause);
void setClimb(bool climbing);
void pauseLift(bool pause);

#endif
