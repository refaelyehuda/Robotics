/*
 * Behavior.cpp
 *
 *  Created on: Dec 31, 2015
 *      Author: user
 */

#include "Behavior.h"

Behavior::Behavior(Robot* robot) {
	// TODO Auto-generated constructor stub
	_robot = robot;
	_sizeOfNext = 0;
	_next = NULL;
}
bool Behavior::addNext(Behavior* beh)
{
	Behavior** _save = _next;
	int i;
	_next = new Behavior*[_sizeOfNext+1];
	if(!_next)
	{
		_next = _save;
		return false;
	}
	_sizeOfNext++;
	for(i=0;i<_sizeOfNext-1;i++)
		_next[i] = _save[i];
	_next[i] = beh;
	delete []_save;
	return true;
}
Behavior* Behavior:: getNext()
{
	int i;
	for(i=0;i<_sizeOfNext;i++)
		if(_next[i]->startCond())
			return _next[i];

	return NULL;
}
Behavior::~Behavior() {
	// TODO Auto-generated destructor stub
	delete [] _next;
}
