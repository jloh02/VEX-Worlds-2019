#include "auton_sets.hpp"

void redCore(){
  Motor intake(intakePort);
  resetCoord(0, 0, 90);

  setPusher(275);   //Setup movement
  baseTurn(116.5, 0.62, 0.2);  //Turn to face ball on platform
  waitBase(600);
  baseMove(14,0.5,1.3); //Move forward to collect ball
  waitBase(800);
  setPusher(370);   //Collapse pusher over ball
  intake.move(100);
  delay(200);
  baseMove(-14, 0.5,1.3);  //Move back to original position and intake ball
  delay(100);
  setPusher(450);
  waitBase(700);
  setPusher(80);  //Pusher in position to hit low flag
  delay(300);

  baseTurn(-5,0.48,0.5);  //Turn to face low flags
  waitBase(850);
  delay(100);
  baseMove(46,0.53,0.2);  //Score low flags
  waitBase(1900);
  delay(200);
  baseMove(-52,0.56,0.2);  //Return to shooting position
  waitBase(1900);
  baseTurn(2,3.0,0.0);  //Turn to face high flags
  waitBase(400);
  catapultActivated = true; //Score 2 high flags
  intake.move(0);
  delay(300);

  setPusher(250);   //Pusher in position to get balls from cap
  baseMove(12,0.5,0.2);    //Position to get good angle to get balls from cap
  waitBase(750);
  baseTurn(45, 0.62, 0.2);   //Face cap
  waitBase(600);
  baseMove(17, 0.45, 0.3);  //Move towards cap
  waitBase(1000);
  setPusher(390);
  delay(100);
  baseMove(6,0,0.62,0.2);   //Flip cap
  delay(75);
  intake.move(100);
  waitBase(1000);
  baseMove(8.5,0.62,0.2);    //Collect balls from cap
  waitBase(600);
  delay(200);

  baseMove(-5,0.5,0.0);     //Reverse to original position
  waitBase(600);
  setPusher(80);

  //80 degrees to avoid cap entirely
  baseTurn(83,0.9,0.0);      //Turn to get to position to hit next set of flags
  waitBase(550);
  intake.move(0);
}

void blueCore(){
  Motor intake(intakePort);
  resetCoord(0, 0, -90);

  setPusher(275);   //Setup movement
  baseTurn(-116.5, 0.62, 0.2);  //Turn to face ball on platform
  waitBase(600);
  baseMove(14,0.5,1.3); //Move forward to collect ball
  waitBase(800);
  setPusher(370);   //Collapse pusher over ball
  intake.move(100);
  delay(200);
  baseMove(-14, 0.5,1.3);  //Move back to original position and intake ball
  delay(100);
  setPusher(450);
  waitBase(700);
  setPusher(80);  //Pusher in position to hit low flag
  delay(300);

  baseTurn(5,0.48,0.5);  //Turn to face low flags
  waitBase(850);
  delay(100);
  baseMove(46,0.53,0.2);  //Score low flags
  waitBase(1900);
  delay(200);
  baseMove(-52,0.56,0.2);  //Return to shooting position
  waitBase(1900);
  baseTurn(-2,3.0,0.0);  //Turn to face high flags
  waitBase(400);
  catapultActivated = true; //Score 2 high flags
  intake.move(0);
  delay(200);

  setPusher(250);   //Pusher in position to get balls from cap
  baseMove(11.5,0.5,0.2);    //Position to get good angle to get balls from cap
  waitBase(700);
  baseTurn(-45, 0.6, 0.2);   //Face cap
  waitBase(600);
  baseMove(17, 0.45, 0.3);  //Move towards cap
  waitBase(1000);
  setPusher(390);
  delay(100);
  baseMove(-7,0,0.62,0.2);   //Flip cap
  delay(75);
  intake.move(100);
  waitBase(1000);
  baseMove(8.5,0.62,0.2);    //Collect balls from cap
  waitBase(600);
  delay(200);

  baseMove(-5,0.5,0.0);     //Reverse to original position
  waitBase(600);
  setPusher(80);

  baseTurn(-83,0.9,0.0);      //Turn to get to position to hit next set of flags
  waitBase(550);
  intake.move(0);
}

void basicRed(){
  Motor intake(intakePort);
  double autonStart = millis();

  redCore();

  baseMove(31,0.5,0.0);       //Position to hit next set of flags
  waitBase(1300);
  baseTurn(47,51,0.6,0.0);    //Face mid flags
  waitBase(650);
  baseMove(-5,0.6,0.0);       //Reverse to get better shooting arc
  waitBase(600);
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

  baseMove(31,0.5,0.0);       //Position to hit next set of flags
  waitBase(1300);
  baseTurn(-46.5,51,0.6,0.0);    //Face mid flags
  waitBase(650);
  baseMove(-5,0.6,0.0);       //Reverse to get better shooting arc
  waitBase(600);
  while(millis()-autonStart < 14800) {intake.move(100); delay(25);}  //Waste time until last second
  baseMove(0,0,0);
  intake.move(0);
  catapultActivated = true;   //Shoot mid flags
  delay(200);
}

void oppRed(){
  double autonStart = millis();
  Motor intake(intakePort);

  redCore();

  baseMove(34,0.5,0.0);       //Position to hit next set of flags
  waitBase(1500);
  baseTurn(91.5,50,0.8,0.0);    //Face mid flags
  waitBase(650);
  baseMove(3,0.9,0.0);     //Reverse to original position
  //waitBase(650);
  while(millis()-autonStart < 14800) {intake.move(100); delay(25);}  //Waste time until last second
  baseMove(0,0,0);
  intake.move(0);
  catapultActivated = true;   //Shoot mid flags
  delay(200);
}

void oppBlue(){
  double autonStart = millis();
  Motor intake(intakePort);

  blueCore();

  baseMove(36,0.5,0.0);       //Position to hit next set of flags
  waitBase(1700);
  baseTurn(-94,51,0.8,0.0);    //Face mid flags
  waitBase(650);
  while(millis()-autonStart < 14800) {intake.move(100); delay(25);}  //Waste time until last second
  baseMove(0,0,0);
  intake.move(0);
  catapultActivated = true;   //Shoot mid flags
  delay(200);
}
