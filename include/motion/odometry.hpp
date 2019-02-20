#ifndef ODOM_GUARD
#define ODOM_GUARD

#include "okapi/api.hpp"
#include "subsystems/drive.hpp"

using namespace okapi;

namespace odometry
{

extern QLength currX;
extern QLength currY;
extern QAngle currAngle;
extern ADIEncoder rightEnc;
extern ADIEncoder leftEnc;

extern double rightEncLast;
extern double leftEncLast;

extern void init();

extern void calculate();

extern void run(void *);

extern void resetAngle(QAngle angle);

extern void printCurrPosition(void *);
} // namespace odometry

#endif