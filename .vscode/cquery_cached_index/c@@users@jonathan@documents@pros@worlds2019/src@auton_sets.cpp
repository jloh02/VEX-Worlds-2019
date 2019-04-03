#include "auton_sets.hpp"

void redCore(){
  Motor intake(intakePort);
  resetCoord(0, 0, 117);

  setPusher(275);   //Setup movement
  baseMove(15.0, 0.6, 1.2); //Move forward to collect ball
  waitBase(1000);
  setPusher(380);   //Collapse pusher over ball
  intake.move(100);
  delay(200);
  baseMove(-15.0, 0.55, 1.4);  //Move back to original position and intake ball
  delay(100);
  setPusher(450);
  waitBase(1000);
  setPusher(80);  //Pusher in position to hit low flag
  delay(500);

  baseTurn(-7,0.4,0.7);  //Turn to face low flags
  waitBase(1200);
  baseMove(46,0.37,1.5);  //Score low flags
  waitBase(1500);
  baseMove(-52,0.4,1.5);  //Return to shooting position
  waitBase(1500);
  baseTurn(6, 0.5,0.4);  //Turn to face high flags
  waitBase(1000);
  catapultActivated = true; //Score 2 high flags
  intake.move(0);
  delay(300);

  setPusher(250);   //Pusher in position to get balls from cap
  baseMove(3,0.7,0.7);    //Position to get good angle to get balls from cap
  waitBase(1500);
  baseTurn(22, 24.5, 0.7, 0.7);   //Face cap
  waitBase(1000);
  baseMove(24, 0.45, 1.2);  //Move towards cap
  waitBase(1100);
  setPusher(387);
  delay(100);
  baseMove(-7,0,0.7,1.0);   //Flip cap
  delay(75);
  intake.move(100);
  waitBase(1000);
  baseMove(8.5,0.7,1.0);    //Collect balls from cap
  waitBase(1000);
  delay(200);

  baseMove(-8.5,0.7,1.0);     //Reverse to original position
  waitBase(1200);
  setPusher(80);
}

void blueCore(){
  Motor intake(intakePort);
  resetCoord(0, 0, -117);

  setPusher(275);   //Setup movement
  baseMove(15.0, 0.6, 1.2); //Move forward to collect ball
  waitBase(1000);
  setPusher(380);   //Collapse pusher over ball
  intake.move(100);
  delay(200);
  baseMove(-15.0, 0.55, 1.4);  //Move back to original position and intake ball
  delay(100);
  setPusher(450);
  waitBase(1000);
  setPusher(80);  //Pusher in position to hit low flag
  delay(500);

  baseTurn(7,0.4,0.7);  //Turn to face low flags
  waitBase(1200);
  baseMove(46,0.37,1.5);  //Score low flags
  waitBase(1500);
  baseMove(-52,0.4,1.5);  //Return to shooting position
  waitBase(1500);
  baseTurn(-6, 0.5,0.4);  //Turn to face high flags
  waitBase(1000);
  catapultActivated = true; //Score 2 high flags
  intake.move(0);
  delay(300);

  setPusher(250);   //Pusher in position to get balls from cap
  baseMove(3,0.7,0.7);    //Position to get good angle to get balls from cap
  waitBase(1500);
  baseTurn(-22, 24.5, 0.7, 0.7);   //Face cap
  waitBase(1000);
  baseMove(24, 0.45, 1.2);  //Move towards cap
  waitBase(1100);
  setPusher(387);
  delay(100);
  baseMove(-7,0,0.7,1.0);   //Flip cap
  delay(75);
  intake.move(100);
  waitBase(1000);
  baseMove(8.5,0.7,1.0);    //Collect balls from cap
  waitBase(1000);
  delay(200);

  baseMove(-8.5,0.7,1.0);     //Reverse to original position
  waitBase(1200);
  setPusher(80);
}

void basicRed(){
  Motor intake(intakePort);
  double autonStart = millis();

  redCore();

  baseTurn(92,0.7,0.7);      //Turn to get to position to hit mid flags
  waitBase(2000);
  baseMove(24,0.7,1.3);       //Position to hit mid flags
  waitBase(2000);
  intake.move(0);
  baseTurnRelative(-62,0.75,0.7);    //Face mid flags
  waitBase(1200);
  baseMove(-5,0.7,0.7);       //Reverse to get better shooting arc
  waitBase(800);
  while(millis()-autonStart < 14800) {intake.move(100); delay(25);}  //Waste time until last second
  baseMove(0,0,0);
  intake.move(0);
  catapultActivated = true;   //Shoot mid flags
  delay(200);
}

void basicBlue(){
  double autonStart = millis();
  Motor intake(intakePort);

  blueCore();

  baseTurn(-92,0.7,0.7);      //Turn to get to position to hit mid flags
  waitBase(2000);
  baseMove(24,0.7,1.3);       //Position to hit mid flags
  waitBase(2000);
  intake.move(0);
  baseTurnRelative(62,0.75,0.7);    //Face mid flags
  waitBase(1200);
  baseMove(-5,0.7,0.7);       //Reverse to get better shooting arc
  waitBase(800);
  while(millis()-autonStart < 14800) {intake.move(100); delay(25);}  //Waste time until last second
  baseMove(0,0,0);
  intake.move(0);
  catapultActivated = true;   //Shoot mid flags
  delay(200);
}

void oppRed(){

}

void oppBlue(){

}
