//
// Created by yousef on 13/04/18.
//

#include "NFAOperator.h"
#include "GroupedNFA.h"

NFA OR(NFA nfa1, NFA nfa2) {
    NFA nfa;
    nfa.name = nfa1.name + "|" + nfa2.name;
    nfa.startState = nfa.createState(false);
    nfa.finalState = nfa.createState(true);
    nfa1.finalState->accepted = false;
    nfa2.finalState->accepted = false;
    nfa.addEdge(nfa.startState, nfa1.startState, "\\L");
    nfa.addEdge(nfa.startState, nfa2.startState, "\\L");
    nfa.addEdge(nfa1.finalState, nfa.finalState, "\\L");
    nfa.addEdge(nfa2.finalState, nfa.finalState, "\\L");
    return nfa;
}

NFA AND(NFA nfa1, NFA nfa2) {
    NFA nfa;
    nfa.name = nfa1.name + "." + nfa2.name;
    GroupedNFA *groupedNFA = GroupedNFA::getInstance();
    // remove final state of nfa1 from all states list
    for (int i = 0; i < groupedNFA->allStates.size(); i++)
        if (nfa1.finalState == groupedNFA->allStates[i]) {
            groupedNFA->allStates.erase(groupedNFA->allStates.begin() + i);
        }
    nfa1.finalState = nfa2.startState;
    nfa.startState = nfa1.startState;
    nfa.finalState = nfa2.finalState;
    return nfa;
}

NFA kleeneClosure(NFA nfa1) {
    NFA nfa;
    nfa1.finalState->accepted = false;
    nfa1.addEdge(nfa1.finalState, nfa1.startState, "\\L");
    nfa.startState = nfa.createState(false);
    nfa.finalState = nfa.createState(true);
    nfa.addEdge(nfa.startState, nfa1.startState, "\\L");
    nfa.addEdge(nfa1.finalState, nfa.finalState, "\\L");
    nfa.addEdge(nfa.startState, nfa.finalState, "\\L");
    nfa.name = nfa1.name + "*";
    return nfa;
}

NFA positiveClosure(NFA nfa1) {
    NFA nfa;
    nfa = AND(nfa1, kleeneClosure(nfa1));
    nfa.name = nfa1.name + "+";
    return nfa;
}