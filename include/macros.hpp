#ifndef MACRO_GUARD
#define MACRO_GUARD
#include "okapi/api.hpp"

using namespace okapi;

namespace macro
{

enum macroStates
{
  none = 'x',
  singleShot = '0',
  doubleShotNear = 'n',
  doubleShotFar = 'f',
  customShot = 'c',
  anglerCH = '1',
  anglerMH = '2',
  anglerFM = '3',
  anglerFH = '4',
};

extern macroStates currState;

extern void update();

extern void act(void *);

} // namespace macro

void customShotCall(int target1, int target2);

#endif
