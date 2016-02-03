/*
 * Map.h
 *
 *  Created on: Nov 18, 2015
 *      Author: colman
 */

#ifndef MAP_H_
#define MAP_H_
#include "../Settings.h"
#include "../STC/Node.h"
#include "lodepng.h"
#include <vector>
using namespace std;
typedef vector<vector<bool> > Grid;
class Map {
private:
	vector<unsigned char> image;
	vector<vector<Node *> > gridGraph;
	Grid map;
	Grid inflateMap;
	//original Map size
	unsigned int mapWidth;
	unsigned int mapHeight;
	//grid Map size
	unsigned int fineMapWidth;
	unsigned int fineMapHeight;
	//coarse Map size
	unsigned int coarseMapWidth;
	unsigned int coarseMapHeight;
	float mapResolution;
	float robotSize;
	//size of the robot in pixels
	int robotSizeInCells;
	//the inflation of the map
	int inflationRadius;
	Grid fineGrid; // each cell in the size of the robot
	Grid coarseGrid; // each cell in the size 2x2 of the fine grid cell
	/**
	 * check if we have an Obstacle in  specific cell
	 */
	bool checkIfCellIsOccupied(int i, int j);
	/**
	 * check if there is  Obstacles around i,j
	 */
	void inflate(int i , int j);
	/**
	 * draw line between two way points
	 */
	void drawline(int x1, int y1, int x2, int y2, int r, int g, int b);
	/**
	 * add way points to  the vector points and draw line between the way points
	 */
	void addWayPoint(int x1, int y1, int x2, int y2, int r, int g, int b);

public:
	vector<Node *>  forwardPath;
	vector<Node *>  wayPoints;
	/**
	 * constructor
	 */
	Map(float mapResolution, float robotSize);
	/**
	 * load map from file
	 */
	void loadMapFromFile(const char* filePath);
	void addPathToFile(const char* filePath ,vector<Node *> path);
	/**
	 * inflate the Obstacles in the  map
	 */
	void inflateObstacles();
	void printMap() const;
	void printGrid(const Grid &grid) const;
	vector<vector<bool> > getInflateMap();
	/**
	 * take the real map and convert each cell to the robot size
	 */
	void buildFineGrid();
	/**
	 * take the fine grid map and convert each cell to the robot size *2
	 */
	void buildCoarseGrid();
	const Grid& getFineGrid() const;
	const Grid& getCoarseGrid()const;
	const vector<vector<Node*> >& getGridGraph() const;
	const vector<Node*>& getWayPoints() const ;
	virtual ~Map();
};

#endif /* MAP_H_ */
