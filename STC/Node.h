/*
 * Node.h
 *
 *  Created on: Nov 18, 2015
 *      Author: colman
 */

#ifndef NODE_H_
#define NODE_H_

#include <vector>
using namespace std;

typedef pair<int, int> Position;

class Node {
public:
	//  i,j in STC graph output
	int row, col;
	bool visited;
	// contains the neighbors of the point
	vector<Node *> neighborsInSpanningTree;
/**
 * constructor
 */
	Node(int row, int col);
	virtual ~Node();
	Position getPosition();
	bool isVisited();
};

#endif /* NODE_H_ */
