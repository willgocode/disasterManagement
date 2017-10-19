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

/* Functions */
/* generateNodes: will take a map, a number of nodes, a matrix size and a number of channels */
/*				  will return randomly generated points that are not the static src/dest 	 */

/* createSrcAndDestination: not used for this version, but it will choose a random src/dest  */

/* DataContainer Structure: Contains information such as how long it took to prepare the     */
/*							channel, totalRREQs and if the destination has been found. 		 */

/* findPath: will return a DataContainer that keeps track if the dest was found from a given */
/*   			 src node.																 	 */

/* getPath: will return the number of nodes from the src node to the dest node. 			 */


void generateNodes(map<tuple<int, int>, Node* > *nodeMap, int numberOfNodes, int matrixSize, 
		int numberOfChannels) {

	/* Will randomly generate two numbers as coordinates to put into the matrix */
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

DataContainer findPath(map<tuple<int, int>, Node* > &nodeMap, int srcX, int srcY, 
		int destX, int destY, int numberOfNodes) {

	/* This function uses a breadth first search. It will enqueue the node that has not */
	/* been visited yet. 																*/
	bool destinationReached = false;
	queue<pair<tuple<int, int>, Node*> > nextQueue;
	auto srcNode = nodeMap.find(make_tuple(srcX, srcY));
	nextQueue.push(make_pair(srcNode -> first, srcNode -> second));
	srcNode -> second -> flagNode();
	int unflagged = nodeMap.size() - 1;
	int totalNodes = 0;
	int timeWaitedForChannel = 0;
	DataContainer container;
	
	/* Loop will go until either the queue for the search is empty or if the dest node */
	/* is found. 																	   */
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
			
			/* This checks for nodes within three spaces of the current node and if it */
			/* has been reached yet.												   */
			if(get<0>(tempCoordinates) <= get<0>(topCoordinates) + 3 &&
			   get<0>(tempCoordinates) >= get<0>(topCoordinates) - 3 &&
			   get<1>(tempCoordinates) <= get<1>(topCoordinates) + 3 &&
			   get<1>(tempCoordinates) >= get<1>(topCoordinates) - 3 &&
			   !tempNode -> isFlagged()) {
				/* This loop will cycle the channel until the channel of the next node */
				/* is equal to the channel of the current node.						   */
				while(tempNode -> getCurrentChannel() != 
						srcNode -> second -> getCurrentChannel()) {

					tempNode -> cycleChannel();
					timeWaitedForChannel += 10;
				}
					
				/* Flag the node and insert when you find a match, then move on.	   */
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

	/* Set the dataContainer to store the total time waited for the channel, total nodes */
	/* traversed and if the destination was found or not. 								 */
	container.channelPrepTime = timeWaitedForChannel;
	container.totalRREQs = totalNodes;
	container.destinationFound = destinationReached;

	return container;
}

int getPath(map<tuple<int, int>, Node* > nodeMap, int destX, int destY) {
	auto it = nodeMap.find(make_pair(destX, destY));
	Node *nodePtr = it -> second;
	int counter = 1;
	nodePtr = nodePtr -> getPrevious();
	while(nodePtr != NULL) {
		nodePtr = nodePtr -> getPrevious();
		counter++; 
	}
	return counter;
}

#endif
