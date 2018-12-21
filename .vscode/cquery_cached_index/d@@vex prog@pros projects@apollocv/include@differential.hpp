#pragma once
#include "okapi/api.hpp"

extern okapi::Motor diffLeft;
extern okapi::Motor diffRight;

extern char getDiffState();
extern void abortDiff();
extern void updateDiff();
extern void diffAct();

extern void runIntake(int speed);

extern pros::ADILineSensor lineL;
extern pros::ADILineSensor lineR;

extern pros::ADILineSensor lineP;

extern bool hasBall();
extern bool isLoaded();
