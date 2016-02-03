/*
 * PlnObstacleAvoid.cpp
 *
 *  Created on: Jan 7, 2016
 *      Author: user
 */

#include "PlnObstacleAvoid.h"
#include "../Behavior/AvoidObstacle.h"
#include "../Behavior/MoveToWaypoint.h"
PlnObstacleAvoid::PlnObstacleAvoid(Robot* robot) {
	//Creating behaviors
	_behaviors[0] = new AvoidObstacle(robot);
	_behaviors[1] = new MoveToWaypoint(robot);
	//Connecting behaviors
	_behaviors[0]->addNext(_behaviors[1]);
	_behaviors[1]->addNext(_behaviors[0]);
	_start = _behaviors[1];

}

PlnObstacleAvoid::~PlnObstacleAvoid() {
	for(int i=0;i<2;i++)
			delete []_behaviors[i];
}
