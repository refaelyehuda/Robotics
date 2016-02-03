/*
 * Manager.cpp
 *
 *  Created on: Jan 7, 2016
 *      Author: user
 */

#include "Manager.h"

Manager::Manager(Robot* robot, Plan* plan) {
	_robot= robot;
	_plan = plan;
}
void Manager::run()
{
	Behavior* currBeh = _plan->getStart();
	_robot->Read();
	while(currBeh)
	{
		_robot->Read();
		while(!(currBeh->stopCond()))
		{
			currBeh->action();
			_robot->Read();
		}
		currBeh = currBeh->getNext();
	}


}
Manager::~Manager() {
	// TODO Auto-generated destructor stub

}
