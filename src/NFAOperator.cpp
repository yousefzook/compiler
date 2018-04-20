//
// Created by yousef on 13/04/18.
//

#include "NFAOperator.h"
#include "NFA.h"
#include <iostream>
using namespace std;

NFA OR(NFA nfa1, NFA nfa2) {
	NFA nfa;
	nfa.name = nfa1.name + "|" + nfa2.name;

	nfa.addEdge(nfa.startState, nfa1.startState, "L");
	nfa.addEdge(nfa.startState, nfa2.startState, "L");

	nfa1.finalState->accepted = false;
	nfa2.finalState->accepted = false;
	nfa1.addEdge(nfa1.finalState, nfa.finalState, "L");
	nfa2.addEdge(nfa2.finalState, nfa.finalState, "L");

	return nfa;
}

NFA AND(NFA nfa1, NFA nfa2) {
	NFA nfa;
	nfa.name = nfa1.name + "." + nfa2.name;

	nfa.startState = nfa1.startState;
	nfa1.finalState = nfa2.startState;

	return nfa;
}

NFA kleeneClosure(NFA nfa) {
	NFA temp;
	temp.name = nfa.name + "*";

	temp.addEdge(temp.startState, nfa.startState, "L");
	temp.finalState->accepted = false;
	temp.addEdge(nfa.finalState, temp.finalState, "L");
	temp.addEdge(nfa.finalState, nfa.startState, "L");

	return temp;
}

NFA positiveClosure(NFA nfa) {
	NFA temp;
	temp.name = nfa.name + "+";

	NFA kleene = kleeneClosure(nfa);
	temp = OR(nfa, kleene);
	return temp;
}

//int main(int argc, char **argv) {
//	NFA nfa1;
//	nfa1.addEdge(nfa1.startState, nfa1.finalState, "a");
//	NFA nfa2;
//	nfa2.addEdge(nfa2.startState, nfa2.finalState, "b");
//
//	NFA nfa = OR(nfa1, nfa2);
//	cout << "Hello" << endl;
//}
