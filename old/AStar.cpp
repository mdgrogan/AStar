#include <algorithm>
#include "Definitions.h"
/*
class AStar {
    public:
	void init(State &startState, State &goalState);
	bool addChild(State &s, int srcStack, int dstStack); 
	int search(int maxSteps);
	void reconstructPath();
    
	Node start;
	Node goal;
	std::priority_queue<Node, std::vector<Node>, greaterThan> frontier;
	std::vector<Node> visited;
	std::vector<Node> children;
    private:
	void printSearchState();
	bool isVisited(Node n);
};
*/

/******************************************
 * Set starting and goal nodes 
 ******************************************/
void AStar::init(State &startState, State &goalState) {
    start.state = startState;
    goal.state = goalState;

    // Starting cost function == heuristic
    start.g = 0;
    start.h = start.state.H(goal.state);
    start.f = start.g + start.h;

    // Add start node to frontier
    frontier.push(start);
}

/******************************************
 * This will be called from State::getChildren
 ******************************************/
bool AStar::addChild(State &s, int srcStack, int dstStack) {
    Node n;

    n.state = s;
    n.state.move(srcStack, dstStack);
	//n->state.printState();
    children.push_back(n);
    return true;
}

bool AStar::isBetterPath(Node n, int tmpG) {
    for (int i=0; i<visited.size(); i++) {
	if (n.state.isSame(visited[i].state)) {
	    if (n.g < visited[i].g) {
		return true;
	    }
	}
    }
    return false;
}

void AStar::reconstructPath() {
    Node *tmp = &current;
    tmp->state.printState();
    tmp->parent->state.printState();
    while (tmp != NULL) {
	goalPath.push_back(tmp);
	tmp = tmp->parent;
    }
    for (int i=0; i<goalPath.size(); i++) {
	goalPath[i]->state.printState();
    }
}

void AStar::printSearchState() {
    std::cout<<"Step="<<step<<"\t";
    std::cout<<"Queue="<<frontier.size()<<"\t";
    std::cout<<"f="<<current.f
	<<" g="<<current.g
	<<" h="<<current.h
	<<std::endl;
}

int AStar::search(int maxSteps) {
    step = 0;
    while (!frontier.empty() && step != maxSteps) {

	// current node is best in frontier
	current = frontier.top();

	// goal test
	if (current.state.isSame(goal.state)) {
	    std::cout<<"Found goal"<<std::endl;
	    reconstructPath();
	    return step;
	}
	
	// at current, so add to visited list
	frontier.pop();
	visited.push_back(current);

	// clear children list
	children.clear();

	// find possible child nodes
	current.state.getChildren(this);

	for (int i=0; i<children.size(); i++) {
	    // set parent pointer
	    children[i].parent = &current;
	    //children[i].state.printState();

	    int tmpG = current.g + current.state.G();
	    if (isBetterPath(children[i], tmpG)) {
		continue;
	    }
	    
	    // discovered new node
	    children[i].g = tmpG;
	    children[i].h = children[i].state.H(goal.state);
	    children[i].f = children[i].g + children[i].h;
	    frontier.push(children[i]);
	}
	printSearchState();
	step++;
    }
    return -1;
}












