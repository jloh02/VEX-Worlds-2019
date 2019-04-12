#include "skills_sets.hpp"    

void real_skills(){
  Motor intake(intakePort);
  Motor lift(liftPort);
  resetCoord(3,-49 ,90);

  intake.move(100);
  setPusher(320);   //Setup movement
  baseMove(40,0.45,1.3); //Move forward to push cap and collect ball
  waitBase(3000);
  delay(200);
  baseMove(-15, 0.45,1.3);  //Move back to get cap
  delay(400);
  setPusher(80);  //Pusher in position to hit low flag
  waitBase(3000);

  baseTurn(45,-60,0.8,0.2, true); //Back face cap
  waitBase(3000);
  baseMove(-33, 0.5, 1.3); // Intake cap
  waitBase(3000);
  setLift(120);
  delay(200);
  baseMove(5, 0.6, 1.3); //Position to score on post
  waitBase(3000);

  baseTurn(-90,0.5,0.2, true); //Face post
  waitBase(3000);
  baseMove(-40, 0.5, 1.3);  //Score cap
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
  delay(100);
  baseMove(91,0.53,0.2);  //Score low flags
  while(getY()<0) delay(25); //Shoot high flags while going forward to hit low flag
  catapultActivated = true; //Score 2 high flags
  waitBase(3000);
  delay(200);
  baseMove(-52,0.56,0.2);  //Return to shooting position
  waitBase(3000);
  baseTurn(2,3.0,0.0);  //Turn to face high flags
  waitBase(3000);

  intake.move(0);
  delay(300);

  setPusher(250);   //Pusher in position to get balls from cap
  baseMove(11.5,0.5,0.2);    //Position to get good angle to get balls from cap
  waitBase(3000);
  baseTurn(45, 0.6, 0.2);   //Face cap
  waitBase(3000);
  baseMove(17, 0.45, 0.3);  //Move towards cap
  waitBase(3000);
  setPusher(390);
  delay(100);
  baseMove(7,0,0.62,0.2);   //Flip cap
  delay(75);
  intake.move(100);
  waitBase(3000);
  baseMove(8.5,0.62,0.2);    //Collect balls from cap
  waitBase(3000);
  delay(200);

  catapultActivated = true; //Score 2 high flags
  intake.move(0);
  delay(300);

  baseMove(-5,0.5,0.0);     //Reverse to original position
  waitBase(3000);
  setPusher(80);

  baseTurn(80,0.9,0.0);      //Turn to get to position to hit next set of flags
  waitBase(3000);
  intake.move(0);
}
