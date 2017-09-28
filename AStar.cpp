#include <algorithm>
#include "Definitions.h"

/******************************************
 * Allocate and delete nodes 
 ******************************************/
Node* AStar::newNode() {
    Node *n = new Node;
    if (!n)
	exit(0);
    return n;
}

void AStar::freeNode(Node *n) {
    delete n;
}

/******************************************
 * Set starting and goal nodes 
 ******************************************/
void AStar::init(State &startState, State &goalState) {
    start = newNode();
    goal = newNode();
    start->state = startState;
    goal->state = goalState;

    // Starting cost function == heuristic
    start->g = 0;
    start->h = start->state.H(goal->state);
    start->f = start->g + start->h;
    start->depth = 0;
    // Add start node to frontier
    frontier.push(start);
}

/******************************************
 * This will be called from State::getChildren
 * Adds child node with the passed parameters.
 * It's a little obtuse...
 ******************************************/
bool AStar::addChild(State &s, int srcStack, int dstStack) {
    Node *n = newNode();
    if (!n) {
	return false;
    }
    n->state = s;
    n->state.move(srcStack, dstStack);
    children.push_back(n);
    return true;
}

/******************************************
 * Check if node has been visited and, if so,
 * is it better than the previously visited 
 * node. If so, return true.
 ******************************************/
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

/******************************************
 * Reconstruct (and print) path from current
 * node to root. 
 ******************************************/
void AStar::reconstructPath(Node *current) {
    while (current->parent != NULL) {
	goalPath.push_back(current);
	current = current->parent;
    }
    // root node will have no parent
    goalPath.push_back(current); 
    std::cout<<"Path:"<<std::endl;
    for (int i=goalPath.size()-1; i>=0; i--) {
	goalPath[i]->state.printState();
    }
}

/******************************************
 * Print search parameters associated with 
 * current node. 
 ******************************************/
void AStar::printSearchState(Node *current) {
    std::cout<<"Step="<<step<<", ";
    std::cout<<"Queue="<<frontier.size()<<", ";
    std::cout<<"f="<<current->f
	<<", g="<<current->g
	<<", h="<<current->h
	<<", depth="<<current->depth
	<<std::endl;
}

/******************************************
 * Main a* search. 
 ******************************************/
int AStar::search(int maxSteps) {
    step = 0;
    while (!frontier.empty() && step != maxSteps) {
	// clear children list
	children.clear();
	
	// current node is best in frontier
	Node *current = frontier.top();

	// goal test
	if (current->state.isSame(goal->state)) {
	    visited.clear();
	    std::cout<<"Found goal"<<std::endl;
	    printSearchState(current);
	    reconstructPath(current);
	    return step;
	}
	
	// at current, so add to visited list
	frontier.pop();
	visited.push_back(current);

	// find possible child nodes
	current->state.getChildren(this);

	for (int i=0; i<children.size(); i++) {
	    int tmpG = current->g + current->state.G();

	    // check visited list if child is on it or has
	    // more expensive path
	    if (isBetterPath(children[i], tmpG)) {
		continue;
	    }
	    
	    // discovered new node
	    children[i]->parent = current;
	    children[i]->g = tmpG;
	    children[i]->h = children[i]->state.H(goal->state);
	    children[i]->f = children[i]->g + children[i]->h;
	    children[i]->depth = current->depth + 1;
	    frontier.push(children[i]);
	}
	//printSearchState(current);
	step++;
    }
    return -1;
}
