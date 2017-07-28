#ifndef NODE_CPP
#define NODE_CPP
#include <iostream>

using namespace std;

class Node {
private:
	bool _flagged;
	bool _isSource;
	bool _isDestination;
	int _xCoordinate;
	int _yCoordinate;
	int _numberOfChannels;
	int _currentChannel;
	Node * _previous;
	
public:
	Node() { _flagged = false; _isSource = false; _isDestination = false;
		_xCoordinate = 0; _yCoordinate = 0; _numberOfChannels = 5; _currentChannel = rand() % _numberOfChannels; 
		_previous = NULL;}

	Node(int numberOfChannels) { _flagged= false; _isSource = false; _isDestination = false;
		_xCoordinate = 0; _yCoordinate = 0; _numberOfChannels = numberOfChannels; 
		_currentChannel = rand() % _numberOfChannels; _previous = NULL;}
	
	Node * getPrevious() { return _previous; };
	bool isFlagged() { return _flagged; }
	bool isSource() { return _isSource; }
	bool isDest() { return _isDestination; }
	tuple<int, int> getCoordinates() { return make_tuple(_xCoordinate, _yCoordinate); }
	int getCurrentChannel() { return _currentChannel; }
	
	void flagNode() { _flagged = true; }
	void setSource(int x, int y) { _xCoordinate = x; _yCoordinate = y; _isSource = true; }
	void setDest(int x, int y) { _xCoordinate = x; _yCoordinate = y; _isDestination = true; }
	void setPrevious(Node *previous) { _previous = previous; }
	void setCoordinates(int x, int y) { _xCoordinate = x; _yCoordinate = y; }
	void cycleChannel() { if(_currentChannel < _numberOfChannels - 1) _currentChannel++; else _currentChannel = 0; }
};


#endif
