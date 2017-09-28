#include "Definitions.h"


int main(int argc, char **argv) {
    if (argc!=4) {
	std::cout<<"Usage: ./main [#searches] [#stacks] [#blocks]"<<std::endl;
	return 1;
    }
    
    int numSearch = atoi(argv[1]);
    int numStacks = atoi(argv[2]);
    int numBlocks = atoi(argv[3]);
    
    AStar aStar;
    State startState;
    State goalState;

    // used to be in constructor-----------------
    startState.nStacks = goalState.nStacks = numStacks;
    startState.nBlocks = goalState.nBlocks = numBlocks;
    for (int i=0; i<numStacks; i++) {
        goalState.blockState.push_back({0});
        startState.blockState.push_back({0});
        goalState.blockState[i].clear();
        startState.blockState[i].clear();
    }
    for (int i=0; i<numBlocks; i++) {
	goalState.blockState[0].push_back(i);
//        startState.blockState[0].push_back(i);
    }
    startState.scramble();
    //-------------------------------------------


    std::cout<<"Goal blockState:"<<std::endl;
    goalState.printState();

    std::cout<<"Start blockState:"<<std::endl;
    std::cout<<"H(goal): "<<startState.H(goalState)<<std::endl;
    startState.printState();
    
    aStar.init(startState, goalState);
    aStar.search(numSearch);  
    return 0;
}

