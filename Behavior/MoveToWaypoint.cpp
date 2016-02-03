/*
 * MoveForward.cpp
 *
 *  Created on: Dec 31, 2015
 *      Author: user
 */

#include "MoveToWaypoint.h"

MoveToWaypoint::MoveToWaypoint(Robot* robot):Behavior(robot) {
	// TODO Auto-generated constructor stub
}

bool MoveToWaypoint::startCond()
{
	return _robot->freeInFront(Settings::SAFE_DISTANCE);
}

bool MoveToWaypoint::stopCond()
{
    return _robot->checkIfReachToDestination() || !_robot->freeInFront(Settings::SAFE_DISTANCE);
}

void MoveToWaypoint::action()
{
	_robot->TryToReachNextWaypoint();
}

MoveToWaypoint::~MoveToWaypoint() {
	// TODO Auto-generated destructor stub

}
