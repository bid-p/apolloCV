#include "main.h"

using namespace okapi;

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

//ControllerButton abortBtn = controller[ControllerDigital::Y];

void stop() { // there is no longer an abort button
	abortPuncher();
	abortDiff();
	abortDrive();
}

void states() {
	pros::lcd::print(1, "Drive state: %c | Drive temp: %i", getDriveState(), (int) driveR1.getTemperature());
	pros::lcd::print(2, "Puncher state: %c | Puncher temp: %i", getPuncherState(), (int) puncher.getTemperature());
	pros::lcd::print(3, "Puncher encoder: %i", (int) puncher.getPosition()); //pros::lcd::print(3, "Angle target: %i",(int) angleTarget);
	pros::lcd::print(4, "Angle state: %c | Angle temp: %i", getAngleState(), (int) angleChanger.getTemperature());
	pros::lcd::print(5, "Angle encoder: %i", (int) angleChanger.getPosition());
	pros::lcd::print(6, "Diff state: %c | Diff Left temp: %i", getDiffState(), (int) diffLeft.getTemperature());
	//pros::lcd::print(7, "Diff right temp: %i", (int) diffRight.getTemperature()); // this is redundant i think
	pros::lcd::print(7, "Macro state: %c", getMacroState());
}

void opcontrol() {
	pros::lcd::print(0, "Opcontrol");
	while (true) {
		states();

		updateDrive();
		updateDiff();
		updatePuncher();

		/*if(abortBtn.changedToPressed()) {
			stop();
		}*/

		driveAct();
		diffAct();
		puncherAct();
		pros::delay(10);
	}
}
