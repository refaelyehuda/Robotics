/*
 * Main.cpp
 *
 *  Created on: Nov 18, 2015
 *      Author: colman
 */

#include "Map/Map.h"
#include "STC/STC.h"
#include "Settings.h"
#include "Robot.h"
#include "Plan/PlnObstacleAvoid.h"
#include "Manager.h"
#include <iostream>
#include <fstream>
#include <string>

int main() {

	// load all settings from configuration file
	Settings::loadConfFile();

	// Map Init
	Map map(Settings::MAP_RESOLUTION, Settings::ROBOT_SIZE);
	// Load map from image file
	const char* filePath = Settings::MAP_IMAGE_PATH.c_str();
	map.loadMapFromFile(filePath);

	// Map inflation
	map.inflateObstacles();
	map.buildFineGrid();
	map.buildCoarseGrid();

	// STC
	Position startPos;
	startPos.first = Settings::STC_START_POS_X;
	startPos.second = Settings::STC_START_POS_Y;
	STC stc(map, startPos);
	stc.printPath();
	map.addPathToFile(Settings::STC_IMAGE_PATH.c_str(),stc.getPath());

	// Connect and initialize robot
	Robot robot(Settings::HOST,Settings::PORT);

	//add way points to robot
	robot.setWayPoints(map.getWayPoints());
	PlnObstacleAvoid pln(&robot);
	Manager m(&robot, &pln);
	m.run();

	return 0;
}


