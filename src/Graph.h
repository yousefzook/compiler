//
// Created by yousef on 27/03/18.
//

#ifndef CLEAN_COMPILER_GRAPH_H
#define CLEAN_COMPILER_GRAPH_H

#include <string>

using namespace std;

#include <vector>

class Graph {

public:
	// Constructor
	Graph();
	// Destructor
	virtual ~Graph();

	struct State {
		vector<pair<State *, string> > nextStates;
		bool accepted;
	};

	/* Create a state choosing whether it's accepted or not.
	 * */
	State *createState(bool accepted);

	/* Create an edge with a transition between two states.
	 * */
	void addEdge(State *srcState, State *destState, string transition);

	State *startState;
	State *finalState;

private:
};

#endif //CLEAN_COMPILER_GRAPH_H
