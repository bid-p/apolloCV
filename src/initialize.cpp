#include "main.h"

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize()
{
    // pros::lcd::initialize();

    odometry::init();

    angler::vision.clear_led();

    pros::Task odometryTask(odometry::run, nullptr, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Odometry");

    autonSelector();

    // set all the states to not running by default
    drive::currState = drive::notRunning;
    angler::currState = angler::notRunning;
    puncher::currState = puncher::notRunning;
    differential::currState = differential::notRunning;
    macro::currState = macro::none;

    initProgSkills();
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}
