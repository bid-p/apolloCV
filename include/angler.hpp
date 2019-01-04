#ifndef ANGLER_GUARD
#define ANGLER_GUARD
#include "okapi/api.hpp"

using namespace okapi;

namespace angler {

typedef enum states {
  notRunning,
  closeMid,
  closeHigh,
  far1Mid,
  far1High,
  far2Mid,
} tAnglerStates;

extern tAnglerStates currState;

extern Motor angler;

extern AsyncPosIntegratedController angleController;

extern char stateIndicator;

extern void update();

extern void act(void *);

} // namespace angler

#endif
