#ifndef MACRO_GUARD
#define MACRO_GUARD
#include "okapi/api.hpp"

using namespace okapi;

namespace macro
{

enum macroStates
{
  none = 'x',
  singleShot = 's',
  doubleShotNear = 'n',
  doubleShotFar = 'f',
  anglerCH = '1',
  anglerMH = '2',
  anglerFM = '3',
  anglerFH = '4'
};

extern macroStates currState;

extern void update();

extern void act(void *);

} // namespace macro

#endif
