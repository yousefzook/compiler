/*
 * Graph.h
 *
 *  Created on: Mar 16, 2018
 *      Author: Yousef Zook
 */
#include <vector>
#include <string>
using namespace std;

#ifndef GRAPH_H_
#define GRAPH_H_

class Graph {
public:
	Graph();
	virtual ~Graph();

	/* State struct that have references of next states
	 * and transitions between them and an accepted boolean.
	 * */
	struct State {
		vector<pair<State*, string> > nextStates;
		bool accepted;
	};

	/* Create a state choosing whether it's accepted or not.
	 * */
	State* createState(bool accepted);

	/* Create an edge with a transition between two states.
	 * */
	void addEdge(State* srcState, State* destState, string transition);

	/* Remove state from the graph and delete all
	 * its corresponding edges.
	 * */
//	void deleteState(State* state);

	/* Get all final states
	 * */
	vector<State*> getFinalStates();

public:

	/* It's the user duty to use this start state
	 * as the graph actual start state because
	 * it will be used in other operations
	 */
	State * startState;

	/* Vector contains all created states
	 */
	vector<State*> allStates;
};

#endif /* GRAPH_H_ */
