#include <iostream>
#include <ctime>
#include <tuple>
#include <vector>
#include <map>
#include <queue>

using namespace std;

class Node {
	private: 
		bool _flagged;
		bool _isSource;
		bool _isDestination;
		int _xCoordinate;
		int _yCoordinate;
		Node * _previous;

	public:
		Node() { _flagged = false; _isSource = false; _previous = NULL; }

		Node * getPrevious() { return _previous; };
		bool isFlagged() { return _flagged; }
		bool isSource() { return _isSource; }
		bool isDest() { return _isDestination; }
		tuple<int, int> getCoordinates() { return make_tuple(_xCoordinate, _yCoordinate); }

		void flagNode() { _flagged = true; }
		void setSource(int x, int y) { _xCoordinate = x; _yCoordinate = y; _isSource = true; }
		void setDest(int x, int y) { _xCoordinate = x; _yCoordinate = y; _isDestination = true; }
		void setPrevious(Node *previous) { _previous = previous; }
		void setCoordinates(int x, int y) { _xCoordinate = x; _yCoordinate = y; }
};

int main() {
	int i = 0;
	srand((int)time(0));
	map<tuple<int, int>, Node* > nodeMap; 				// contains coordinates of all nodes
	
	// create 20 nodes, map them 
	while(nodeMap.size() != 20) {
		int randX = (rand() % 10);
		int randY = (rand() % 10);
		if(nodeMap.find(make_tuple(randX, randY)) == nodeMap.end()) {
			Node *tempNode = new Node;
			tempNode -> setCoordinates(randX, randY);
			tuple<int, int> coordinates = make_tuple(randX, randY);
			nodeMap.insert(pair<tuple<int, int>, Node* >(coordinates, tempNode));
		}
	}
	
	/*
	cout << nodeMap.size() << endl;

	for(auto it = nodeMap.begin(); it != nodeMap.end(); it++) {
		tuple<int, int> node = it -> first;
		cout << get<0>(node) << " " << get<1>(node) << " " << &it -> second  << endl;
	}
	*/
	// end mapping and creating of nodes 
	
	// designate source and destination in map
	int randSrc = (rand() % 10);
	int randDest = (rand() % 10);

	while(randSrc == randDest) {
		randDest = (rand() % 10);
	}

	int count = 0;
	int srcX = 0, srcY = 0, destX = 0, destY = 0;
	for(auto it = nodeMap.begin(); it != nodeMap.end(); it++) {
		if(count == randSrc || count == randDest) {
			if(count == randSrc) {
				tuple<int, int> srcCoordinate = it -> first;
				srcX = get<0>(srcCoordinate);
				srcY = get<1>(srcCoordinate);
				it -> second -> setSource(srcX, srcY);
				//auto coordTest = it -> second -> getCoordinates();
				//cout << "Src test: " << get<0>(coordTest) << " " << get<1>(coordTest) << endl;
			}
			if(count == randDest) {
				tuple<int, int> destCoordinate = it -> first;
				destX = get<0>(destCoordinate);
				destY = get<1>(destCoordinate);
				it -> second -> setDest(destX, destY);
				//auto coordTest = it -> second -> getCoordinates();
				//cout << "Dest test: " << get<0>(coordTest) << " " << get<1>(coordTest) << endl;
			}
		}
		count++;
	}
	cout << "Source: (" << srcX << ", " << srcY << "), ";
	cout << "Destination: (" << destX << ", " << destY << ") " << endl;
	cout << endl;
	// end designation of source and destination 

	bool destinationReached = false;
	queue<pair<tuple<int, int>, Node*> > nextQueue;
	auto srcNode = nodeMap.find(make_tuple(srcX, srcY));
	nextQueue.push(make_pair(srcNode -> first, srcNode -> second));
	srcNode -> second -> flagNode();
	int unflagged = 19;
	//nodeMap.erase(srcNode -> first);
	
	while(!nextQueue.empty() && !destinationReached) {
		for(auto it = nodeMap.begin(); it != nodeMap.end() && unflagged != 0; it++) {

			if(nextQueue.front().second -> isDest()) {
				//cout << "Found it." << endl;
				destinationReached = true;
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

				it -> second -> flagNode();
				it -> second -> setPrevious(topNode);
				//cout << "Testing: " << get<0>(it -> second -> getPrevious() -> getCoordinates()) << " " <<
			//		get<1>(it -> second -> getPrevious() -> getCoordinates()) << endl;
				unflagged--;
				//cout << "Enqueue: " << get<0>(tempCoordinates) << " " << get<1>(tempCoordinates) << endl;
				//cout << "Queue size: " << nextQueue.size() << endl;
		

				nextQueue.push(make_pair(tempCoordinates, tempNode));
				//cout << "Unflagged " << unflagged << endl;
			}
		}
		nextQueue.pop();
	}

	auto it = nodeMap.find(make_pair(destX, destY));
	Node *nodePtr = it -> second;
	cout << "(" << get<0>(nodePtr -> getCoordinates()) << ", " << get<1>(nodePtr -> getCoordinates()) << ")";
	nodePtr = nodePtr -> getPrevious();
	while(nodePtr != NULL) {
		cout << " <- (" << get<0>(nodePtr -> getCoordinates()) << ", " 
			 << get<1>(nodePtr -> getCoordinates()) << ")";
		nodePtr = nodePtr -> getPrevious();
	}
	cout << endl;
	cout << endl;

	// initialize matrix of 0 
	int nodeMatrix[10][10];
	for(int i = 0; i < 10; i++) {
		for(int j = 0; j < 10; j++) {
			nodeMatrix[i][j] = 0;
		}
	}
	// end initialize 

	// set up matrix 
	for(auto it = nodeMap.begin(); it != nodeMap.end(); it++) {
		auto coordinates = it -> first;
		nodeMatrix[get<0>(coordinates)][get<1>(coordinates)] += 1;
	}
	nodeMatrix[srcX][srcY]++;
	nodeMatrix[destX][destY] += 2;
	// end set up matrix 

	/*
	for(int i = 0; i < nodeList.size(); i++) {
		tuple<int, int> tempNode = nodeList.at(i);
		int tempX = get<0>(tempNode);
		int tempY = get<1>(tempNode);
		if(nodeMatrix[tempX][tempY] != 0) {
			cout << tempX << " " << tempY << endl;
		}
		nodeMatrix[tempX][tempY] = 1;
	}
	*/

	// print matrix 
	for(int i = 0; i < 10; i++) {
		for(int j = 0; j < 10; j++) {
			cout << nodeMatrix[i][j] << " ";
		}
		cout << endl;
	}
	// end print matrix 

	
	/*
	cout << srcX << " " << srcY << endl;
	bool destinationReached = false;
	for(int i = srcX - 3; i <= srcX + 3; i++) {
		for(int j = srcY - 3; j <= srcY + 3; j++) {
			cout << i << " " << j << endl;
		}
	}
	*/

	return 0;
}
