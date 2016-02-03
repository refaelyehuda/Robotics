/*
 * MoveForward.cpp
 *
 *  Created on: Dec 31, 2015
 *      Author: user
 */

#include "AvoidObstacle.h"

AvoidObstacle::AvoidObstacle(Robot* robot):Behavior(robot) {

}
bool AvoidObstacle::startCond()
{
	return !_robot->freeInFront(Settings::SAFE_DISTANCE);
}
bool AvoidObstacle::stopCond()
{
	return _robot->freeInFront(Settings::SAFE_DISTANCE);
}
void AvoidObstacle::action()
{
	_robot->setSpeed(0.0,Settings::RADIAL_SPEED);
}

AvoidObstacle::~AvoidObstacle() {
	// TODO Auto-generated destructor stub

}
