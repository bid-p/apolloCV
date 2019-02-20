#include "main.h"

using namespace okapi;

ControllerButton liftUpBtn = controller[ControllerDigital::A];
ControllerButton liftDownBtn = controller[ControllerDigital::Y];
ControllerButton intakeInBtn = controller[ControllerDigital::R1];
ControllerButton intakeOutBtn = controller[ControllerDigital::R2];

ControllerButton liftHoldBtn = controller[ControllerDigital::B];

namespace differential
{
differentialStates currState;

Motor diffLeft(DIFF_L, true, AbstractMotor::gearset::green);
Motor diffRight(DIFF_R, false, AbstractMotor::gearset::green);

Timer ballBrakeTimer;
pros::ADILineSensor line(SPORT_INTAKE);

Potentiometer liftPot(SPORT_LIFT);
AverageFilter<5> liftPotFilter;

int liftVal;

int liftTarget;

bool hasBall()
{
    if (line.get_value() < 2400)
    {
        reutrn true;
    }
    return false;
}

void update()
{
    liftVal = liftPotFilter.filter(liftPot.get());

    if (currState == intakeIn && !puncher::isLoader() && hasBall())
    {
        currentState = ballDecel;
    }
    if (currState == ballDecel && puncher::isLoaded())
    {
        currState = intakeIn;
    }
    if (currState == intakeIn && puncher::isLoaded())
}
} // namespace differential