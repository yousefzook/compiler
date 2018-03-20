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
	// initialize startState
	startState = createState(false);
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

/* Initialize a new state and add it states vector.
 * */
Graph::State* Graph::createState(bool accepted) {
	State* newState = new State();
	newState->accepted = accepted;
	allStates.push_back(newState);

	return newState;
}

/* Get all final states
 * */
vector<Graph::State*> Graph::getFinalStates() {
	vector<State*> finalStates;

	for (vector<State*>::iterator i = allStates.begin(); i < allStates.end();
			i++) {
//		cout << *i << endl;
		if ((*i)->accepted == true) {
			finalStates.push_back((*i));
//			cout << "HIIIIIIII" << endl;
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
//
//	Graph::State* c = g->createState(true);
//
//	string s = "letter";
//	g->addEdge(g->startState, b, s);
//
//	vector<Graph::State*> finals = g->getFinalStates();
//
//	cout << "!!!Hello World!!!" << endl;
////	cout << g->startState->nextStates.back().second << endl;
//	cout << g->allStates.size() << endl;
//
//	return 0;
//}

