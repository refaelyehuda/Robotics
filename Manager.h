/*
 * Manager.h
 *
 *  Created on: Jan 7, 2016
 *      Author: user
 */

#ifndef MANAGER_H_
#define MANAGER_H_
#include "Robot.h"
#include "Plan/Plan.h"
#include "Behavior/Behavior.h"
/**
 * this class run the behaviors
 */
class Manager {
	Robot* _robot;
	Plan* _plan;

public:
	Manager(Robot* robot, Plan* plan);
	void run();
	virtual ~Manager();
};

#endif /* MANAGER_H_ */
