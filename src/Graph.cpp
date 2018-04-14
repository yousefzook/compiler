//
// Created by yousef on 27/03/18.
//

#include "Graph.h"
#include "GroupedNFA.h"

Graph::Graph() {
	// initialize startState and finalState
	startState = createState(false);
	finalState = createState(true);
}

Graph::~Graph() {
}

/* Initialize a new state and add it states vector.
 * */
Graph::State *Graph::createState(bool accepted) {
	State *newState = new State();
	newState->accepted = accepted;
	// This needs to be handled
	GroupedNFA *groupedNFA = GroupedNFA::getInstance();
	groupedNFA->allStates.push_back(newState);

	return newState;
}

/* There will not be a physical edge , we just put
 * the destination state and its transition in
 * the source state nextStates vector
 *  */
void Graph::addEdge(State *srcState, State *destState, string transition) {
	srcState->nextStates.push_back(
			pair<State *, string>(destState, transition));
}
