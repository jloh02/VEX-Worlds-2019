#include "auton_sets.hpp"
void basicRed(){

}

void basicBlue(){
  double autonStart = millis();
  resetCoord(0, 0, -117);

  Motor intake(intakePort);

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
  baseTurn(7,0.4,0.7);
  waitBase(1200);
  //'delay(300);
  baseMove(46,0.37,1.5);
  waitBase(1500);
  baseMove(-52,0.4,1.5);
  waitBase(1500);
  baseTurn(-6, 0.5,0.4);
  waitBase(1000);
  catapultActivated=true;
  intake.move(0);
  delay(300);

  /*delay(400);   //Wait for ball to settle
  baseTurn(0, 0.7, 0.7);    //Turn to shoot
  waitBase(1000);
  baseMove(-5,0.5,0.5);     //Move back to get better shooting angle
  waitBase(1000);
  delay(200);
  intake.move(0);
  catapultActivated = true;   //Shoot side flags
  delay(250);*/

  //baseMove(0,4.3,0.6,1.3);
  //waitBase(600);
  setPusher(250);
  baseMove(3,0.7,0.7);
  waitBase(1500);
  baseTurn(-22, 24.5, 0.7, 0.7);   //Face cap
  waitBase(1000);
  baseMove(24, 0.45, 1.2);  //Move towards cap
  waitBase(1100);
  setPusher(387);
  delay(100);
  baseMove(-7,0,0.7,1.0); //Flip cap
  delay(75);
  intake.move(100);
  waitBase(1000);
  baseMove(8.5,0.7,1.0);     //Collect balls from cap
  waitBase(1000);
  delay(200);

  baseMove(-8.5,0.7,1.0);     //Reverse to original position
  waitBase(1200);
  setPusher(80);
  baseTurn(-92,0.7,0.7);
  waitBase(2000);
  baseMove(24,0.7,1.3);
  waitBase(2000);
  intake.move(0);
  baseTurnRelative(62,0.75,0.7);
  waitBase(1200);
  baseMove(-5,0.7,0.7);
  waitBase(800);
  while(millis()-autonStart < 14800) {intake.move(100); delay(25);}
  baseMove(0,0,0);
  intake.move(0);
  catapultActivated = true;
  delay(200);
  /*baseTurn(10,0.55,0.7);    //Face side low flag
  waitBase(1000);
  intake.move(0);
  baseMove(44,0.55,1.3);  //Score low flag
  waitBase(1000);

  baseMove(-24,0.6,1.3);    //Position to shoot middle flags
  waitBase(1000);
  baseTurnRelative(45,0.65,0.7);
  waitBase(1000);
  baseMove(-32,0.7,1.3);
  waitBase(1500);
  delay(100);

  baseTurn(-50,68,0.6,0.7); //Aim middle flags
  waitBase(800);
  //delay(300);
  while(millis()-autonStart < 14800) {intake.move(100); delay(25);}
  intake.move(0);
  catapultActivated = true;   //Shoot side flags
  delay(200);*/

}

void oppRed(){

}

void oppBlue(){

}
