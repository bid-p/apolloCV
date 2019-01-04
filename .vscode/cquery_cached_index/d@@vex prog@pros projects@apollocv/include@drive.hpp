#ifndef DRIVE_GUARD
#define DRIVE_GUARD

#include "okapi/api.hpp"
using namespace okapi;

namespace drive {

typedef enum states {
  notRunning,
  running,
} tDriveStates;

extern tDriveStates currState;

extern char stateIndicator;

extern Motor driveR1, driveR2, driveL1, driveL2;
extern ChassisControllerIntegrated chassisController;
extern AsyncMotionProfileController profileController;

extern void update();
extern void act(void *);

} // namespace drive

extern void turnAngleVel(QAngle angle, double maxVel);

#endif
