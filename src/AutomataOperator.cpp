/*
 * AutomateOperator.cpp
 *
 *  Created on: Mar 16, 2018
 *      Author: yousef
 */

#include "AutomataOperator.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

AutomataOperator::AutomataOperator()
{
    // TODO Auto-generated constructor stub
    ID=0;

}

AutomataOperator::~AutomataOperator()
{
    // TODO Auto-generated destructor stub
}

NFA AutomataOperator::createBasicGraph(string value)
{
    NFA newGraph;
    newGraph.startState->id=AutomataOperator::getID();
    cout<<"////////////////////"<<endl;
    cout<<newGraph.startState->id<<endl;
    graph::State *des=newGraph.createState(true,AutomataOperator::getID());
    newGraph.addEdge(newGraph.startState,des,value);
    cout<<"start state ID  "<<newGraph.startState->id<<"   end state ID "<<des->id<<endl;
    cout<<"value  "<<value<<endl;
    cout<<"/////////////////////////////"<<endl;
    return newGraph;
}

NFA AutomataOperator::orOperation(NFA nfa1, NFA nfa2)
{
// Concatenate nfa2 to nfa1
    nfa1.allStates.insert(nfa1.allStates.end(), nfa2.allStates.begin(),
                          nfa2.allStates.end());
    // Get final states of both NFAs (which now in nfa1).
    vector<NFA::State*> finalStates = nfa1.getFinalStates();

    // Create new final state.
    NFA::State* newFinalState = nfa1.createState(true,AutomataOperator::getID());
    cout<<"after change final state"<<newFinalState->id<<endl;

    // The old final states will not be accepted
    // and we create an edge between every one of
    // them and the new final state.
    for (vector<NFA::State*>::iterator i = finalStates.begin();
            i < finalStates.end(); i++)
    {
        NFA::State* state = (*i);

        state->accepted = false;
        nfa1.addEdge(state, newFinalState, "L");
    }

    // The old start states will not be start
    // and we create an edge between them and
    // the new start state.
    cout<<" nfa1 start "<<nfa1.startState->id<<endl;
    cout<<" nfa2 start "<<nfa2.startState->id<<endl;
    NFA::State* oldStartState = nfa1.startState;
    cout<<"before change start state"<<nfa1.startState->id<<endl;
    nfa1.startState = nfa1.createState(false,AutomataOperator::getID());
    cout<<"after change start state"<<nfa1.startState->id<<endl;
    nfa1.addEdge(nfa1.startState, oldStartState, "L");
    nfa1.addEdge(nfa1.startState, nfa2.startState, "L");
    cout<<"after change start state"<<nfa1.startState->nextStates.size()<<endl;

    return nfa1;
}

/* Anding the two NFAs and put the result in nfa1
 * */
NFA AutomataOperator::andOperation(NFA nfa1, NFA nfa2)
{
    // Get final states of nfa1.
    vector<NFA::State*> finalStates1 = nfa1.getFinalStates();
    // Concatenate nfa2 to nfa1
    nfa1.allStates.insert(nfa1.allStates.end(), nfa2.allStates.begin(),
                          nfa2.allStates.end());
    // The old final states of nfa1 will not be
    // accepted and we create an edge between every
    // one of them and the start state of nfa2.
    bool checkFinal=true;
    for (vector<NFA::State*>::iterator i = finalStates1.begin();
            i < finalStates1.end(); i++)
    {
        NFA::State* state = (*i);
        checkFinal=false;
        state->accepted = false;
        nfa1.addEdge(state, nfa2.startState, "L");
    }

    if(checkFinal)
        nfa1.addEdge(nfa1.startState, nfa2.startState, "L");
cout<<"enter and "<<endl;
    return nfa1;
}

NFA AutomataOperator::closureOperation(NFA nfa)
{
    // Get final states.
    cout<<"Enter closure Operation ----------------"<<endl;
    vector<NFA::State*> finalStates = nfa.getFinalStates();

    // Create new final state.
    NFA::State* newFinalState = nfa.createState(true,AutomataOperator::getID());

    // The old final states will not be accepted
    // and we create an edge between every
    // one of them and the new final state.
    for (vector<NFA::State*>::iterator i = finalStates.begin();
            i < finalStates.end(); i++)
    {
        NFA::State* state = (*i);

        state->accepted = false;
        nfa.addEdge(state, newFinalState, "L");
    }

    // We create two edges in two directions
    // between start and new final states.
    nfa.addEdge(nfa.startState, newFinalState, "L");
    nfa.addEdge(newFinalState, nfa.startState, "L");

    return nfa;
}

NFA AutomataOperator::positiveClosureOperation(NFA nfa)
{
    cout <<"Enter positive closure "<<endl;
    //Get final states.
    vector<NFA::State*> finalStates = nfa.getFinalStates();

    // we create an edge between every
    // final state and the start state.
    for (vector<NFA::State*>::iterator i = finalStates.begin();
            i < finalStates.end(); i++)
    {
        NFA::State* state = (*i);

        nfa.addEdge(state, nfa.startState, "L");
    }
cout<<"return from positive closure ****"<<endl;
    return nfa;
}

NFA AutomataOperator::optionalOperation(NFA nfa)
{
    // Get final states.
    vector<NFA::State*> finalStates = nfa.getFinalStates();

    // Create an edge between start
    // state and every final state.
    for (vector<NFA::State*>::iterator i = finalStates.begin();
            i < finalStates.end(); i++)
    {
        NFA::State* state = (*i);

        nfa.addEdge(nfa.startState, state, "L");
    }

    return nfa;
}


int AutomataOperator::getID()
{
    AutomataOperator::ID++;
    return AutomataOperator::ID;
}


DFA* NFAToDFA(NFA* nfa)
{

    // [TODO] --- to be implemented .....

    return 0;
}
