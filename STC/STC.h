
#include "../Map/Map.h"
#include "Node.h"

using namespace std;


class STC {
private:
	Map &map;
	//
	vector<vector<Node *> > graph;
	//contains the path of points from DFS
	vector<Node *>Path;
	int graphWidth;
    int graphHeight;
	void buildGraph();
	/**
	 * run DFS get the first point
	 */
	void DFS(Node* n);
	void printGraph();
public:
	/**
	 * constructor
	 */
	STC(Map &map, Position startPos);
	vector<vector<Node *> > getGraph();
	/**
	 *build the spanning tree
	 */
	void buildSpanningTree();

	void printPath();

	virtual ~STC();
	const vector<Node*>& getPath() const ;

};


