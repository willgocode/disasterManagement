#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <iostream>
#include <ctime>
#include <tuple>
#include <map>
#include <queue>
#include "Node.cpp"

using namespace std;

/* Used to get this data from the findPath function. */
struct DataContainer {
	int channelPrepTime = 0;
	int totalRREQs = 0;
	bool destinationFound = false;
};

/* randomly generates nodes and stores them into an stl map */
void generateNodes(map<tuple<int, int>, Node* > *nodeMap, int numberOfNodes, int matrixSize,
		int numberOfChannels);

/* randomly assign a source and a destination and update map */
void createSrcAndDestination(map<tuple<int, int>, Node* > *nodeMap, int &srcX,int &srcY,int &destX,
		int &destY, int numberOfNodes);

/* find a path from the src to the destination */
DataContainer findPath(map<tuple<int, int>, Node* > &nodeMap, int srcX, int srcY, int destX, int destY,
		int numberOfNodes);

/* print the path backwards from the destination */
int getPath(map<tuple<int, int>, Node* > nodeMap, int destX, int destY);

#endif
