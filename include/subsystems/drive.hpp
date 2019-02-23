#ifndef DRIVE_GUARD
#define DRIVE_GUARD

#include "okapi/api.hpp"
#include "motion/adaptivepurepursuit.hpp"

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

extern pathfollowing::AdaptivePurePursuit appc;

extern void update();

extern void act(void *);

} // namespace drive

extern void turnAngleVel(QAngle angle, double maxVel);

extern void turnAngleVel(QAngle angle, double maxVel, bool async);

extern void turnAngleVel(QAngle angle, double maxVel, bool odom, bool async);

extern void removePaths(std::string path1);
extern void removePaths(std::string path1, std::string path2);

#endif