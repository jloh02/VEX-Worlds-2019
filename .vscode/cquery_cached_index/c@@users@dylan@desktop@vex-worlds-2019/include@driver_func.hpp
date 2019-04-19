#include "main.h"
#include "base_lib.hpp"
#include "mech_lib.hpp"

#define liftScorePosition 515
#define liftDescorePosition 544
#define liftUpPosition 120
#define liftDownPosition 0

#define poleAlignPower 50
#define lowerLiftDelay 200
#define backOutTime 300
#define backOutPower 100

#define pushInDelay 0
#define pushInTime 500
#define pushInPower 50
#define pushIn2Time 200
#define pushIn2Power 80
#define descoreDelay 80

#ifndef _DRIVER_FUNC_HPP_
#define _DRIVER_FUNC_HPP_

void scoreCap();
void descoreCap();
void directClimb();

#endif
