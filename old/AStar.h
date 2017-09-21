#ifndef ASTAR_H
#define ASTAR_H
#include <vector>
#include "BlocksWorld.h"

class State;

class Node {
    public:
	Node *parent;
	Node *child;
	State state; 

	int f;
	int g;
	int h;

	bool operator<(const Node &rhs) {
	    return this->f < rhs.f;
	}
};


class AStar {
    public:
	Node *allocateNode();
	void deleteNode(Node *n);
	// the addChild stuff can and probably should be cleaned up both here
	// and in BlocksWorld
	bool addChild(State &s, int srcStack, int dstStack); 
    
	std::vector<Node*> frontier;
	std::vector<Node*> visited;
	std::vector<Node*> children;
};


#endif //ASTAR_H
