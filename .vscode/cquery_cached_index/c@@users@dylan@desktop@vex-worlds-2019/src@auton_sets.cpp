#include "auton_sets.hpp"

void backRed(){
  Motor lift(liftPort);
  Motor intake(intakePort);
  double autonStart = millis();

  setPusher(80);  //Pusher in position to hit low flag

  resetCoord(4,-51.3,90);
  intake.move(100);  //start intake
  baseMove(34.5,0.55,0.1); //Move forward to collect ball
  waitBase(3000);
  delay(200);
  baseMove(-10, 0.59, 0.0);    // move back to position for the turn to the cap
  waitBase(3000);
  intake.move(0);

  baseTurn(-38,0.5,0.15); //Back face cap
  waitBase(3000);

  baseMove(-18.5, 0.6, 0.05); // Move back to Intake cap
  waitBase(3000);
  //delay(500);
  setLift(200);    //raise the cap
  delay(200);

  baseMove(7, 0.64,0.0); //Position to score on post
  waitBase(10000);

  baseTurn(-90,0.9,0.0);
  //baseTurn(-12,-56.8,0.6,0.0); //Face post
  waitBase(3000);

  pausePusher(true);
  baseMove(36.0, 0.38, 0.1);     //Move to Score cap
  waitBase(10000);

  setLift(515);                //score cap
  double startScore = millis();
  while(fabs(515 - lift.get_position()) > 5 && millis()-startScore<1300) {
    delay(25);
  }
  baseMove(-7, 0.5, 0.0);      //Move away from wall
  waitBase(3000);

  pausePusher(false);         //remove it from the slack position
  setLift(0);                  //put lift down
  delay(500);                  //wait for lift to come down

  baseTurn(-5,0.48,0.2);       //Turn to face low flags
  waitBase(3000);
  delay(100);
  baseMove(30,0.55,0.1);        //move to the parking platform
  waitBase(3000);
  baseTurn(-5,49.5,2.0,0.1);      //turn to Score high flags
  waitBase(3000);
  int excessCount = 0;
  while(millis()-autonStart < 14800) {intake.move(-100); delay(25);excessCount++;}  //Waste time until last second
  catapultActivated = true;    //Score 2 high flags
  delay(200);

}


void backBlue(){
  Motor lift(liftPort);
  Motor intake(intakePort);
  double autonStart = millis();

  setPusher(80);  //Pusher in position to hit low flag

  resetCoord(4,-51.3,-90);
  intake.move(100);  //start intake
  baseMove(34.5,0.55,0.1); //Move forward to collect ball
  waitBase(3000);
  delay(200);
  baseMove(-10, 0.59, 0.0);    // move back to position for the turn to the cap
  waitBase(3000);
  intake.move(0);

  baseTurn(38,0.5,0.15); //Back face cap
  waitBase(3000);

  baseMove(-18.5, 0.6, 0.05); // Move back to Intake cap
  waitBase(3000);
//  delay(500);
  setLift(200);    //raise the cap
  delay(200);

  baseMove(7, 0.64,0.0); //Position to score on post
  waitBase(10000);

  baseTurn(90,0.9,0.0);
//  baseTurn(-12,-56.8,0.6,0.0); //Face post
  waitBase(3000);

  pausePusher(true);
  baseMove(36.0, 0.38, 0.1);     //Move to Score cap
  waitBase(10000);

  setLift(515);                //score cap
  double startScore = millis();
  while(fabs(515 - lift.get_position()) > 5 && millis()-startScore<1300) {
    delay(25);
  }
  baseMove(-7, 0.5, 0.0);      //Move away from wall
  waitBase(3000);

  pausePusher(false);         //remove it from the slack position
  setLift(0);                  //put lift down
  delay(500);                  //wait for lift to come down

  baseTurn(5,0.48,0.2);       //Turn to face low flags
  waitBase(3000);
  delay(100);
  baseMove(30,0.55,0.1);        //move to the parking platform
  waitBase(3000);
  baseTurn(-5,49.5,2.0,0.1);      //turn to Score high flags
  waitBase(3000);
  int excessCount = 0;
  while(millis()-autonStart < 14800) {intake.move(-100); delay(25);excessCount++;}
  catapultActivated = true;    //Score 2 high flags
  delay(200);


}


void redCore(){
  Motor intake(intakePort);
  resetCoord(0, 0, 90);

  setPusher(275);   //Setup movement
  baseTurn(115, 1.1, 0.3);  //Turn to face ball on platform
  waitBase(450);
  baseMove(16,0.5,1.3); //Move forward to collect ball
  waitBase(700);
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
  waitBase(800);
  delay(100);
  baseMove(43,0.53,0.2);  //Score low flags
  waitBase(1500);
  delay(200);
  baseMove(-49,0.56,0.2);  //Return to shooting position
  waitBase(1600);
  baseTurn(2,1.5,1.0);  //Turn to face high flags
  waitBase(300);
  catapultActivated = true; //Score 2 high flags
  intake.move(0);
  delay(300);

  setPusher(250);   //Pusher in position to get balls from cap
  baseMove(12,0.5,0.2);    //Position to get good angle to get balls from cap
  waitBase(600);
  baseTurn(45, 0.62, 0.2);   //Face cap
  waitBase(550);
  baseMove(18, 0.3, 0.1);  //Move towards cap
  waitBase(800);
  setPusher(390);
  delay(350);
  pausePusher(true);
  //baseMove(6,0,0.62,0.2);   //Flip cap
  intake.move(100);  //intake balls while moving back
  baseMove(-11,0.7,0.2);
  delay(75);
  waitBase(650);
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
  waitBase(500);
  intake.move(0);
}

void blueCore(){
  Motor intake(intakePort);
  resetCoord(0, 0, -90);

  setPusher(275);   //Setup movement
  baseTurn(-115, 1.1, 0.3);  //Turn to face ball on platform
  waitBase(450);
  baseMove(15,0.5,1.3); //Move forward to collect ball
  waitBase(700);
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
  waitBase(800);
  delay(100);
  baseMove(45,0.65,0.2);  //Score low flags
  waitBase(1700);
  delay(200);
  baseMove(-52,0.45,0.1);  //Return to shooting position
  waitBase(1800);
  baseTurn(-6.5,1.05,0.8);  //Turn to face high flags
  waitBase(300);
  catapultActivated = true; //Score 2 high flags
  intake.move(0);
  delay(300);

  setPusher(250);   //Pusher in position to get balls from cap
  baseMove(12,0.5,0.2);    //Position to get good angle to get balls from cap
  waitBase(600);
  baseTurn(-47, 0.62, 0.2);   //Face cap
  waitBase(550);
  baseMove(18, 0.25, 0.11);  //Move towards cap
  waitBase(800);
  setPusher(390);
  delay(350);
  pausePusher(true);
  //baseMove(6,0,0.62,0.2);   //Flip cap
  intake.move(100);  //intake balls while moving back
  baseMove(-11,0.7,0.2);
  delay(75);
  waitBase(650);
  pausePusher(false);
  setPusher(420);
  /*baseMove(8.5,0.62,0.2);    //Collect balls from cap
  waitBase(600);*/
  delay(750);

  baseMove(-9,0.5,0.0);     //Reverse to original position
  waitBase(600);
  setPusher(80);

  baseTurn(-83,0.9,0.0);      //Turn to get to position to hit next set of flags
  waitBase(500);
  intake.move(0);
}

void basicRed(){
  Motor intake(intakePort);
  double autonStart = millis();

  redCore();
  //setPusher(450);            //push down to push the cap to score
  delay(200);
  baseMove(31,0.5,0.0);       //Position to hit next set of flags
  waitBase(1200);
  baseTurn(47,51,0.6,0.0);    //Face mid flags
  waitBase(650);
  baseMove(-5,0.6,0.0);       //Reverse to get better shooting arc
  waitBase(550);
  setPusher(80);
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
  baseTurn(-49.5,51,0.6,0.0);    //Face mid flags
  waitBase(650);
  baseMove(-5.0,0.6,0.0);       //Reverse to get better shooting arc
  waitBase(600);
  while(millis()-autonStart < 14800) {intake.move(-100); delay(25);}  //Waste time until last second
  baseMove(0,0,0);
  intake.move(-100);
  catapultActivated = true;   //Shoot mid flags
  delay(200);
}

void oppRed(){
  double autonStart = millis();
  Motor intake(intakePort);

  redCore();

  //setPusher(450);              //push down to push the cap to score
  delay(200);
  baseMove(34,0.5,0.0);       //Position to hit next set of flags
  waitBase(1400);
  baseTurn(95,50,0.8,0.0);    //Face opp flags
  waitBase(650);
  baseMove(2,0.9,0.0);     //Move forward to get better arc
  waitBase(350);
  setPusher(80);
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

  delay(200);
  baseMove(36,0.5,0.0);       //Position to hit next set of flags
  waitBase(1600);
  baseTurn(-94,48,0.8,0.0);    //Face opp flags
  waitBase(650);
  while(millis()-autonStart < 14800) {intake.move(-100); delay(25);}  //Waste time until last second
  baseMove(0,0,0);
  intake.move(0);
  catapultActivated = true;   //Shoot mid flags
  delay(200);
}
