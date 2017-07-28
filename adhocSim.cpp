#include <iostream>
#include <ctime>
#include <tuple>
#include <map>
#include <queue>
#include "Node.cpp"
#include "Functions.h"

using namespace std;


int main(int argc, char *argv[]) {
	if(argc != 4) { cout << "./adhocSim.exe <numberOfNodes> <sizeOfMatrix> <numberOfChannels>" << 
		endl; return 0;}

	cout << endl;
	int srcX = 20, srcY = 10, destX = 20, destY = 40;
	int numberOfNodes = stoi(argv[1]);
	int matrixSize = stoi(argv[2]);
	int numberOfChannels = stoi(argv[3]);
	srand((int)time(0));
	map<tuple<int, int>, Node* > nodeMap;
	
	generateNodes(&nodeMap, numberOfNodes, matrixSize, numberOfChannels);
	//createSrcAndDestination(&nodeMap, srcX, srcY, destX, destY, numberOfNodes);
	findPath(nodeMap, srcX, srcY, destX, destY, numberOfNodes);
	printPath(nodeMap, destX, destY); 

	int nodeMatrix[matrixSize][matrixSize];
	for(int i = 0; i < matrixSize; i++) {
		for(int j = 0; j < matrixSize; j++) {
			nodeMatrix[i][j] = 0;
		}
	}
	
	// set up matrix
	for(auto it = nodeMap.begin(); it != nodeMap.end(); it++) {
		auto coordinates = it -> first;
		nodeMatrix[get<1>(coordinates)][get<0>(coordinates)] += 1;
	}
	nodeMatrix[srcY][srcX]++;
	nodeMatrix[destY][destX] += 2;
	// end set up matrix 

	// print matrix 
	for(int i = 0; i < matrixSize; i++) {
		for(int j = 0; j < matrixSize; j++) {
			cout << nodeMatrix[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	// end print matrix 

	return 0;
}
