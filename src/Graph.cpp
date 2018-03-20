/*
 * Graph.cpp
 *
 *  Created on: Mar 16, 2018
 *      Author: yousef
 */

#include "Graph.h"

#include <string>
#include <iostream>

Graph::Graph() {
	// initialize startState and add it
	// to the states vector
	startState = createState(false);
	allStates.push_back(startState);
}

Graph::~Graph() {

}
/* There will not be a physical edge , we just put
 * the destination state and its transition in
 * the source state nextStates vector
 *  */
void Graph::addEdge(State* srcState, State* destState, string transition) {
	srcState->nextStates.push_back(pair<State*, string>(destState, transition));
}

/* Initialize a new state and return it.
 * */
Graph::State* Graph::createState(bool accepted) {
	State* newState = new State();
	newState->accepted = accepted;

	return newState;
}

/* Get all final states
 * */
vector<Graph::State*> Graph::getFinalStates() {
	vector<State*> finalStates;

	for (vector<State*>::iterator i = allStates.begin(); i < allStates.end();
			i++) {
		if ((*i)->accepted == true) {
			finalStates.push_back((*i));
		}
	}

	return finalStates;
}

//void Graph::deleteState(State* state) {
//
//	for (vector<State*>::iterator i = allStates.begin();
//			i < allStates.end(); i++) {
//		State* s = (*i);
//
//	}
//}

//int main(int argc, char **argv) {
//	Graph* g = new Graph();
//
//	Graph::State* b = g->createState(true);
//	string s = "letter";
//	g->addEdge(g->startState, b, s);
//
//	cout << "!!!Hello World!!!" << endl;
//	cout << g->startState->nextStates.back().second << endl;
//
//	return 0;
//}

