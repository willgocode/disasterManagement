#include <iostream>
#include <ctime>
#include <tuple>
#include <map>
#include <queue>
#include "Node.cpp"
#include "Functions.h"

using namespace std;


int main() {
	int srcX = 0, srcY = 0, destX = 0, destY = 0;
	srand((int)time(0));
	map<tuple<int, int>, Node* > nodeMap;
	
	generateNodes(&nodeMap);
	createSrcAndDestination(&nodeMap, srcX, srcY, destX, destY);
	findPath(nodeMap, srcX, srcY, destX, destY);
	printPath(nodeMap, destX, destY);

	int nodeMatrix[10][10];
	for(int i = 0; i < 10; i++) {
		for(int j = 0; j < 10; j++) {
			nodeMatrix[i][j] = 0;
		}
	}
	
	// set up matrix
	for(auto it = nodeMap.begin(); it != nodeMap.end(); it++) {
		auto coordinates = it -> first;
		nodeMatrix[get<0>(coordinates)][get<1>(coordinates)] += 1;
	}
	nodeMatrix[srcX][srcY]++;
	nodeMatrix[destX][destY] += 2;
	// end set up matrix 

	// print matrix 
	for(int i = 0; i < 10; i++) {
		for(int j = 0; j < 10; j++) {
			cout << nodeMatrix[i][j] << " ";
		}
		cout << endl;
	}
	// end print matrix 

	return 0;
}
