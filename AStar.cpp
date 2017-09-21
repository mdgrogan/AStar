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
Node* AStar::newNode() {
    Node *n = new Node;
    return n;
}

void AStar::freeNode(Node *n) {
    delete n;
}

/******************************************
 * Set starting and goal nodes 
 ******************************************/
void AStar::init(State &startState, State &goalState) {
//    std::cout<<"entering init()"<<std::endl;
    start = newNode();
    goal = newNode();
    start->state = startState;
    goal->state = goalState;

    // Starting cost function == heuristic
    start->g = 0;
    start->h = start->state.H(goal->state);
    start->f = start->g + start->h;
    // Add start node to frontier
//    std::cout<<"init(1)"<<std::endl;
    frontier.push(start);
//    std::cout<<"exiting init()"<<std::endl;
}

/******************************************
 * This will be called from State::getChildren
 ******************************************/
bool AStar::addChild(State &s, int srcStack, int dstStack) {
//    std::cout<<"entering addChild()"<<std::endl;
    Node *n = newNode();
    if (!n) {
	return false;
    }
    n->state = s;
    n->state.move(srcStack, dstStack);
	//n->state.printState();
    children.push_back(n);
//    std::cout<<"exiting addChild()"<<std::endl;
    return true;
}

bool AStar::isBetterPath(Node *n, int tmpG) {
    for (int i=0; i<visited.size(); i++) {
	if (n->state.isSame(visited[i]->state)) {
	    if (n->g < visited[i]->g) {
		return true;
	    }
	}
    }
    return false;
}

void AStar::reconstructPath(Node *current) {
    while (current->parent != NULL) {
	goalPath.push_back(current);
	current = current->parent;
    }
    std::cout<<"Path:"<<std::endl;
    for (int i=goalPath.size()-1; i>=0; i--) {
	goalPath[i]->state.printState();
    }
}

void AStar::printSearchState(Node *current) {
    std::cout<<"Step="<<step<<", ";
    std::cout<<"Queue="<<frontier.size()<<", ";
    std::cout<<"f="<<current->f
	<<", g="<<current->g
	<<", h="<<current->h
	<<std::endl;
}

int AStar::search(int maxSteps) {
    step = 0;
//    std::cout<<"entering Search()"<<std::endl;
    while (!frontier.empty() && step != maxSteps) {

	// clear children list
	children.clear();
	//
	// current node is best in frontier
	Node *current = frontier.top();

//    std::cout<<"Search(1)"<<std::endl;
	// goal test
	if (current->state.isSame(goal->state)) {
	    visited.clear();
	    std::cout<<"Found goal"<<std::endl;
	    reconstructPath(current);
	    return step;
	}
	
//    std::cout<<"Search(2)"<<std::endl;
	// at current, so add to visited list

	frontier.pop();
	visited.push_back(current);

//    std::cout<<"Search(3)"<<std::endl;


//    std::cout<<"Search(4)"<<std::endl;
	// find possible child nodes
	current->state.getChildren(this);

//    std::cout<<"Search(5)"<<std::endl;
	for (int i=0; i<children.size(); i++) {
	    int tmpG = current->g + current->state.G();


//    std::cout<<"Search(6)"<<std::endl;

	    // check visited list if child is on it or has
	    // more expensive path
	    if (isBetterPath(children[i], tmpG)) {
		continue;
	    }
	    
//    std::cout<<"Search(7)"<<std::endl;
	    // discovered new node
	    children[i]->parent = current;
//	    std::cout<<"test\n";
//	    current->state.printState();
//	    children[i]->state.printState();

	    children[i]->g = tmpG;
	    children[i]->h = children[i]->state.H(goal->state);
	    children[i]->f = children[i]->g + children[i]->h;
	    frontier.push(children[i]);
	}
	printSearchState(current);
	step++;
    }
    return -1;
}












