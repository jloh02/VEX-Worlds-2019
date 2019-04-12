#include "auton_sets.hpp"
#include "skills_sets.hpp"

//------------- AUTONOMOUS ROUTINES ------------//
// 1: Front tile, side and mid pole (16)        //
// 2: Front tile, opponent and mid pole (12)    //
// 3: Back tile, side pole and park (13)        //
// 4: Safe Skills                               //
// 5:                                           //
// 1-5 for RED, 6-10 for BLUE                   //
// 999: Skills                                  //
//----------------------------------------------//

void autonomous() {
  Task cataControl(catapultControl);
  Task basControl(baseControl);
  Task basOdometry(baseOdometry);
  Task basMotorControl(baseMotorControl);
  Task lifControl(liftControl);
  Task pushControl(pusherControl);

	Motor lift (liftPort);
  lift.tare_position();
  Motor pusher (pusherPort);
  pusher.tare_position();

  //resetCoord(0,0,0);
  //baseMove(40,0.52,0.9);
  //waitBase(10000);

  switch(autonNum){
    case 1:
      basicRed();
      break;
    case 2:
      oppRed();
      break;
    case 6:
      basicBlue();
      break;
    case 7:
      oppBlue();
      break;
    case 5:
      safe_skills();
      break;
    case 10:
      real_skills();
      break;
  }
}
