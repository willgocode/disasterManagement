#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <iostream>
#include <ctime>
#include <tuple>
#include <map>
#include <queue>
#include "Node.cpp"

using namespace std;

// randomly generates nodes and stores them into an stl map
void generateNodes(map<tuple<int, int>, Node* > *nodeMap);

// randomly assign a source and a destination and update map
void createSrcAndDestination(map<tuple<int, int>, Node* > *nodeMap, int &srcX,int &srcY,int &destX,int &destY);

// find a path from the src to the destination
void findPath(map<tuple<int, int>, Node* > &nodeMap, int srcX, int srcY, int destX, int destY);

// print the path backwards from the destination
void printPath(map<tuple<int, int>, Node* > nodeMap, int destX, int destY);

#endif
