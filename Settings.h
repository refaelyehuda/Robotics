/*
 * Settings.h
 *
 *  Created on: Jan 4, 2016
 *      Author: colman
 */

#ifndef SETTINGS_H_
#define SETTINGS_H_

#include <math.h>
#include <string>
#include <Configuration.h>
#include <iostream>

using namespace config4cpp;
using namespace std;

class Settings {
private:
	static Configuration* cfg;
	static const char* scope;
	static const char* configFile;

public:

	/** Connection Settings **/
	static string HOST; //host address
	static int PORT; //port

	/** Constants **/
	static float ROBOT_SIZE; //size of robot in meters
	static float MAP_RESOLUTION; //resolution of the map
	static int MAP_WIDTH; //map width in pixels
	static int MAP_HEIGHT; //map height in pixels
	static string MAP_IMAGE_PATH; //path of original map image in file system
	static int STC_START_POS_X; //X value of STC start position
	static int STC_START_POS_Y; //Y value of STC start position
	static string STC_IMAGE_PATH; //path of map + STC path image in file system
	static float INFLATION_RADIUS_FACTOR;
	static float SAFE_DISTANCE; //the distance from obstacle
	static int ROBOT_ODOMETRY_X;
	static int ROBOT_ODOMETRY_Y;
	static float ROBOT_ODOMETRY_YAW;
	static float WAYPOINT_RADIUS;
	static float LINEAR_SPEED;
	static float RADIAL_SPEED;

	/** Static Methods **/

	//load all static variables values from configuration file
	static void loadConfFile();

	//convert from degrees to radians
	static double degToRadians (double deg) {
		return (deg * M_PI) / 180;
	}

	//convert from radians to degrees
	static double radiansToDeg (double rad) {
		return (rad * 180) / M_PI;
	}

	Settings();
	virtual ~Settings();
};

#endif /* SETTINGS_H_ */
