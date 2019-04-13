#include "auton_sets.hpp"

void redCore(){
  Motor intake(intakePort);
  resetCoord(0, 0, 90);

  setPusher(275);   //Setup movement
  baseTurn(115, 1.1, 0.3);  //Turn to face ball on platform
  waitBase(800);
  baseMove(16,0.5,1.3); //Move forward to collect ball
  waitBase(800);
  setPusher(370);   //Collapse pusher over ball
  intake.move(100);
  delay(200);
  baseMove(-16, 0.5,1.3);  //Move back to original position and intake ball
  delay(100);
  setPusher(450);
  waitBase(700);
  setPusher(80);  //Pusher in position to hit low flag
  delay(300);

  baseTurn(-5,0.48,0.5);  //Turn to face low flags
  waitBase(850);
  delay(100);
  baseMove(43,0.53,0.2);  //Score low flags
  waitBase(1800);
  delay(200);
  baseMove(-49,0.56,0.2);  //Return to shooting position
  waitBase(1800);
  baseTurn(2,1.5,1.0);  //Turn to face high flags
  waitBase(300);
  catapultActivated = true; //Score 2 high flags
  intake.move(0);
  delay(300);

  setPusher(250);   //Pusher in position to get balls from cap
  baseMove(12,0.5,0.2);    //Position to get good angle to get balls from cap
  waitBase(750);
  baseTurn(45, 0.62, 0.2);   //Face cap
  waitBase(600);
  baseMove(18, 0.3, 0.1);  //Move towards cap
  waitBase(800);
  setPusher(390);
  delay(500);
  pausePusher(true);
  //baseMove(6,0,0.62,0.2);   //Flip cap
  intake.move(100);  //intake balls while moving back
  baseMove(-11,0.7,0.2);
  delay(75);
  waitBase(800);
  pausePusher(false);
  setPusher(420);
  /*baseMove(8.5,0.62,0.2);    //Collect balls from cap
  waitBase(600);*/
  delay(750);

  baseMove(-8,0.5,0.0);     //Reverse to original position
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
  baseTurn(-115, 1.1, 0.3);  //Turn to face ball on platform
  waitBase(800);
  baseMove(15,0.5,1.3); //Move forward to collect ball
  waitBase(800);
  setPusher(370);   //Collapse pusher over ball
  intake.move(100);
  delay(200);
  baseMove(-15, 0.5,1.3);  //Move back to original position and intake ball
  delay(100);
  setPusher(450);
  waitBase(700);
  setPusher(80);  //Pusher in position to hit low flag
  delay(300);

  baseTurn(5,0.45,0.25);  //Turn to face low flags
  waitBase(850);
  delay(100);
  baseMove(46,0.64,0.2);  //Score low flags
  waitBase(1900);
  delay(200);
  baseMove(-52,0.3,0.1);  //Return to shooting position
  waitBase(1300);
  baseTurn(-2,1.05,0.2);  //Turn to face high flags
  waitBase(800);
  catapultActivated = true; //Score 2 high flags
  intake.move(0);
  delay(200);

  setPusher(250);   //Pusher in position to get balls from cap
  baseMove(12,0.5,0.2);    //Position to get good angle to get balls from cap
  waitBase(750);
  baseTurn(-45, 0.62, 0.2);   //Face cap
  waitBase(600);
  baseMove(18, 0.25, 0.11);  //Move towards cap
  waitBase(800);
  setPusher(390);
  delay(500);
  pausePusher(true);
  //baseMove(6,0,0.62,0.2);   //Flip cap
  intake.move(100);  //intake balls while moving back
  baseMove(-11,0.7,0.2);
  delay(75);
  waitBase(800);
  pausePusher(false);
  setPusher(420);
  /*baseMove(8.5,0.62,0.2);    //Collect balls from cap
  waitBase(600);*/
  delay(600);

  baseMove(-8,0.5,0.0);     //Reverse to original position
  waitBase(600);
  setPusher(80);

  baseTurn(-83,0.9,0.0);      //Turn to get to position to hit next set of flags
  waitBase(550);
  intake.move(0);
}

void basicRed(){  //94%
  Motor intake(intakePort);
  double autonStart = millis();

  redCore();

  baseMove(31,0.5,0.0);       //Position to hit next set of flags
  waitBase(1300);
  baseTurn(47,51,0.6,0.0);    //Face mid flags
  waitBase(650);
  baseMove(-5,0.6,0.0);       //Reverse to get better shooting arc
  waitBase(600);
  int excessCount = 0;
  while(millis()-autonStart < 14800) {intake.move(-100); delay(25);excessCount++;}  //Waste time until last second
  printf("Excess: %d\n", excessCount*25);
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
  baseTurn(-48.5,51,0.6,0.0);    //Face mid flags
  waitBase(650);
  baseMove(-5,0.6,0.0);       //Reverse to get better shooting arc
  waitBase(600);
  while(millis()-autonStart < 14800) {intake.move(-100); delay(25);}  //Waste time until last second
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
  baseTurn(95,50,0.8,0.0);    //Face mid flags
  waitBase(650);
  baseMove(2,0.9,0.0);     //Move forward to get better arc
  //waitBase(650);
  while(millis()-autonStart < 14800) {intake.move(-100); delay(25);}  //Waste time until last second
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
  baseTurn(-94,48,0.8,0.0);    //Face opp flags
  waitBase(650);
  while(millis()-autonStart < 14800) {intake.move(-100); delay(25);}  //Waste time until last second
  baseMove(0,0,0);
  intake.move(0);
  catapultActivated = true;   //Shoot mid flags
  delay(200);
}
