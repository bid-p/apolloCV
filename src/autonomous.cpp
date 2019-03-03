#include "main.h"

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous()
{
    pros::Task odometryPrint(odometry::printPosition, nullptr, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Position Print --> Screen");

    drive::currState = drive::driveStates::yield;
    differential::currState = differential::differentialStates::yield;
    puncher::currState = puncher::puncherStates::yield;
    angler::currState = angler::anglerStates::yield;

    drive::chassisController.setBrakeMode(AbstractMotor::brakeMode::brake);

    switch (autonRoutine) // Executes specific routine based on auton selector.
    {
    case notSelected:
        break;
    case progSkills:
        executeProgSkills();
        break;

    case redNear1:
        executeRedNear1();
        break;

    case redNear2:
        executeRedNear2();
        break;

    case redFar1:
        executeRedFar1();
        break;

    case redFar2:
        executeRedFar2();
        break;

    case blueNear1:
        executeBlueNear1();
        break;

    case blueNear2:
        executeBlueNear2();
        break;

    case blueFar1:
        executeBlueFar1();
        break;

    case blueFar2:
        executeBlueFar2();
        break;
    }

    // turnAngleVel(90_deg, 100, true, false);

    // turnAngleVel(270_deg, 100, true, false);

    // turnAngleVel(180_deg, 100, true, false);

    // turnAngleVel(0_deg, 100, true, false);

    // executeProgSkills();

    odometry::init();
    odometry::resetAngle(90_deg);
    odometry::currX = 12_in;
    odometry::currY = 96_in;

    path::Line A1(
        {13.25_in, 96_in},
        {52.25_in, 120_in},
        200,
        200);

    // path::Bezier A1(
    //     {path::Point{12_in, 96_in},
    //      path::Point{42_in, 162_in},
    //      path::Point{42_in, 30_in},
    //      path::Point{72_in, 96_in}},
    //     200,
    //     200);

    drive::appc.setPath(&A1);
    appcWUS();

    // turnAngleVel(3600_deg, 100);
    // lv_obj_clean(lv_scr_act());
}
