#ifndef DIFFERENTIAL_GUARD
#define DIFFERENTIAL_GUARD

#include "okapi/api.hpp"

using namespace okapi;

namespace differential
{

enum differentialStates
{
  notRunning = 'x',
  liftHold = 'h',
  liftUp = '1',
  liftDown = '2',
  intakeIn = 'i',
  intakeOut = 'o',
  ballBrake = 't',
  ballDecel = 'd',
  intakeOutNY = 'n',
  targetTransition = 'c',
  yield = 'y',
};

extern differentialStates currState;

extern okapi::Motor diffLeft, diffRight;

extern pros::ADILineSensor lineL;
// extern pros::ADILineSensor lineR;

extern Potentiometer liftPot;

extern AverageFilter<5> liftPotfilter;

extern int liftVal;
extern int liftTarget;

extern void update();

extern void act(void *);

extern bool hasBall();

} // namespace differential

extern void runIntake(int speed);

#endif
