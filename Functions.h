#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <iostream>
#include <ctime>
#include <tuple>
#include <map>
#include <queue>
#include "Node.cpp"

using namespace std;

void generateNodes(map<tuple<int, int>, Node* > *nodeMap);
void createSrcAndDestination(map<tuple<int, int>, Node* > *nodeMap, int &srcX,int &srcY,int &destX,int &destY);
void findPath(map<tuple<int, int>, Node* > &nodeMap, int srcX, int srcY, int destX, int destY);
void printPath(map<tuple<int, int>, Node* > nodeMap, int destX, int destY);

#endif
