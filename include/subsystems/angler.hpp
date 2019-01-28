#ifndef ANGLER_GUARD
#define ANGLER_GUARD
#include "okapi/api.hpp"

using namespace okapi;

namespace angler
{

enum anglerStates
{
  notRunning = 'x',
  toTarget = 't',
  brake = 'b',
  autoAim = 'a',
  yield = 'y',
};

extern pros::Vision vision;

extern anglerStates currState;

extern int target;

extern Motor angler;

extern const double kP;
extern const double kI;
extern const double kD;

extern IterativePosPIDController anglerController;

extern char stateIndicator;

extern void update();

extern void act(void *);

} // namespace angler

#endif
