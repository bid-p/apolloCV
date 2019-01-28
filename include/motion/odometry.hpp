#ifndef ODOM_GUARD
#define ODOM_GUARD
#include "okapi/api.hpp"
#include <tuple>
#include "subsystems/drive.hpp"

using namespace okapi;

namespace odometry
{

extern QLength currX;
extern QLength currY;
extern QAngle currAngle;

extern void init();

extern void calculate();

extern void run(void *);

extern void printPosition(void *);
} // namespace odometry

#endif