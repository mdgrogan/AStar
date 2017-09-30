#ifndef DEFINITIONS_H
#define DEFINITIONS_H
#include <iostream>
#include <queue>
#include <functional>
#include <vector>
#include <cstdlib>
#include <climits>

#define SCRAMBLE 10000

class AStar;


class State {
    public:
	void scramble();
	bool isSame(State &someState);	// Check if same
	bool isMove(int srcStack, int dstStack);
	void move(int srcStack, int dstStack);
	void getChildren(AStar *astar);		// We'll see
	int H(State &goalState);	// Heuristic
	int G();		// Path cost

	void printState();		// Visualize
	
	std::vector<std::vector<int>> blockState; // block state
	int nStacks, nBlocks;	
};

#define LARGENUM 10000
class Node {
    public:
	Node() : g(LARGENUM), parent(NULL) {};
	Node *parent;
	Node *child;
	State state; 

	int f;
	int g;
	int h;
	int depth;
};
struct compareNodePtrs {
    bool operator() (const Node *lhs, const Node *rhs) {
	return lhs->f > rhs->f;
    }
};


class AStar {
    public:
	void init(State &startState, State &goalState);
	int search(int maxSteps);
	bool addChild(State &s, int srcStack, int dstStack); 
    private:
	Node *newNode();
	void freeNode(Node *n);
	bool isBetterPath(Node *n, int tmpG);
	void reconstructPath(Node *current);
	void printSearchState(Node *current);
	void printFile(Node *current);
    
	Node *start;
	Node *goal;
	std::priority_queue<Node*, std::vector<Node*>, compareNodePtrs> frontier;
	std::vector<Node*> visited;
	std::vector<Node*> children;
	std::vector<Node*> goalPath;
	int step;
};


#endif //DEFINITIONS_H
