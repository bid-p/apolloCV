#ifndef MACRO_GUARD
#define MACRO_GUARD
#include "okapi/api.hpp"

using namespace okapi;

namespace macro
{

enum macroStates
{
  none = 'x',
  doubleShotNear = 'n',
  doubleShotFar = 'f',
  customShotDouble = 'd',
  customShotSingle = 's',
  anglerCH = '1',
  anglerMH = '2',
  anglerFM = '3',
  anglerFH = '4',
};

extern macroStates currState;

extern void update();

extern void act(void *);

} // namespace macro

extern void customShotCall(int target1, int target2);

extern void customShotCall(int target1);

#endif
