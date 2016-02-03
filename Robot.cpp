/*
 * Robot.cpp
 *
 *  Created on: Dec 31, 2015
 *      Author: user
 */

#include "Robot.h"
#include <math.h>

Robot::Robot(string ip, int port) :
	_pc(ip, port), _pp(&_pc), _lp(&_pc) {
	_pp.SetMotorEnable(true);
	_pp.SetOdometry(Settings::ROBOT_ODOMETRY_X, Settings::ROBOT_ODOMETRY_Y, Settings::ROBOT_ODOMETRY_YAW);

	for (int i = 0; i < 50; i++) {
		this->_pc.Read();
	}

}
void Robot::setSpeed(float xSpeed, float ySpeed) {
	_pp.SetSpeed(xSpeed, ySpeed);
}
/**
 * check if the space free in distance that we get
 */
bool Robot::freeInFront(float distance) {
	int i;
	for (i = 200; i < 400; i += 5)
		if (_lp[i] < distance)
			return false;

	return true;
}
/**
* check if the robot arrive to the next way point
*/
bool Robot::checkIfReachToDestination() {
	double radius = Settings::WAYPOINT_RADIUS;
	Position currentPosition = wayPoints[nextWayPointIndex]->getPosition();
	double y = mapToWorldY(currentPosition.first);
	double x = mapToWorldX(currentPosition.second);

	double cx = _pp.GetXPos();
	double cy = _pp.GetYPos();
	cout << cx << "," << cy << endl;

	if (nextWayPointIndex > wayPoints.size()) {
		return true;
	}

	//calc oclides destination between robot and radius
	if (sqrt(pow((x - cx), 2) + pow((y - cy), 2)) <= radius) {
		nextWayPointIndex++;
	}
	return false;
}
/**
 * cause for moving  the robot from way point to another way point
 */
void Robot::TryToReachNextWaypoint() {
	double x = _pp.GetXPos();
			double y = _pp.GetYPos();
			double yaw = _pp.GetYaw();
			//double deg = Settings::radiansToDeg(yaw);
			Node* nextWayPoint = wayPoints[nextWayPointIndex];
			Position nextWaypointPosition = nextWayPoint->getPosition();
			double cy = mapToWorldY(nextWaypointPosition.first);
			double cx = mapToWorldX(nextWaypointPosition.second);


			double deltaX = cx-x;
			double deltaY = cy-y;
			double s = atan2(deltaY , deltaX);

			float linearSpeed = Settings::LINEAR_SPEED;
			float radialSpeed = Settings::RADIAL_SPEED;

			cout << "Yaw is " << yaw << endl;
			cout << "S is " << s << endl;

			if (yaw >=0 && s >= 0)  {
				cout<<"Q I"<<endl;
				if (yaw > s + 0.1) {
					cout << "a" << endl;
					_pp.SetSpeed(0, -radialSpeed);
				} else if (yaw < s - 0.3) {
					cout << "b" << endl;
					_pp.SetSpeed(0, radialSpeed); // (radialSpeed old value was 0.3)
				} else {
					cout << "c" << endl;
					_pp.SetSpeed(linearSpeed, 0);
				}
			} else if (yaw < 0 && s < 0) {
				cout<<"Q II"<<endl;
				if (yaw > s + 0.3) {
					cout << "a" << endl;
					_pp.SetSpeed(0, -radialSpeed);
				} else if (yaw < s - 0.3) {
					cout << "b" << endl;
					_pp.SetSpeed(0, radialSpeed);
				} else {
					cout<<"Q IV"<<endl;
					cout << "c" << endl;
					_pp.SetSpeed(linearSpeed, 0);
				}
			} else if (yaw >=0 && s < 0) {
				cout<<"Q III"<<endl;
				if (M_PI - yaw + M_PI - abs(s) > yaw + abs(s)) {
					cout << "a" << endl;
					_pp.SetSpeed(0, -radialSpeed);
				} else if (M_PI - yaw + M_PI - abs(s) < yaw + abs(s)) {
					cout << "b" << endl;
					_pp.SetSpeed(0, radialSpeed);
				} else {
					cout << "c" << endl;
					_pp.SetSpeed(linearSpeed, 0);
				}
			} else if (yaw < 0 && s >= 0) {
				if (M_PI - abs(yaw) + M_PI - s > abs(yaw) + s) {
					cout << "a" << endl;
					_pp.SetSpeed(0, radialSpeed);
				} else if (M_PI - abs(yaw) + M_PI - s < abs(yaw) + s) {
					cout << "b" << endl;
					_pp.SetSpeed(0, -radialSpeed);
				} else {
					cout << "c" << endl;
					_pp.SetSpeed(linearSpeed, 0);
				}
			}

			cout << "next way point: " << nextWayPointIndex << " The point is: " << cx
					<< "," << cy << endl;

}

const vector<Node*>& Robot::getWayPoints() const {
	return wayPoints;
}

void Robot::setWayPoints(const vector<Node*>& wayPoints) {
	this->wayPoints = wayPoints;
	nextWayPointIndex = 0;
}

double Robot::mapToWorldX(int x) {
	return (x - (550 / 2)) * Settings::MAP_RESOLUTION;
}
double Robot::mapToWorldY(int y) {
	return -(y - (380 / 2)) * Settings::MAP_RESOLUTION;
}

double Robot::WorldTomapX(int x) {
	return (x / Settings::MAP_RESOLUTION) + (550 / 2);

}
double Robot::WorldTomapY(int y) {
	return -((y / Settings::MAP_RESOLUTION) - (380 / 2));
}

Robot::~Robot() {
	// TODO Auto-generated destructor stub
}
