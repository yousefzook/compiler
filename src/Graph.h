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

	/*
	 * State struct that have references of next states
	 * and values between them and an accepted boolean.
	 * */
	struct State {
		vector<pair<State*, string> > nextStates;
		bool accepted;
	};

	/*
	 * Create a state , given its previous and next states
	 * and if it's accepted or not
	 * */
	State* createState(vector<pair<State*, string> > prevStates,
			vector<pair<State*, string> > nextStates, bool accepted);

private:
	State * startState;
};

#endif /* GRAPH_H_ */
