#include "skills_sets.hpp"
#include "driver_func.hpp"

void safe_skills(){
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
  baseMove(15.5, 0.3, 0.1);  //Move towards cap
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

  baseMove(-9,0.5,0.0);     //Reverse to original position
  waitBase(600);
  setPusher(80);

  //80 degrees to avoid cap entirely
  baseTurn(83,0.9,0.0);      //Turn to get to position to hit next set of flags
  waitBase(550);


  ////proceed to hit the middle flag
  setPusher(350);               //set to score cap on the floor
  delay(200);
  baseMove(35,0.5,0.0);       //Position to hit next set of flags and also flip the cap on the floor
  waitBase(1500);
  intake.move(0);
  baseTurn(49,51,0.6,0.0);    //Face mid flags
  waitBase(650);
  baseMove(-5.5,0.6,0.0);       //Reverse to get better shooting arc
  waitBase(600);
  setPusher(80);
  delay(700);
  catapultActivated = true;   //Shoot mid flags
  delay(500);

  ////continuation
  intake.move(-100);
  baseTurn(7,2.9,0.25);   //turn to hit the low flag
  waitBase(4000);
  delay(200);
  baseMove(44,0.65,0.05);   //move forward to hit the low flag
  waitBase(3000);
  delay(200);
  baseMove(-7,0.65,0.0);  //move out from the low flag
  waitBase(5000);
  baseTurn(-60,0.6,0.3);   //turn to get to the other cap with 2 balls
  waitBase(3000);
  baseMove(-75,0.55,0.0);   //move to the cap with two balls
  waitBase(3000);
  baseTurn(0,0.6,0.3);   //turn to continue blue side auton
  waitBase(3000);
  intake.move(0);

  //blue auton basically

  setPusher(250);   //Pusher in position to get balls from cap
  baseMove(11.5,0.5,0.2);    //Position to get good angle to get balls from cap
  waitBase(3000);
  baseTurn(-46, 0.62, 0.2);   //Face cap
  waitBase(600);
  baseMove(15.5, 0.2, 0.0);  //Move towards cap
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
  setPusher(100);

  baseTurn(0,0.58,0.1);
  waitBase(3000);
  baseMove(-10,0.7,0.15);     //Move backward to get better arc
  waitBase(650);
  baseTurn(93,50,0.8,0.0);    //Face opp flags
  waitBase(650);
  intake.move(0);
  delay(200);
  catapultActivated = true;   //Shoot opp flags
  delay(200);

  //going to climb
  intake.move(-100);
  baseMove(5,0.5,0.0);        //move forward to position for the turn
  waitBase(3000);
  setPusher(340);
  baseTurn(-90,0.62,0.2);     //turn to move forward to climb
  waitBase(3000);
  baseMove(30,0.8,0.0);
  waitBase(3000);
  delay(600);
  setPusher(80);
  delay(500);
  baseMove(-10,0.7,0.2);
  waitBase(3000);
  setPusher(420);
  delay(500);
  baseMove(37,0.9,0.0);
  waitBase(3000);
  intake.move(0);
  baseMove(-8,0.7,0.2);
  waitBase(3000);
  setPusher(270);
  delay(500);
  baseTurn(-180,0.62,0.2);
  waitBase(3000);
  baseMove(10,0.5,0.0);
  waitBase(500);
  pauseBase(true);
  directClimb();
  delay(200);
}
