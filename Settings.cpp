/*
 * Settings.cpp
 *
 *  Created on: Jan 4, 2016
 *      Author: colman
 */

#include "Settings.h"

/* Variables Definitions */

Configuration* Settings::cfg;
const char* Settings::scope;
const char* Settings::configFile;
string Settings::HOST;
int Settings::PORT = 0;
float Settings::ROBOT_SIZE;
float Settings::MAP_RESOLUTION;
int Settings::MAP_WIDTH;
int Settings::MAP_HEIGHT;
string Settings::MAP_IMAGE_PATH;
int Settings::STC_START_POS_X;
int Settings::STC_START_POS_Y;
string Settings::STC_IMAGE_PATH;
float Settings::INFLATION_RADIUS_FACTOR;
float Settings::SAFE_DISTANCE;
int Settings::ROBOT_ODOMETRY_X;
int Settings::ROBOT_ODOMETRY_Y;
float Settings::ROBOT_ODOMETRY_YAW;
float Settings::WAYPOINT_RADIUS;
float Settings::LINEAR_SPEED;
float Settings::RADIAL_SPEED;

/* Methods Implementations */

void Settings::loadConfFile() {
	cfg = Configuration::create();
	scope = "";
	configFile = "Settings.cfg";

	try {
		cfg->parse(configFile);
		HOST = cfg->lookupString(scope, "HOST");
		PORT = cfg->lookupInt(scope, "PORT");
		ROBOT_SIZE = cfg->lookupFloat(scope, "ROBOT_SIZE");
		MAP_RESOLUTION = cfg->lookupFloat(scope, "MAP_RESOLUTION");
		MAP_WIDTH = cfg->lookupInt(scope, "MAP_WIDTH");
		MAP_HEIGHT = cfg->lookupInt(scope, "MAP_HEIGHT");
		MAP_IMAGE_PATH = cfg->lookupString(scope, "MAP_IMAGE_PATH");
		STC_IMAGE_PATH = cfg->lookupString(scope, "STC_IMAGE_PATH");
		STC_START_POS_X = cfg->lookupInt(scope, "STC_START_POS.X");
		STC_START_POS_Y = cfg->lookupInt(scope, "STC_START_POS.Y");
		INFLATION_RADIUS_FACTOR = cfg->lookupFloat(scope, "INFLATION_RADIUS_FACTOR");
		SAFE_DISTANCE = cfg->lookupFloat(scope, "SAFE_DISTANCE");
		ROBOT_ODOMETRY_X = cfg->lookupInt(scope, "ROBOT_ODOMETRY.X");
		ROBOT_ODOMETRY_Y = cfg->lookupInt(scope, "ROBOT_ODOMETRY.Y");
		ROBOT_ODOMETRY_YAW = cfg->lookupFloat(scope, "ROBOT_ODOMETRY.YAW");
		WAYPOINT_RADIUS = cfg->lookupFloat(scope, "WAYPOINT_RADIUS");
		LINEAR_SPEED = cfg->lookupFloat(scope, "LINEAR_SPEED");
		RADIAL_SPEED = cfg->lookupFloat(scope, "RADIAL_SPEED");

	} catch (const ConfigurationException & ex) {
		cerr << ex.c_str() << endl;
		cfg->destroy();
	}
	cfg->destroy();
}

Settings::Settings() {}

Settings::~Settings() {}

