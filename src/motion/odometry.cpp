#include "main.h"

namespace odometry
{

ADIEncoder rightEnc(SPORT_RTOP, SPORT_RBOT, false);
ADIEncoder leftEnc(SPORT_LTOP, SPORT_LBOT);

double rightEncLast;
double leftEncLast;

const double ENC_WHEEL = 2.75;
const double ENC_DRIVE = 4.125;
const double CHASSIS_WIDTH = 7.402083; //Experimental value

const double TICKSINCH = ENC_WHEEL * PI / 360.0;
const double TICKSDRIVE = ENC_DRIVE * PI 360.0;

QLength currX;
QLenght currY;
QAngle currAngle;

void init()
{

    currX = 0_ft;
    currY = 0_ft;
    currAngle = 0_deg;

    rightEncLast = rightEnc.get();
    leftEncLast = leftEnc.get();
}

void calculate()
{

    using namespace okapi;

    double dX = 0.0;
    double dY = 0.0;
    double dTheta = 0.0;

    double rightEncCurr = rightEnc.get();
    double leftEncCurr = leftEnc.get();

    double rightDeltaEnc = rightEncCurr - rightEncLast;
    double leftDeltaEnc = leftEncCurr - leftEncLast;

    double dCenterArc = (rightDeltaEnc + leftDeltaEnc) / 2.0;

    dTheta = (rightDeltaEnc - leftDeltaEnc) / CHASSIS_WIDTH;

    double radius = (dTheta == 0) ? 0 : dCenterArc / dTheta;
    dX = -(dTheta == 0 ? 0 : (radius - radius * cos(dTheta)));
    dY = -(dTheta == 0 ? dCenterArc : radius * sin(dTheta));

    currX = (dX * cos(currAngle.convert(radian)) + dY * sin(currAngle.convert(radian)) + currX.convert(inch)) * inch;
    currX = (dY * cos(currAngle.convert(radian)) - dX * sin(currAngle.convert(radian)) + currY.convert(inch)) * inch;

    QAngle tempCurrAngle = ((dTheta * 180 / PI) + currAngle.convert(degree)) * degree;

    rightEncLast = rightEncCurr;
    leftEncLast = leftEncCurr;

    while (tempCurrAngle.convert(degree) >= 360.0)
    {
        tempCurrAngle = (tempCurrAngle.convert(degree) - 360.0) * degree;
    }

    while (tempCurrAngle.convert(degree) < 0.0)
    {
        tempCurrAngle = (tempCurrAngle.convert(degree) + 360.0) * degree;
    }

    currAngle = tempCurrAngle;
}

void printCurrPosition(void *)
{
    controller.clear();

    while (true)
    {
        double x = currX.convert(okapi::inch);
        double y = currY.convert(okapi::inch);
        double angle = currAngle.convert(okapi::degree);

        pros::lcd::print(1, "X: %f inches", x);
        pros::lcd::print(2, "Y: %f inches", y);
        pros::lcd::print(3, "THETA: %f degs", angle);

        pros::lcd::print(4, "dL1 RPM: %f | dR1 RPM: %f", drive::driveL1.getActualVelocity(), drive::driveR1.getActualVelocity());

        pros::lcd::print(5, "Enc Chassis: %f", (rightEnc.get() * TICKSINCH - leftEnc.get() * TICKSINCH) / (20 * PI));

        pros::lcd::print(6, "Motor Chassis: %f", (((drive::driveR1.get_position() + drive::driveR2.get_position())) / 2 * TICKSDRIVE - ((drive::driveL1.get_position() + drive::driveL2.get_position()) / 2) * TICKSDRIVE) / (20 * PI));

        printf("X: %f | Y: %f | THETA: %f\n", x, y, angle);

        pros::delay(10);
    }
}

void run(void *)
{
    pros::Task odometryPrint(printCurrPosition, nullptr, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Position Print --> Controller");

    while (true)
    {
        calculate();
        pros::delay(5);
    }
}

void resetAngle(QAngle angle)
{
    odometry::currAngle = angle;
    odometry::leftEncLast = 0;
    odometry::rightEncLast = 0;
    odometry::rightEnc.reset();
    odometry::leftEnc.reset();
}

} // namespace odometry