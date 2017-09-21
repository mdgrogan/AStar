#include "Definitions.h"


/******************************************
 * isMove: check if move is valid.
 ******************************************/
bool State::isMove(int srcStack, int dstStack) {
    if ((srcStack<0) | (srcStack>nStacks) | 
	    (dstStack<0) | (dstStack>nStacks)) {
	//std::cout<<"bad inputs"<<std::endl;
	return false;
    }
    if (srcStack == dstStack) {
	//std::cout<<"bad inputs"<<std::endl;
	return false;
    }
    if (blockState[srcStack].empty()) {
	//std::cout<<"source stack empty"<<std::endl;
	return false;
    }
    //blockState[dstStack].push_back(blockState[srcStack].back());
    //blockState[srcStack].pop_back();
    return true;
}

/******************************************
 * Move top element from source stack to
 * destination stack. Check if valid with
 * isMove() first.
 ******************************************/
void State::move(int srcStack, int dstStack) {
    blockState[dstStack].push_back(blockState[srcStack].back());
    blockState[srcStack].pop_back();
}

/******************************************
 * Randomize start position
 ******************************************/
void State::scramble() {
    int r1, r2;
    srand(time(0));
    for (int i=0; i<SCRAMBLE; i++) {
	r1 = rand()%nStacks;
	r2 = rand()%nStacks;
	if (isMove(r1, r2))
	    move(r1, r2);
    }
}

/******************************************
 * Check if two blockStates are the same (goal testing)
 ******************************************/
bool State::isSame(State &someState) {
    if (blockState == someState.blockState) {
	return true;
    }
    return false;
}


/******************************************
 * Generate possible successors: check all
 * potential moves for validity
 ******************************************/
void State::getChildren(AStar *astar) {
    State NewState;
    NewState.nStacks = nStacks;
    NewState.nBlocks = nBlocks;
    NewState.blockState = blockState;
    
    for (int i=0; i<nStacks; i++) {
	for (int j=0; j<nStacks; j++) {
	    if (isMove(i, j)) {
		if (!astar->addChild(NewState, i, j)) {
		    std::cout<<"cannot add new child"<<std::endl;
		}
	    }
	}
    }
}

/******************************************
 * Heuristic: this one just counts blocks 
 * out of place.
 ******************************************/
int State::H(State &goalState) {
    int in = 0; // in place blocks
    int out = nBlocks; // out of place
    for (int i=0; i<blockState[0].size(); i++) {
	if (blockState[0][i] == i) {
	    in++;
	}
    }
    out -= in;
    return out;
}

/******************************************
 * Cost (total) of moving to child node. In
 * BlocksWorld, this is 1 I think...
 ******************************************/
int State::G() {
	return 1;
}

/******************************************
 * Print out the current blockState of the 'blocks'
 * in the example format
 ******************************************/
void State::printState() {
    for (int i=0; i<blockState.size(); i++) {
	std::cout<<i+1<<" | ";
	for (int j=0; j<blockState[i].size(); j++) {
	    std::cout<<blockState[i][j]+1<<" ";
	}
	std::cout<<std::endl;
    }
    std::cout<<std::endl;
}

