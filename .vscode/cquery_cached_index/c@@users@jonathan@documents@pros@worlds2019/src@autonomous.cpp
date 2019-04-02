#include "auton_sets.hpp"

//------------- AUTONOMOUS ROUTINES ------------//
// 1: Front tile, side and mid pole (16)        //
// 2: Front tile, opponent and mid pole (12)    //
// 3: Back tile, side pole and park (13)        //
// 4: Back tile, pole cap, floor cap, park (13) //
// 5: Get ball under cap (1)                    //
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

  autonNum = 6;
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
  }
}
