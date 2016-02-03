/*
 * MoveForward.h
 *
 *  Created on: Dec 31, 2015
 *      Author: user
 */



#include "Behavior.h"
#include "../Robot.h"
#include "../Settings.h"

/**
 * this class configure functions for avoiding from obstacles
 */
class AvoidObstacle: public Behavior {
public:
	AvoidObstacle(Robot* robot);
	virtual bool startCond();
	virtual bool stopCond();
	virtual void action();
	virtual ~AvoidObstacle();
};


