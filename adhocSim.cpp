#include <iostream>
#include <ctime>
#include <tuple>
#include <map>
#include <queue>
#include "Node.cpp"
#include "Functions.h"

using namespace std;


int main(int argc, char *argv[]) {
	if(argc != 3) { cout << "./adhocSim.exe <numberOfNodes> <sizeOfMatrix>" << endl; return 0;}

	cout << endl;
	for(int i = 0; i < 20; i++) {
		int srcX = 0, srcY = 0, destX = 0, destY = 0;
		int numberOfNodes = stoi(argv[1]);
		int matrixSize = stoi(argv[2]);
		srand((int)time(0));
		map<tuple<int, int>, Node* > nodeMap;
		
		generateNodes(&nodeMap, numberOfNodes, matrixSize);
		createSrcAndDestination(&nodeMap, srcX, srcY, destX, destY, numberOfNodes);
		bool found = findPath(nodeMap, srcX, srcY, destX, destY, numberOfNodes);
		if(found) { printPath(nodeMap, destX, destY); }

		/*
		int nodeMatrix[matrixSize][matrixSize];
		for(int i = 0; i < matrixSize; i++) {
			for(int j = 0; j < matrixSize; j++) {
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
		for(int i = 0; i < matrixSize; i++) {
			for(int j = 0; j < matrixSize; j++) {
				cout << nodeMatrix[i][j] << " ";
			}
			cout << endl;
		}
		cout << endl;
		// end print matrix 
	}
	*/
}

	return 0;
}
