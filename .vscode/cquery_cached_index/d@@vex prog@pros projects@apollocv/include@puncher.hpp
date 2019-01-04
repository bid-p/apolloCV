#ifndef PUNCHER_GUARD
#define PUNCHER_GUARD
#include "okapi/api.hpp"

using namespace okapi;

namespace puncher {

typedef enum states {
  notRunning,
  shooting,
  cocking,
} tPuncherStates;

extern tPuncherStates currState;

extern char stateIndicator;

extern Motor puncher;

extern AsyncPosIntegratedController puncherController;

extern pros::ADILineSensor lineP;

extern bool isLoaded();

extern void update();
extern void act(void *);

} // namespace puncher

#endif
