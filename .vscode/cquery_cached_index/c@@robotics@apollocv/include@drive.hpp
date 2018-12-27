#pragma once
#include "okapi/api.hpp"
using namespace okapi;
extern okapi::Controller controller;
extern okapi::Motor driveR1, driveR2, driveL1, driveL2;
extern ChassisControllerIntegrated chassisController;
extern AsyncMotionProfileController profileController;

extern char getDriveState();
extern void abortDrive();
extern void updateDrive();
extern void driveAct();
extern void turnAngleVel(QAngle angle, double maxVel);
