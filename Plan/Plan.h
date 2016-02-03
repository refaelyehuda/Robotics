/*
 * Plan.h
 *
 *  Created on: Jan 7, 2016
 *      Author: user
 */

#ifndef PLAN_H_
#define PLAN_H_
#include "../Behavior/Behavior.h"


class Plan {
protected:
	Behavior* _start;
public:
	Plan();
	virtual Behavior* getStart(){return _start;}
	virtual ~Plan();
};

#endif /* PLAN_H_ */
