#ifndef FUNCTIONS_CPP
#define FUNCTIONS_CPP
#include <iostream>
#include <ctime> 
#include <tuple>
#include <map>
#include <queue>
#include <fstream>
#include "Node.cpp"
#include "Functions.h"

using namespace std;

void generateNodes(map<tuple<int, int>, Node* > *nodeMap, int numberOfNodes, int matrixSize, 
		int numberOfChannels) {
	while(nodeMap -> size() != numberOfNodes - 2) {
		int randX = (rand() % matrixSize);
		int randY = (rand() % matrixSize);
		if(nodeMap -> find(make_tuple(randX, randY)) == nodeMap -> end()) {
			Node *tempNode = new Node(numberOfChannels);
			tempNode -> setCoordinates(randX, randY);
			tuple<int, int> coordinates = make_tuple(randX, randY);
			nodeMap -> insert(pair<tuple<int, int>, Node* >(coordinates, tempNode));
		}
	}

	tuple<int, int> srcCoords = make_tuple(20, 10);
	tuple<int, int> destCoords = make_tuple(20, 40);
	Node *srcNode = new Node(numberOfChannels);
	Node *destNode = new Node(numberOfChannels);
	srcNode -> setCoordinates(20, 10);
	destNode -> setCoordinates(20, 40);
	srcNode -> setSource(20, 10);
	destNode -> setSource(20, 40);
	nodeMap -> insert(pair<tuple<int, int>, Node* >(srcCoords, srcNode));
	nodeMap -> insert(pair<tuple<int, int>, Node* >(destCoords, destNode));
}

void createSrcAndDestination(map<tuple<int, int>, Node* > *nodeMap, int &srcX,int &srcY,int &destX,
		int &destY, int numberOfNodes) {
	int randSrc = (rand() % numberOfNodes);
	int randDest = (rand() % numberOfNodes);
	
	while(randSrc == randDest) 
		randDest = (rand() % numberOfNodes);
	
	int count = 0;
	for(auto it = nodeMap -> begin(); it != nodeMap -> end(); it++) {
		if(count == randSrc || count == randDest) {
			if(count == randSrc) {
				tuple<int, int> srcCoordinate = it -> first;
				srcX = get<0>(srcCoordinate);
				srcY = get<1>(srcCoordinate);
				it -> second -> setSource(srcX, srcY);
			}
			if(count == randDest) {
				tuple<int, int> destCoordinate = it -> first;
				destX = get<0>(destCoordinate);
				destY = get<1>(destCoordinate);
				it -> second -> setDest(destX, destY);
			}
		}
		count++;
	}

	cout << "Source: (" << srcX << ", " << srcY << "), ";
	cout << "Destination: (" << destX << ", " << destY << ") " << endl;
}

DataContainer findPath(map<tuple<int, int>, Node* > &nodeMap, int srcX, int srcY, int destX, int destY,
		int numberOfNodes) {

	bool destinationReached = false;
	queue<pair<tuple<int, int>, Node*> > nextQueue;
	auto srcNode = nodeMap.find(make_tuple(srcX, srcY));
	nextQueue.push(make_pair(srcNode -> first, srcNode -> second));
	srcNode -> second -> flagNode();
	int unflagged = nodeMap.size() - 1;
	int totalNodes = 0;
	int timeWaitedForChannel = 0;
	DataContainer container;
	
	while(!nextQueue.empty() && !destinationReached) {
		for(auto it = nodeMap.begin(); it != nodeMap.end() && unflagged != 0; it++) {
			if(nextQueue.front().second -> isDest()) {
				destinationReached = true;
				totalNodes = nodeMap.size() - unflagged;
				break;
			}

			pair<tuple<int, int>, Node*> topPair = nextQueue.front();
			tuple<int, int> topCoordinates = topPair.first;
			Node *topNode = new Node;
			topNode = topPair.second;
			
			auto tempNode = it -> second;
			auto tempCoordinates = it -> first;
			
			if(get<0>(tempCoordinates) <= get<0>(topCoordinates) + 3 &&
			   get<0>(tempCoordinates) >= get<0>(topCoordinates) - 3 &&
			   get<1>(tempCoordinates) <= get<1>(topCoordinates) + 3 &&
			   get<1>(tempCoordinates) >= get<1>(topCoordinates) - 3 &&
			   !tempNode -> isFlagged()) {
				while(tempNode -> getCurrentChannel() != 
						srcNode -> second -> getCurrentChannel()) {
					tempNode -> cycleChannel();
					timeWaitedForChannel += 10;
				}
					
				it -> second -> flagNode();
				it -> second -> setPrevious(topNode);
				unflagged--;
				
				nextQueue.push(make_pair(tempCoordinates, tempNode));
			}
		}
		nextQueue.pop();
	}

	if(nodeMap[pair<int, int>(destX, destY)] -> getPrevious()) {
		destinationReached = true;
	}

	container.channelPrepTime = timeWaitedForChannel;
	container.totalRREQs = totalNodes;
	container.destinationFound = destinationReached;

	return container;
}

int getPath(map<tuple<int, int>, Node* > nodeMap, int destX, int destY) {
	auto it = nodeMap.find(make_pair(destX, destY));
	Node *nodePtr = it -> second;
	int counter = 1;
	//cout << "(" << get<0>(nodePtr -> getCoordinates()) << ", " << get<1>(nodePtr -> getCoordinates()) << ")";
	nodePtr = nodePtr -> getPrevious();
	while(nodePtr != NULL) {
		//cout << " <- (" << get<0>(nodePtr -> getCoordinates()) << ", "
	//		 << get<1>(nodePtr -> getCoordinates()) << ")";
		nodePtr = nodePtr -> getPrevious();
		counter++; 
	}
//	cout << endl;
//	cout << endl;
	return counter;
}

/*
void cycleAllNodes(map<tuple<int, int>, Node* > *nodeMap, int srcX, int srcY, int destX, int destY) {
	tuple<int, int> srcCoordinates = make_tuple(srcX, srcY);
	tuple<int, int> destCoordinates = make_tuple(destX, destY);

	for(auto it = nodeMap -> begin(); it != nodeMap -> end(); it++) {
		if(it -> first == srcCoordinates) 
			continue;
		if(it -> first == destCoordinates)
			continue;
		cout << get<0>(it -> first) << " " << get<1>(it -> first)  << endl;
		it -> second -> cycleChannel();
	}
}
*/
#endif
