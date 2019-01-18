#ifndef PUNCHER_GUARD
#define PUNCHER_GUARD
#include "okapi/api.hpp"

using namespace okapi;

namespace puncher
{

enum puncherStates
{
  notRunning = 'x',
  shooting = 's',
  cocking = 'c',
  yield = 'y'
};

extern puncherStates currState;

extern char stateIndicator;

extern Motor puncher;

extern AsyncPosIntegratedController puncherController;

extern pros::ADILineSensor lineP;

extern pros::ADILineSensor lineCock;

extern bool isLoaded();

extern void update();
extern void act(void *);

extern void puncherMacro();

} // namespace puncher

#endif
