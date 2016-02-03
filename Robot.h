/*
 * Robot.h
 *
 *  Created on: Dec 31, 2015
 *      Author: user
 */

#ifndef ROBOT_H_
#define ROBOT_H_

#include "Settings.h"
#include <libplayerc++/playerc++.h>
using namespace PlayerCc;
#include "STC/Node.h"
#include <vector>
#include <string>

class Robot {
public:
	PlayerClient _pc;
	Position2dProxy _pp;
	LaserProxy _lp;
	vector<Node *>  wayPoints;
	int nextWayPointIndex;
public:
	Robot(string ip, int port);
	void Read(){_pc.Read();}
	void setSpeed(float xSpeed, float ySpeed);
	/**
	 * check if the space free in distance that we get
	 */
	bool freeInFront(float distance);
	/**
	 * check if the robot arrive to the next way point
	 */
	bool checkIfReachToDestination();
	/**
	 * cause for moving  the robot from way point to another way point
	 */
	void TryToReachNextWaypoint();
	virtual ~Robot();
	const vector<Node*>& getWayPoints() const;
	void setWayPoints(const vector<Node*>& wayPoints);
	/**
	 * convert points from map to simulation and vice versa
	 */
	double mapToWorldX(int x);
	double mapToWorldY(int y);
	double WorldTomapX(int x);
	double WorldTomapY(int y);
};

#endif /* ROBOT_H_ */
