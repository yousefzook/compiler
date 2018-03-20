/*
 * AutomateOperator.cpp
 *
 *  Created on: Mar 16, 2018
 *      Author: yousef
 */

#include "AutomataOperator.h"
#include "NFA.h"
#include "DFA.h"
#include "RegularDefinition.h"

AutomataOperator::AutomataOperator() {
	// TODO Auto-generated constructor stub

}

AutomataOperator::~AutomataOperator() {
	// TODO Auto-generated destructor stub
}

/* Oring the two NFAs and put the result in nfa1
 * */
NFA* orOperation(NFA* nfa1, NFA* nfa2) {
	// Concatenate nfa2 to nfa1
	nfa1->allStates.insert(nfa1->allStates.end(), nfa2->allStates.begin(),
			nfa2->allStates.end());

	// Get final states of both NFAs (which now in nfa1).
	vector<NFA::State*> finalStates = nfa1->getFinalStates();

	// Create new final state.
	NFA::State* newFinalState = nfa1->createState(true);

	// The old final states will not be accepted
	// and we create an edge between every one of
	// them and the new final state.
	for (vector<NFA::State*>::iterator i = finalStates.begin();
			i < finalStates.end(); i++) {
		NFA::State* state = (*i);

		state->accepted = false;
		nfa1->addEdge(state, newFinalState, RegularDefinition::L);
	}

	// The old start states will not be start
	// and we create an edge between them and
	// the new start state.
	NFA::State* oldStartState = nfa1->startState;
	nfa1->startState = nfa1->createState(false);

	nfa1->addEdge(nfa1->startState, oldStartState, RegularDefinition::L);
	nfa1->addEdge(nfa1->startState, nfa2->startState, RegularDefinition::L);

	return nfa1;
}

/* Anding the two NFAs and put the result in nfa1
 * */
NFA* andOperation(NFA* nfa1, NFA* nfa2) {
	// Get final states of nfa1.
	vector<NFA::State*> finalStates1 = nfa1->getFinalStates();

	// Concatenate nfa2 to nfa1
	nfa1->allStates.insert(nfa1->allStates.end(), nfa2->allStates.begin(),
			nfa2->allStates.end());

	// The old final states of nfa1 will not be
	// accepted and we create an edge between every
	// one of them and the start state of nfa2.
	for (vector<NFA::State*>::iterator i = finalStates1.begin();
			i < finalStates1.end(); i++) {
		NFA::State* state = (*i);

		state->accepted = false;
		nfa1->addEdge(state, nfa2->startState, RegularDefinition::L);
	}

	return nfa1;
}

NFA* closureOperation(NFA* nfa) {
	// Get final states.
	vector<NFA::State*> finalStates = nfa->getFinalStates();

	// Create new final state.
	NFA::State* newFinalState = nfa->createState(true);

	// The old final states will not be accepted
	// and we create an edge between every
	// one of them and the new final state.
	for (vector<NFA::State*>::iterator i = finalStates.begin();
			i < finalStates.end(); i++) {
		NFA::State* state = (*i);

		state->accepted = false;
		nfa->addEdge(state, newFinalState, RegularDefinition::L);
	}

	// We create two edges in two directions
	// between start and new final states.
	nfa->addEdge(nfa->startState, newFinalState, RegularDefinition::L);
	nfa->addEdge(newFinalState, nfa->startState, RegularDefinition::L);

	return nfa;
}

NFA* positiveClosureOperation(NFA* nfa) {
	// Get final states.
	vector<NFA::State*> finalStates = nfa->getFinalStates();

	// we create an edge between every
	// final state and the start state.
	for (vector<NFA::State*>::iterator i = finalStates.begin();
			i < finalStates.end(); i++) {
		NFA::State* state = (*i);

		nfa->addEdge(state, nfa->startState, RegularDefinition::L);
	}

	return nfa;
}

NFA* optionalOperation(NFA* nfa) {
	// Get final states.
	vector<NFA::State*> finalStates = nfa->getFinalStates();

	// Create an edge between start
	// state and every final state.
	for (vector<NFA::State*>::iterator i = finalStates.begin();
			i < finalStates.end(); i++) {
		NFA::State* state = (*i);

		nfa->addEdge(nfa->startState, state, RegularDefinition::L);
	}

	return nfa;
}

DFA* NFAToDFA(NFA* nfa) {

	// [TODO] --- to be implemented .....

	return 0;
}
