#include "auton_sets.hpp"
void basicRed(){

}

void basicBlue(){
  Motor intake(intakePort);

  setPusher(300);   //Setup movement
  baseMove(17.0, 0.5, 1.4); //Move forward to collect ball
  waitBase(1000);
  setPusher(450);   //Collapse pusher over ball
  intake.move(100);
  delay(200);
  baseMove(-17.0, 0.5, 1.4);  //Move back to original position and intake ball
  waitBase(1000);
  setPusher(0);
  delay(600);   //Wait for ball to settle
  baseTurn(120, 0.6, 0.7);    //Turn to shoot
  waitBase(1000);
  delay(300);
  catapultActivated = true;   //Shoot side flags
  delay(150);
  
}

void oppRed(){

}

void oppBlue(){

}
