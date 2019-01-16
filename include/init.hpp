#ifndef INIT_GUARD
#define INIT_GUARD

#include "api.h"
#include "okapi/api.hpp"

using namespace okapi;

extern Controller controller;

extern const double joyDeadband;

void waitUntilSettled(okapi::AbstractMotor &motor);

extern pros::Task driveActTask;
extern pros::Task puncherActTask;
extern pros::Task anglerActTask;
extern pros::Task differentialActTask;

extern void initActTasks();

extern void updateFunc(void *);

#endif
