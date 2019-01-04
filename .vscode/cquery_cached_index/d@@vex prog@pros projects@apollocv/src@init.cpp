#include "main.h"

Controller controller;

const double joyDeadband = .08;

void initActTasks() {

  pros::Task driveActTask(drive::act, NULL, TASK_PRIORITY_DEFAULT,
                          TASK_STACK_DEPTH_DEFAULT, "Act Drive");

  pros::Task puncherActTask(puncher::act, NULL, TASK_PRIORITY_DEFAULT,
                            TASK_STACK_DEPTH_DEFAULT, "Act Puncher");

  pros::Task anglerActTask(angler::act, NULL, TASK_PRIORITY_DEFAULT,
                           TASK_STACK_DEPTH_DEFAULT, "Act Angler");

  pros::Task differentialActTask(differential::act, NULL, TASK_PRIORITY_DEFAULT,
                                 TASK_STACK_DEPTH_DEFAULT, "Act Diff");
}
