#ifndef BLOCKSWORLD_H
#define BLOCKSWORLD_H
#include <iostream>
#include <vector>
#include <cstdlib>
#include "AStar.h"

#define SCRAMBLE 1000

class AStar;

class State {
    public:
	void scramble();
	bool isSame(State &someState);	// Check if same
	bool isMove(int srcStack, int dstStack);
	void move(int srcStack, int dstStack);
	void getChildren(AStar *astar);		// We'll see
	int H(State &goalState);	// Heuristic
	int Cost(State *child);		// Path cost

	void printState();		// Visualize
	
	std::vector<std::vector<int>> blockState; // block state
	int nStacks, nBlocks;	
};



#endif //BLOCKSWORLD_H
