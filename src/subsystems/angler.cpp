#include "main.h"

using namespace okapi;

namespace angler
{

anglerStates currState;

pros::Vision vision(VISION, pros::E_VISION_ZERO_CENTER);

int target;

Motor angler(ANGLE_CHANGER, true, AbstractMotor::gearset::green);

const double kP = 0;
const double kI = 0;
const double kD = 0;

IterativePosPIDController anglerController = IterativeControllerFactory::posPID(kP, kI, kD, 0, std::make_unique<AverageFilter<5>>());

void update()
{
}

void act(void *)
{
    while (true)
    {
        switch (currState)
        {
        // Turn off Angler
        case notRunning:
            anglerController.flipDisable(true);
            angler.setBrakeMode(AbstractMotor::brakeMode::coast);
            angler.moveVoltage(0);
            break;
        // Set Angler position to a given target
        case toTarget:
            // angler::vision.set_led(COLOR_RED);
            anglerController.flipDisable(true);
            angler.moveAbsolute(target, 600);
            // angler::vision.set_led(COLOR_ANTIQUE_WHITE);
            break;
        // Essentially a PID hold but without current use
        // by shorting the motor terminals.
        case brake:
            anglerController.flipDisable(true);
            angler.setBrakeMode(AbstractMotor::brakeMode::hold);
            angler.moveVoltage(0);
            break;

        case autoAim:
            anglerController.flipDisable(false);
            if (alliance == red)
            {
                // TODO: Add vision code
            }
            if (alliance == blue)
            {
                // TODO: Add vision code
            }
            break;
        // yield control of the angler to the macro
        // state machine so it can use the angler motor.
        case yield:
            anglerController.flipDisable(true);
            break;
        }
        pros::delay(10);
    }
}
} // namespace angler