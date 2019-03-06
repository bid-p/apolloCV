#include "main.h"
// #include "config.hpp"
// #include "adaptivepurepursuit.hpp"
// #include "drive.hpp"

namespace pathfollowing
{
AdaptivePurePursuit::AdaptivePurePursuit(
	std::unique_ptr<okapi::IterativePosPIDController> straight,
	std::unique_ptr<okapi::IterativePosPIDController> turn,
	int lookahead, double lookaheadKf) : straightController(std::move(straight)),
										 turnController(std::move(turn)),
										 mainLookahead(lookahead),
										 lookahead(lookahead),
										 lookaheadKf(lookaheadKf),
										 direction(1),
										 angleTarget(0_deg),
										 distanceSettledUtil(SettledUtilFactory::create(2, 0.2, 50_ms)),
										 angularSettledUtil(SettledUtilFactory::create(9999, 0.05, 50_ms)),
										 _isSettled(false),
										 isLooping(true),
										 taskHandle(nullptr)

{
	// i commented this out because I think if it's globally constructed it might gay?
	// it's okay though i added a call to this in initiailize
	// startThread();
}

void AdaptivePurePursuit::setPath(path::Path *path)
{
	this->path = path;
	int look = path->getLookahead();
	lookahead = (look < 0) ? mainLookahead : look;
}

void AdaptivePurePursuit::setLookahead(int lookahead)
{
	this->lookahead = lookahead;
}
/*
this is manas gay angle math
void AdaptivePurePursuit::loop()
{
	using namespace okapi;

	path::Point robotPosition = {odometry::currX, odometry::currY};

	path::PointAndDistance closestPointAndDistance = path->getClosestPointAndDistance(robotPosition);

	int newLookahead = lookahead - (closestPointAndDistance.distance.convert(inch) * lookaheadKf);
	// if (closestPointAndDistance.distance.convert(inch) == 0) {
	// 	newLookahead = lookahead;
	// } else {
	// 	newLookahead = (double) lookahead / (closestPointAndDistance.distance.convert(inch) * lookaheadKf);
	// }
	newLookahead = (newLookahead < 0) ? 1 : newLookahead;
	//newLookahead = (newLookahead > lookahead) ? lookahead : newLookahead;

	int requiredPosition = closestPointAndDistance.point.t;
	target = path->pointAt(requiredPosition + newLookahead);

	double distTolookaheadPoint =
		sqrt(pow(target.x.convert(inch) - robotPosition.x.convert(inch), 2) + pow(target.y.convert(inch) - robotPosition.y.convert(inch), 2));

	straightController->setTarget(0);

	double forwardPower = straightController->step(-distTolookaheadPoint);
	// QAngle bearing =
	// 	std::atan2((this->target.x.convert(inch) - robotPosition.x.convert(inch)),
	// 			   (this->target.y.convert(inch) - robotPosition.y.convert(inch))) *
	// 	radian;
	QAngle bearing =
		std::atan2((this->target.x.convert(inch) - robotPosition.x.convert(inch)),
				   (this->target.y.convert(inch) - robotPosition.y.convert(inch))) *
		radian;

	direction = 1;

	QAngle currBearingAngle = std::atan2(sin(odometry::currAngle.convert(radian)), cos(odometry::currAngle.convert(radian))) * radian;

	double angleError = bearing.convert(radian) - currBearingAngle.convert(radian);
	angleError = std::atan2(sin(angleError), cos(angleError));

	//if (target.t == path->getResolution())
	//{
	if (angleError * 180.0 / PI > 90)
	{
		angleError -= PI;
		// angleError *= -1;
		direction *= -1;
	}
	else if (angleError * 180.0 / PI < -90)
	{
		angleError += PI;
		// angleError *= -1;
		direction *= -1;
	}
	//}

	//turnController->setTarget(bearing.convert(degree));
	turnController->setTarget(0);

	// double turnPower = turnController->step(odometry::currAngle.convert(degree));
	// double turnPower = turnController->step(currHeading.convert(degree));
	//double turnPower = turnController->step(turnControllerPV.convert(degree));
	double turnPower = turnController->step(-angleError);

	printf("Bearing: %f, ", bearing.convert(degree));
	printf("angleError: %f, ", (angleError * 180.0 / PI));
	printf("Forward: %f, Turn: %f, ", forwardPower, turnPower);
	printf("Angle: %1.2f\n", currBearingAngle.convert(degree));

	drive::chassisController.driveVector(direction * forwardPower, turnPower); // TODO CHASSIS MODEL IN CONSTRUCTOR INSTEAD OF HERE
}*/

QAngle AdaptivePurePursuit::calculateAngleError(QAngle pV, QAngle setpoint)
{
	if (setpoint.convert(radian) < PI && pV.convert(radian) > PI)
	{
		pV = radian * (pV.convert(radian) - PI * 2);
	}
	double error = setpoint.convert(radian) - pV.convert(radian);
	return radian * (error > PI ? error - PI * 2 : error);
}

void AdaptivePurePursuit::loop()
{
	using namespace okapi;

	path::Point robotPosition = {odometry::currX, odometry::currY};

	path::PointAndDistance closestPointAndDistance = path->getClosestPointAndDistance(robotPosition);

	int newLookahead = lookahead - (closestPointAndDistance.distance.convert(inch) * lookaheadKf);
	// if (closestPointAndDistance.distance.convert(inch) == 0) {
	// 	newLookahead = lookahead;
	// } else {
	// 	newLookahead = (double) lookahead / (closestPointAndDistance.distance.convert(inch) * lookaheadKf);
	// }
	newLookahead = (newLookahead < 0) ? 1 : newLookahead;
	//newLookahead = (newLookahead > lookahead) ? lookahead : newLookahead;

	int requiredPosition = closestPointAndDistance.point.t;
	target = path->pointAt(requiredPosition + newLookahead);

	double distTolookaheadPoint =
		sqrt(pow(target.x.convert(inch) - robotPosition.x.convert(inch), 2) + pow(target.y.convert(inch) - robotPosition.y.convert(inch), 2));

	straightController->setTarget(0);

	double forwardPower = straightController->step(-distTolookaheadPoint);
	// QAngle bearing =
	// 	std::atan2((this->target.x.convert(inch) - robotPosition.x.convert(inch)),
	// 			   (this->target.y.convert(inch) - robotPosition.y.convert(inch))) *
	// 	radian;
	QAngle bearing =
		std::atan2((this->target.x.convert(inch) - robotPosition.x.convert(inch)),
				   (this->target.y.convert(inch) - robotPosition.y.convert(inch))) *
		radian;

	// constrain to 0-2pi
	while (bearing.convert(radian) < 0)
	{
		bearing = radian * (bearing.convert(radian) + PI * 2);
	}
	// QAngle currBearingAngle = std::atan2(sin(odometry::currAngle.convert(radian)), cos(odometry::currAngle.convert(radian))) * radian;
	QAngle currBearingAngle = odometry::currAngle;

	double angleError = calculateAngleError(currBearingAngle, bearing).convert(radian);
	// angleError = std::atan2(sin(angleError), cos(angleError));

	//if (target.t == path->getResolution())
	//{
	direction = 1;
	if (angleError * 180.0 / PI > 90)
	{
		angleError -= PI;
		// angleError *= -1;
		direction *= -1;
	}
	else if (angleError * 180.0 / PI < -90)
	{
		angleError += PI;
		// angleError *= -1;
		direction *= -1;
	}
	//}

	//turnController->setTarget(bearing.convert(degree));
	turnController->setTarget(0);

	// double turnPower = turnController->step(odometry::currAngle.convert(degree));
	// double turnPower = turnController->step(currHeading.convert(degree));
	//double turnPower = turnController->step(turnControllerPV.convert(degree));
	double turnPower = turnController->step(-angleError);

	printf("Bearing: %f, ", bearing.convert(degree));
	printf("angleError: %f, ", (angleError * 180.0 / PI));
	printf("Forward: %f, Turn: %f, ", forwardPower, turnPower);
	printf("Angle: %1.2f\n", currBearingAngle.convert(degree));

	drive::chassisController.driveVector(direction * forwardPower, turnPower); // TODO CHASSIS MODEL IN CONSTRUCTOR INSTEAD OF HERE
}

path::Point AdaptivePurePursuit::getPointTarget()
{
	return target;
}

void AdaptivePurePursuit::checkIsSettled()
{
	// you should calculate distanceError and turnError inside of this function --> ok
	// oops sorry manas thought i was looking at a different function (ic)
	// update private bool isSettled logic here

	auto point = path->pointAt(path->getResolution());
	auto preFinalPoint = path->pointAt(path->getResolution() - 1);

	double finalAngleTarget = std::atan2(point.y.convert(okapi::inch) - preFinalPoint.y.convert(okapi::inch), point.x.convert(okapi::inch) - preFinalPoint.x.convert(okapi::inch));
	double angleError = atan2(sin(finalAngleTarget - odometry::currAngle.convert(okapi::radian)), cos(finalAngleTarget - odometry::currAngle.convert(okapi::radian)));

	double finalDistance = sqrt(pow((point.x.convert(okapi::inch) - odometry::currX.convert(okapi::inch)), 2) + pow((point.y.convert(okapi::inch) - odometry::currY.convert(okapi::inch)), 2));

	_isSettled = distanceSettledUtil.isSettled(finalDistance) && angularSettledUtil.isSettled(angleError * 180.0 / PI); // converted to degrees for ease of settle error, etc.
}

// bool AdaptivePurePursuit::isSettled()
// {
// 	path::Point endPoint = path->pointAt(path->getResolution());
// 	double distance = sqrt(pow(endPoint.x.convert(inch) - odometry::currX.convert(inch), 2) + pow(endPoint.y.convert(inch) - odometry::currY.convert(inch), 2));
// 	return (distance < 2);
// }

bool AdaptivePurePursuit::isSettled()
{
	return _isSettled;
}

void AdaptivePurePursuit::resetSettled()
{
	distanceSettledUtil.reset(); // that was me, checking API rn
	angularSettledUtil.reset();  // im just guessing this method exists not gonna lie

	_isSettled = false;
}

void AdaptivePurePursuit::waitUntilSettled(bool stopWhenSettled)
{
	while (isLooping && !_isSettled)
	{
		pros::delay(10);
	}

	resetSettled();

	// my code is so good it comments itself
	if (stopWhenSettled)
	{
		stop();
	}
}

void AdaptivePurePursuit::runPathAsync(path::Path *path)
{
	setPath(path);
	start();
}

void AdaptivePurePursuit::runPath(path::Path *path)
{
	runPathAsync(path);
	waitUntilSettled();
}

void AdaptivePurePursuit::setKf(double kf)
{
	this->lookaheadKf = kf;
}

void AdaptivePurePursuit::setStraightGains(double kP, double kI, double kD)
{
	straightController->setGains(kP, kI, kD, 0.0);
}

void AdaptivePurePursuit::setTurnGains(double kP, double kI, double kD)
{
	turnController->setGains(kP, kI, kD, 0.0);
}

void AdaptivePurePursuit::runLoop()
{
	while (true)
	{
		if (isLooping)
		{
			loop();
			checkIsSettled(); // updates internal boolean `isSettled` which is then exposed through getter bool isSettled();

			// if (drive::appc.isSettled())
			// {
			// 	looperoni = false;
			// }
		}
		else
		{
			resetSettled();
		}
		pros::delay(10);
	}
}

void AdaptivePurePursuit::trampoline(void *instance)
{ // we're literally just calling the runLoop function
	static_cast<AdaptivePurePursuit *>(instance)->runLoop();
}

void AdaptivePurePursuit::startThread()
{
	taskHandle = new pros::Task(trampoline, static_cast<void *>(this));
}

void AdaptivePurePursuit::stopThread()
{
	taskHandle->remove();
	delete taskHandle;
}

void AdaptivePurePursuit::stop()
{
	isLooping = false;
	drive::chassisController.stop(); // reEEEEEEEE this'll do for now, far too lazy to restructure ngl
	resetSettled();
}

void AdaptivePurePursuit::start()
{
	isLooping = true;
}

} // namespace pathfollowing