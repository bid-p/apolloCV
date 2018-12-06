#pragma once
#include "okapi/api.hpp"

extern okapi::Controller controller;
extern okapi::Motor driveR1, driveR2, driveL1, driveL2;
extern char getDriveState();
extern void abortDrive();
extern void updateDrive();
extern void driveAct();
