#ifndef FUNCTIONS_CPP
#define FUNCTIONS_CPP
#include <iostream>
#include <ctime> #include <tuple>
#include <map>
#include <queue>
#include "Node.cpp"
#include "Functions.h"

using namespace std;

void generateNodes(map<tuple<int, int>, Node* > *nodeMap) {
	while(nodeMap -> size() != 20) {
		int randX = (rand() % 10);
		int randY = (rand() % 10);
		if(nodeMap -> find(make_tuple(randX, randY)) == nodeMap -> end()) {
			Node *tempNode = new Node;
			tempNode -> setCoordinates(randX, randY);
			tuple<int, int> coordinates = make_tuple(randX, randY);
			nodeMap -> insert(pair<tuple<int, int>, Node* >(coordinates, tempNode));
		}
	}
}

void createSrcAndDestination(map<tuple<int, int>, Node* > *nodeMap, int &srcX,int &srcY,int &destX,int &destY) {
	int randSrc = (rand() % 10);
	int randDest = (rand() % 10);
	
	while(randSrc == randDest) 
		randDest = (rand() % 10);
	
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

void findPath(map<tuple<int, int>, Node* > &nodeMap, int srcX, int srcY, int destX, int destY) {
	bool destinationReached = false;
	queue<pair<tuple<int, int>, Node*> > nextQueue;
	auto srcNode = nodeMap.find(make_tuple(srcX, srcY));
	nextQueue.push(make_pair(srcNode -> first, srcNode -> second));
	srcNode -> second -> flagNode();
	int unflagged = nodeMap.size() - 1;
	int totalTime = 0;
	int totalNodes = 0;
	
	while(!nextQueue.empty() && !destinationReached) {
		for(auto it = nodeMap.begin(); it != nodeMap.end() && unflagged != 0; it++) {
			if(nextQueue.front().second -> isDest()) {
				destinationReached = true;
				totalNodes = nextQueue.size();
				break;
			}
			totalTime += 100;
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
				
				it -> second -> flagNode();
				it -> second -> setPrevious(topNode);
				unflagged--;
				
				nextQueue.push(make_pair(tempCoordinates, tempNode));
			}
		}
		nextQueue.pop();
	}
	cout << "Total time taken is: " << totalTime << " ms." << endl;
	cout << "Total nodes visited: " << (totalTime / 100) + totalNodes << "." << endl;
}

void printPath(map<tuple<int, int>, Node* > nodeMap, int destX, int destY) {
	auto it = nodeMap.find(make_pair(destX, destY));
	Node *nodePtr = it -> second;
	int counter = 1;
	cout << "(" << get<0>(nodePtr -> getCoordinates()) << ", " << get<1>(nodePtr -> getCoordinates()) << ")";
	nodePtr = nodePtr -> getPrevious();
	while(nodePtr != NULL) {
		cout << " <- (" << get<0>(nodePtr -> getCoordinates()) << ", "
			 << get<1>(nodePtr -> getCoordinates()) << ")";
		nodePtr = nodePtr -> getPrevious();
		counter++; 
	}
	cout << endl;
	cout << endl;
}

#endif
