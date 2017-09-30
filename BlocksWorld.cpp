#include <time.h>
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
    std::vector<int> x;
    for (int i=0; i<nBlocks; i++) {
	x.push_back(i);
    }
    for (int i=0; i<blockState.size(); i++) {
	blockState[i].clear();
    }
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    srand((time_t)ts.tv_nsec);
    for (int i=0; i<nBlocks; i++) {
	r1 = rand()%nStacks;
	r2 = rand()%x.size();
	blockState[r1].push_back(x[r2]);
	x.erase(x.begin()+r2);
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
    
    // Not optimized...
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
 * Heuristic: yikes. This one counts blocks 
 * out of place. If blocks are out of place 
 * in the first row
 ******************************************/
int State::H(State &goalState) {
    int count = nBlocks;
    for (int i=0; i<blockState[0].size(); i++) {
	if (blockState[0][i] == i) {
	    count--;
	}
	else {
	    count++;
	}
    }
    for (int i=1, maxi=blockState.size(); i<maxi; i++) {
	for (int j=0, maxj=blockState[i].size(); j<maxj; j++) {
	    int tmp = 1;
	    while (j-tmp+1 > 0) {
		if (blockState[i][j-tmp] < blockState[i][j]) {
		    count++;
		}
		tmp++;
	    }
	}
    }
    return count;
}
/******************************************
 * Heuristic: this one counts blocks 
 * out of place and adds a step if we aren't
 * in the goal stack.
 ******************************************/
/* H2
int State::H2(State &goalState) {
    int count = nBlocks+1;
    for (int i=0; i<blockState[0].size(); i++) {
	if (blockState[0][i] == i) {
	    count--;
	}
    }
    for (int i=1, maxi=blockState.size(); i<maxi; i++) {
	for (int j=0, maxj=blockState[i].size(); j<maxj; j++) {
	    count++;
	}
    }
    return count;
}*/
/******************************************
 * Heuristic: this one just counts blocks 
 * out of place.
 ******************************************/
/* H1 
int State::H(State &goalState) {
    int out = nBlocks; // out of place
    for (int i=0; i<blockState[0].size(); i++) {
	if (blockState[0][i] == i) {
	    out--;
	}
    }
    return out;
}*/

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

