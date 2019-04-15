#include "skills_sets.hpp"

void real_skills(){
  Motor intake(intakePort);
  Motor lift(liftPort);
  resetCoord(4,-51.3 ,90);

  intake.move(100);
  setPusher(320);   //Setup movement
  baseMove(35,0.45,1.3); //Move forward to push cap and collect ball
  waitBase(3000);
  delay(200);
/*  baseMove(-10, 0.5,1.3);  //Move back to get cap
  delay(400);
  setPusher(80);  //Pusher in position to hit low flag
  waitBase(3000);

  baseTurn(-37,0.5,0.3); //Back face cap
  waitBase(3000);
  baseMove(-18, 0.5, 1.3); // Intake cap
  waitBase(3000);
  setLift(120);
  delay(200);
  baseMove(10, 0.6, 0.2); //Position to score on post
  waitBase(3000);

  baseTurn(-90,0.6,0.2); //Face post
  waitBase(3000);

  baseMove(35, 0.5, 1.3);  //Score cap
  delay(800);
  setLift(515);
  waitBase(3000);
  double startScore = millis();
  while(fabs(515 - lift.get_position()) > 5 && millis()-startScore<1300){
    delay(25);
  }
  baseMove(5, 0.6,0.2); //Move away from wall
  waitBase(3000);

  baseTurn(-3,0.48,0.5);  //Turn to face low flags
  waitBase(3000);
  setLift(0);
  delay(100);
  baseMove(91,0.53,0.2);  //Score low flags
  while(getY()<0) delay(25); //Shoot high flags while going forward to hit low flag
  catapultActivated = true; //Score 2 high flags
  waitBase(3000);
  delay(200);

  //////////FROM HERE: IT IS AUTONOMOUS
  baseMove(-40.5,0.56,0.2);  //Get into position to get balls from cap
  waitBase(3000);
  setPusher(250);   //Pusher in position to get balls from cap
  baseTurn(45, 0.6, 0.2);   //Face cap
  waitBase(3000);
  baseMove(18, 0.3, 0.1);  //Move towards cap
  waitBase(3000);
  pausePusher(true);       //Let the pusher go slack
  delay(500);
  //baseMove(7,0,0.62,0.2);
  intake.move(100);
  baseMove(-11,0.7,0.2);    //Collect balls from cap
  waitBase(3000);
  delay(75);
  pausePusher(false);
  setPusher(420);
  delay(750);

  baseMove(-8,0.5,0.0);     //Reverse to original position
  waitBase(3000);
  setPusher(320);           //set pusher to flip the cap

  baseTurn(83,0.9,0.0);      //Turn to get to position to hit next set of flags
  waitBase(3000);
  intake.move(0);

  baseMove(31,0.5,0.0);       //Position to hit next set of flags
  waitBase(3000);
  setPusher(80);              //set pusher to hit low flags
  baseTurn(47,51,0.6,0.0);    //Face mid flags
  waitBase(3000);
  baseMove(-5,0.6,0.0);       //Reverse to get better shooting arc
  waitBase(3000);
  catapultActivated = true;   //Shoot mid flags
  delay(200);

//////////END OF AUTONOMOUS PORTION (Scoring of low middle flag and repositioning for auton to the other side)
//values from here onwards need a completely new tuning values

  baseMove(49,0.5,0.0); // move to hit the low flags of the middle pole
  waitBase(3000);
  baseMove(30,0.5,0.0);  // position for the Turn
  waitBase(3000);
  baseTurn(-90,0.5,0.0);
  waitBase(3000);
  baseMove(-55,0.5,0.0);  // move to position to face cap
  waitBase(3000);
  setPusher(250);   //Pusher in position to get balls from cap
  baseTurn(-45, 0.6, 0.2);   //Face cap
  waitBase(3000);

//Collecting balls
  baseMove(18, 0.3, 0.1);  //Move towards cap
  waitBase(3000);
  pausePusher(true);       //Let the pusher go slack
  delay(500);
  //baseMove(7,0,0.62,0.2);
  intake.move(100);
  baseMove(-11,0.7,0.2);    //Collect balls from cap
  waitBase(3000);
  delay(75);
  pausePusher(false);
  setPusher(420);
  delay(750);

//Scoring Flags on the far side
  baseMove(-8,0.5,0.0);     //Reverse to scoring position for the far side flags
  waitBase(3000);
  setPusher(80);

  baseTurn(47,51,0.6,0.0);    //Face far side flags
  waitBase(3000);
  catapultActivated = true;   //Shoot far side flags
  delay(200);
*/
}
