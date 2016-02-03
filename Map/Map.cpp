/*
 * Map.cpp
 *
 *  Created on: Nov 18, 2015
 *      Author: colman
 */

#include "Map.h"
#include <iostream>
/**
 * constructor
 */
Map::Map(float mapResolution, float robotSize) :
	mapResolution(mapResolution), robotSize(robotSize) {
	robotSizeInCells = robotSize / mapResolution;
	inflationRadius = Settings::INFLATION_RADIUS_FACTOR * robotSizeInCells;
	cout << "inflation radius " << inflationRadius << endl;

}
/**
 * load the map from file
 */
void Map::loadMapFromFile(const char* filePath) {
	lodepng::decode(image, mapWidth, mapHeight, filePath);
	fineMapWidth = mapWidth / robotSizeInCells;
	fineMapHeight = mapHeight / robotSizeInCells;
	//create grid graph for to storage the path
	gridGraph.resize(fineMapHeight);
	for (int k = 0; k < fineMapHeight; k++) {
		gridGraph[k].resize(fineMapWidth);
	}
	cout << "map size: " << mapWidth << "," << mapHeight << endl;

	map.resize(mapHeight);
	for (int i = 0; i < mapHeight; i++)
		map[i].resize(mapWidth);

	for (int i = 0; i < mapHeight; i++) {
		for (int j = 0; j < mapWidth; j++) {
			map[i][j] = checkIfCellIsOccupied(i, j);
		}
	}

}

/**
 * check if we have an Obstacle in  specific cell
 */
bool Map::checkIfCellIsOccupied(int i, int j) {
	int c = (i * mapWidth + j) * 4;
	int r = image[c];
	int g = image[c + 1];
	int b = image[c + 2];

	if (r == 0 && g == 0 && b == 0)
		return true;
	return false;
}

void Map::printMap() const {
	for (int i = 0; i < mapHeight; i++) {
		for (int j = 0; j < mapWidth; j++) {
			cout << (inflateMap[i][j] ? "*" : " ");
		}
		cout << endl;
	}
}

void Map::printGrid(const Grid &grid) const {
	int rows = grid.size();
	int cols = grid[0].size();

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			cout << (grid[i][j] ? "*" : " ");
		}
		cout << endl;
	}

	rows = coarseGrid.size();
	cols = coarseGrid[0].size();

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			cout << (coarseGrid[i][j] ? "*" : " ");
		}
		cout << endl;
	}

}
/**
 * inflate the Obstacles in the  map
 */
void Map::inflateObstacles() {

	inflateMap.resize(mapHeight);
	for (int i = 0; i < mapHeight; i++) {
		inflateMap[i].resize(mapWidth);
	}

	for (int i = 0; i < mapHeight; i++) {
		for (int j = 0; j < mapWidth; j++) {
			if (map[i][j]) {
				inflate(i, j);
			}
		}
	}

}

/**
 * check if there is  Obstacles around i,j
 */
void Map::inflate(int i, int j) {

	for (int k = i - inflationRadius; k < i + inflationRadius; k++) {
		for (int m = j - inflationRadius; m < j + inflationRadius; m++) {
			if (m < 0 || k < 0 || k >= mapHeight || m >= mapWidth) {
				continue;
			} else {
				// Mark this cell as occupied in inflateMap
				inflateMap[k][m] = true;
				// Draw black color in corresponding image
				int c = (k * mapWidth + m) * 4;
				image[c] = 0;
				image[c + 1] = 0;
				image[c + 2] = 0;

			}
		}
	}
}

vector<vector<bool> > Map::getInflateMap() {
	return inflateMap;
}


/**
 * take the real map and convert each cell to the robot size
 */
void Map::buildFineGrid() {

	int fineGridCells = mapHeight / robotSizeInCells;
	int fineGridWidth = mapWidth / robotSizeInCells;
	fineGrid.resize(fineGridCells);
	for (int i = 0; i < fineGridCells; i++) {
		fineGrid[i].resize(fineGridWidth);
	}

	int flag = false;

	for (int i = 0; i < fineGridCells; i++) {
		for (int j = 0; j < fineGridWidth; j++) {
			flag = false;
			for (int m = i * robotSizeInCells;
					m < i * robotSizeInCells + robotSizeInCells; m++) {
				for (int z = j * robotSizeInCells;
						z < j * robotSizeInCells + robotSizeInCells; z++) {
					if (inflateMap[m][z] == true) {
						flag = true;
						break;
					}
				}
			}
			fineGrid[i][j] = flag;
		}
	}

}

/**
 * take the fine grid map and convert each cell to the robot size *2
 */
void Map::buildCoarseGrid() {

	int fineGridCells = mapHeight / (robotSizeInCells * 2);
	coarseMapHeight = fineGridCells;
	int fineGridWidth = mapWidth / (robotSizeInCells * 2);
	coarseMapWidth = fineGridWidth;
	coarseGrid.resize(fineGridCells);
	for (int i = 0; i < fineGridCells; i++) {
		coarseGrid[i].resize(fineGridWidth);
	}

	int fleg = false;

	for (int i = 0; i < fineGridCells; i++) {
		for (int j = 0; j < fineGridWidth; j++) {
			fleg = false;
			for (int m = i * (robotSizeInCells * 2);
					m < i * (robotSizeInCells * 2) + (robotSizeInCells * 2);
					m++) {
				for (int z = j * (robotSizeInCells * 2);
						z < j * (robotSizeInCells * 2) + (robotSizeInCells * 2);
						z++) {
					if (inflateMap[m][z] == true) {
						fleg = true;
						break;
					}
				}
			}
			coarseGrid[i][j] = fleg;
		}
	}

}


/**
 * add way points to  the vector points and draw line between the way points
 */
void Map::addWayPoint(int x1, int y1, int x2, int y2, int r, int g, int b) {
	cout << "Way-point: " << "(" << x2 << "," << y2 << ")" <<endl;
	Node* node = new Node(x2, y2);
	wayPoints.push_back(node);
	drawline(x1, y1, x2, y2,  r,  g, b);
}

/**
 * draw line between two way points
 */
void Map::drawline(int x1, int y1, int x2, int y2, int r, int g, int b) {
	//check how we need to move on row or column

	//UP
	if (y1 < y2 && x1 == x2) {

		for (int m = y1; m < y2; m++) {
			int c = (x1 * mapWidth + m) * 4;
			image[c] = r;
			image[c + 1] = g;
			image[c + 2] = b;
		}
		//check how we need to move on row or column
		//DOWN
	} else if (y1 > y2 && x1 == x2) {
		for (int m = y2; m < y1; m++) {
			int c = (x1 * mapWidth + m) * 4;
			image[c] = r;
			image[c + 1] = g;
			image[c + 2] = b;
		}

		//check how we need to move on row or column
		//LEFT
	} else if (y1 == y2 && x1 > x2) {
		for (int m = x2; m < x1; m++) {
			int c = (m * mapWidth + y1) * 4;
			image[c] = r;
			image[c + 1] = g;
			image[c + 2] = b;
		}

		//check how we need to move on row or column
		//RIGHT
	} else if (y1 == y2 && x1 < x2) {
		for (int m = x1; m < x2; m++) {
			int c = (m * mapWidth + y1) * 4;
			image[c] = r;
			image[c + 1] = g;
			image[c + 2] = b;
		}
	}
};

/**
 * add the full path from STC to the map (red line)
 */
void Map::addPathToFile(const char* filePath, vector<Node *> path) {


	int location = -1; // 0 = going left (blue), 1 = going right (black), 2 = down (magenta), 3 = up (green)

	for (int z = 0; z < path.size()-1; z++) {
		int this_x = path[z]->getPosition().first;
		int this_y = path[z]->getPosition().second;

		int next_x = path[z+1]->getPosition().first;
		int next_y = path[z+1]->getPosition().second;

		//convert the row to the original map row that was read from the image
		next_x = ((next_x + 0.5) * robotSizeInCells * 2);
		//convert the row to the original map column that was read from the image
		next_y = ((next_y + 0.5) * robotSizeInCells * 2);

		////convert the row to the original map row that was read from the image
		this_x = ((this_x + 0.5) * robotSizeInCells * 2);
		////convert the row to the original map column that was read from the image
		this_y = ((this_y + 0.5) * robotSizeInCells * 2);

		//buttom right
		int x_br = this_x + (0.5 * robotSizeInCells);
		//convert the row to the original map column that was read from the image
		int y_br = this_y + (0.5 * robotSizeInCells);
		int c = (x_br * (mapWidth) + y_br) * 4;
		image[c] = 0;
		image[c + 1] = 255;
		image[c + 2] = 0;

		//buttom left
		int x_bl = this_x + (0.5 * robotSizeInCells);
		//convert the row to the original map column that was read from the image
		int y_bl = this_y - (0.5 * robotSizeInCells);
		c = (x_bl * (mapWidth) + y_bl) * 4;
		image[c] = 255;
		image[c + 1] = 0;
		image[c + 2] = 0;

		//top right
		int x_tr = this_x - (0.5 * robotSizeInCells);
		//convert the row to the original map column that was read from the image
		int y_tr = this_y + (0.5 * robotSizeInCells);
		c = (x_tr * (mapWidth) + y_tr) * 4;
		image[c] = 0;
		image[c + 1] = 0;
		image[c + 2] = 0;

		//top left
		int x_tl = this_x - (0.5 * robotSizeInCells);
		//convert the row to the original map column that was read from the image
		int y_tl = this_y - (0.5 * robotSizeInCells);
		c = (x_tl * (mapWidth) + y_tl) * 4;
		image[c] = 255;
		image[c + 1] = 0;
		image[c + 2] = 255;

		//check how we need to move on row or column
		//This is for going from left to right on the map
		if (this_y < next_y && this_x == next_x) {

			//corner
			if (location == 2) {
				cout << "black c" << endl;
				addWayPoint(this_x - (0.5 * robotSizeInCells),this_y - (0.5 * robotSizeInCells),
						this_x + (0.5 * robotSizeInCells),this_y - (0.5 * robotSizeInCells),0,0,0);
				addWayPoint(this_x + (0.5 * robotSizeInCells),this_y - (0.5 * robotSizeInCells),
						this_x + (0.5 * robotSizeInCells), this_y + (0.5 * robotSizeInCells),0,0,0);
				//u turn
			} else if (location == 0) {
				cout << "black u" << endl;
				addWayPoint(this_x - (0.5 * robotSizeInCells),this_y + (0.5 * robotSizeInCells),
						this_x - (0.5 * robotSizeInCells),this_y - (0.5 * robotSizeInCells),0,0,0);
				addWayPoint(this_x - (0.5 * robotSizeInCells),this_y - (0.5 * robotSizeInCells),
						this_x + (0.5 * robotSizeInCells), this_y - (0.5 * robotSizeInCells),0,0,0);
				addWayPoint(this_x + (0.5 * robotSizeInCells), this_y - (0.5 * robotSizeInCells),
						this_x + (0.5 * robotSizeInCells), this_y + (0.5 * robotSizeInCells),0,0,0);
			}

			cout << "black" << endl;
			drawline(this_x,this_y,next_x,next_y,255,0,0);
			addWayPoint(this_x + (0.5 * robotSizeInCells), this_y + (0.5 * robotSizeInCells),
					next_x + (0.5 * robotSizeInCells),next_y - (0.5 * robotSizeInCells),0,0,0);

			location = 1;

			//This is for going from right to left on the map
		} else if (this_y > next_y && this_x == next_x) {

			if (location == 3) {
				cout << "blue c" << endl;
				addWayPoint(this_x + (0.5 * robotSizeInCells),this_y + (0.5 * robotSizeInCells),
						this_x - (0.5 * robotSizeInCells),this_y + (0.5 * robotSizeInCells),0,0,255);
				addWayPoint(this_x - (0.5 * robotSizeInCells),this_y + (0.5 * robotSizeInCells),
						this_x - (0.5 * robotSizeInCells), this_y - (0.5 * robotSizeInCells),0,0,255);
			} else if (location == 1) {
				cout << "blue u" << endl;
				addWayPoint(this_x + (0.5 * robotSizeInCells),this_y - (0.5 * robotSizeInCells),
						this_x + (0.5 * robotSizeInCells),this_y + (0.5 * robotSizeInCells),0,0,255);
				addWayPoint(this_x + (0.5 * robotSizeInCells),this_y + (0.5 * robotSizeInCells),
						this_x - (0.5 * robotSizeInCells),this_y + (0.5 * robotSizeInCells),0,0,255);
				addWayPoint(this_x - (0.5 * robotSizeInCells),this_y + (0.5 * robotSizeInCells),
						this_x - (0.5 * robotSizeInCells), this_y - (0.5 * robotSizeInCells),0,0,255);
			}

			cout << "blue" << endl;
			drawline(this_x,this_y,next_x,next_y,255,0,0);
			addWayPoint(this_x - (0.5 * robotSizeInCells), this_y - (0.5 * robotSizeInCells),
					next_x - (0.5 * robotSizeInCells),next_y + (0.5 * robotSizeInCells),0,0,255);
			location = 0;

			//This is for going from down to up on the map
		} else if (this_y == next_y && this_x > next_x) {

			if (location == 1) {
				cout << "green c" << endl;
				addWayPoint(this_x + (0.5 * robotSizeInCells),this_y - (0.5 * robotSizeInCells),
						this_x + (0.5 * robotSizeInCells),this_y + (0.5 * robotSizeInCells),0,255,0);
				addWayPoint(this_x + (0.5 * robotSizeInCells),this_y + (0.5 * robotSizeInCells),
						this_x - (0.5 * robotSizeInCells), this_y + (0.5 * robotSizeInCells),0,255,0);
			} else if (location == 2) {
				cout << "green u" << endl;
				addWayPoint(this_x - (0.5 * robotSizeInCells),this_y - (0.5 * robotSizeInCells),
						this_x + (0.5 * robotSizeInCells),this_y - (0.5 * robotSizeInCells),0,255,0);
				addWayPoint(this_x + (0.5 * robotSizeInCells),this_y - (0.5 * robotSizeInCells),
						this_x + (0.5 * robotSizeInCells),this_y + (0.5 * robotSizeInCells),0,255,0);
				addWayPoint(this_x + (0.5 * robotSizeInCells),this_y + (0.5 * robotSizeInCells),
						this_x - (0.5 * robotSizeInCells), this_y + (0.5 * robotSizeInCells),0,255,0);
			}

			cout << "green" << endl;
			drawline(this_x,this_y,next_x,next_y,255,0,0);
			addWayPoint(this_x - (0.5 * robotSizeInCells), this_y + (0.5 * robotSizeInCells),
					next_x + (0.5 * robotSizeInCells),next_y + (0.5 * robotSizeInCells),0,255,0);

			location = 3;

			//This is for going from up to down on the map
		} else if (this_y == next_y && this_x < next_x) {

			if (location == 0) {
				cout << "purple c" << endl;
				addWayPoint(this_x - (0.5 * robotSizeInCells),this_y + (0.5 * robotSizeInCells),
						this_x - (0.5 * robotSizeInCells),this_y - (0.5 * robotSizeInCells),255,0,255);
				addWayPoint(this_x - (0.5 * robotSizeInCells),this_y - (0.5 * robotSizeInCells),
						this_x + (0.5 * robotSizeInCells), this_y - (0.5 * robotSizeInCells),255,0,255);
			} else if (location == 3) {
				cout << "purple u" << endl;
				addWayPoint(this_x + (0.5 * robotSizeInCells),this_y + (0.5 * robotSizeInCells),
						this_x - (0.5 * robotSizeInCells),this_y + (0.5 * robotSizeInCells),255,0,255);
				addWayPoint(this_x - (0.5 * robotSizeInCells),this_y + (0.5 * robotSizeInCells),
						this_x - (0.5 * robotSizeInCells),this_y - (0.5 * robotSizeInCells),255,0,255);
				addWayPoint(this_x - (0.5 * robotSizeInCells),this_y - (0.5 * robotSizeInCells),
						this_x + (0.5 * robotSizeInCells), this_y - (0.5 * robotSizeInCells),255,0,255);
			}

			cout << "purple" << endl;
			drawline(this_x,this_y,next_x,next_y,255,0,0);
			addWayPoint(this_x + (0.5 * robotSizeInCells), this_y - (0.5 * robotSizeInCells),
					next_x - (0.5 * robotSizeInCells),next_y - (0.5 * robotSizeInCells),255,0,255);

			location = 2;

		}

	}
	cout << "save to image done" << endl;
	lodepng::encode(filePath, image, mapWidth, mapHeight);
}


const Grid& Map::getFineGrid() const {
	return this->fineGrid;
}

const Grid& Map::getCoarseGrid() const {
	return this->coarseGrid;
}

const vector<Node*>& Map::getWayPoints() const {
		return wayPoints;
	}

const vector<vector<Node*> >& Map::getGridGraph() const {
	return gridGraph;
}

Map::~Map() {
	// TODO Auto-generated destructor stub
}

