#include <iostream>
#include <ctime>
#include <tuple>
#include <map>
#include <queue>
#include <time.h>
#include "Node.cpp"
#include "Functions.h"

using namespace std;


int main(int argc, char *argv[]) {
	if(argc != 4) { cout << "./adhocSim.exe <numberOfNodes> <sizeOfMatrix> <numberOfChannels>" << 
		endl; return 0;}

	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	srand((time_t)ts.tv_nsec);

	int averageTime = 0, averageRREQ = 0, averageChannelPrep = 0;

	for(int i = 0; i < 20; i++) {
		int srcX = 20, srcY = 10, destX = 20, destY = 40;
		int numberOfNodes = stoi(argv[1]);
		int matrixSize = stoi(argv[2]);
		int numberOfChannels = stoi(argv[3]);
		map<tuple<int, int>, Node* > nodeMap;
		
		generateNodes(&nodeMap, numberOfNodes, matrixSize, numberOfChannels);
		//createSrcAndDestination(&nodeMap, srcX, srcY, destX, destY, numberOfNodes);
		DataContainer container = findPath(nodeMap, srcX, srcY, destX, destY, numberOfNodes);
		int pathLength = getPath(nodeMap, destX, destY); 
		int totalTime = pathLength * 100;
		cout << endl;

		if(((totalTime) + container.channelPrepTime) > 6000) {
			cout << "Request timed out." << endl;
			cout << endl;
			cout << "=============================================================================" << endl;
			continue;
		}
		
		if(!container.destinationFound) {
			cout << "Couldn't find destination." << endl;
			cout << endl;
			cout << "=============================================================================" << endl;
			continue;
		}

		cout << "Total time for RREQ: " << totalTime + container.channelPrepTime << " ms." << endl;
		averageRREQ += totalTime + container.channelPrepTime;
		cout << "Overall time: " << (totalTime * 2) + container.channelPrepTime << " ms." << endl;
		averageTime += (totalTime * 2) + container.channelPrepTime;
		cout << "Total time preparing channels: " << container.channelPrepTime << " ms." << endl;
		averageChannelPrep += container.channelPrepTime;
		cout << endl;
		cout << "=============================================================================" << endl;

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

	*/
	}

	cout << "Average RREQ: " << averageRREQ / 20 << " ms." << endl;
	cout << "Average total time: " << averageTime / 20 << " ms." << endl;
	cout << "Average channel prep: " << averageChannelPrep / 20 << " ms." << endl;

	return 0;
}
