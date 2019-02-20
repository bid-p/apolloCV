#ifndef DRIVE_GUARD
#define DRIVE_GUARD

#include "okapi/api.hpp"

using namespace okapi;

namespace drive
{

enum driveStates
{
    notRunning = 'x',
    running = 'r',
    yield = 'y'
};

extern driveStates currState;

extern Motor driveR1, driveR2, driveL1, driveL2;

extern ChassisControllerIntegrated chassisController;

extern AsyncMotionProfileController profileController;

extern void update();

extern void act(void *);

} // namespace drive

extern void turnAngleVelocity(QAngle angle, double maxVelocity);

extern void turnAngleVelocity(QAngle angle, double maxVelocity, bool asynchronous);

extern void removePaths(std::string path1);
extern void removePaths(std::string path1, std::string path2);

#endif