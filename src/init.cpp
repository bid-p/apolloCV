#include "main.h"

Controller controller;

const double joyDeadband = .08;

void waitUntilSettled(okapi::AbstractMotor &motor)
{
  auto settledUtil = SettledUtilFactory::create();

  while (
      !settledUtil.isSettled(motor.getTargetPosition() - motor.getPosition()))
  {
    pros::delay(10);
  }
}

void updateFunc(void *)
{
  while (true)
  {
    drive::update();
    differential::update();
    puncher::update();
    angler::update();

    pros::delay(5);
  }
}

void initActTasks()
{

  pros::Task driveActTask(drive::act, NULL, TASK_PRIORITY_DEFAULT,
                          TASK_STACK_DEPTH_DEFAULT, "Act Drive");

  pros::Task puncherActTask(puncher::act, NULL, TASK_PRIORITY_DEFAULT,
                            TASK_STACK_DEPTH_DEFAULT, "Act Puncher");

  pros::Task anglerActTask(angler::act, NULL, TASK_PRIORITY_DEFAULT,
                           TASK_STACK_DEPTH_DEFAULT, "Act Angler");

  pros::Task differentialActTask(differential::act, NULL, TASK_PRIORITY_DEFAULT,
                                 TASK_STACK_DEPTH_DEFAULT, "Act Diff");

  pros::Task macroActTask(macro::act, NULL, TASK_PRIORITY_DEFAULT,
                          TASK_STACK_DEPTH_DEFAULT, "Act Macro");

  pros::Task updateTask(updateFunc, NULL, TASK_PRIORITY_DEFAULT,
                        TASK_STACK_DEPTH_DEFAULT, "Update");
}

extern void states();

extern void autonStates();
