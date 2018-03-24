/*
 * AutomateOperator.cpp
 *
 *  Created on: Mar 16, 2018
 *      Author: yousef
 */

#include "AutomataOperator.h"
#include "TransitionTableConverter.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <queue>

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

NFA AutomataOperator::createBasicGraph(string key,string value)
{
    NFA newGraph;
    newGraph.startState->id=AutomataOperator::getID();
    newGraph.startState->graphName=key;
    graph::State *des=newGraph.createState(true,AutomataOperator::getID(),key);
    newGraph.addEdge(newGraph.startState,des,value);
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
    NFA::State* newFinalState = nfa1.createState(true,AutomataOperator::getID(),nfa2.startState->graphName);

    // The old final states will not be accepted
    // and we create an edge between every one of
    // them and the new final state.
    for (vector<NFA::State*>::iterator i = finalStates.begin();
            i < finalStates.end(); i++)
    {
        NFA::State* state = (*i);
        newFinalState->graphName=state->graphName;
        state->accepted = false;
        nfa1.addEdge(state, newFinalState, "L");
    }
    if(nfa1.startState->nextStates.size()==0)
        nfa1.addEdge(nfa1.startState, newFinalState, "L");
    // The old start states will not be start
    // and we create an edge between them and
    // the new start state.
    NFA::State* oldStartState = nfa1.startState;
    nfa1.startState = nfa1.createState(false,AutomataOperator::getID(),nfa2.startState->graphName);
    nfa1.addEdge(nfa1.startState, oldStartState, "L");
    nfa1.addEdge(nfa1.startState, nfa2.startState, "L");
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
    // one of them and the start state of nfa2. // bool checkFinal=true;
    for (vector<NFA::State*>::iterator i = finalStates1.begin();
            i < finalStates1.end(); i++)
    {
        NFA::State* state = (*i);
        state->accepted = false;
        nfa1.addEdge(state, nfa2.startState, "L");
    }

    if(nfa1.startState->nextStates.size()==0)
        nfa1.addEdge(nfa1.startState, nfa2.startState, "L");
    return nfa1;
}

NFA AutomataOperator::closureOperation(NFA nfa)
{
    // Get final states.
    vector<NFA::State*> finalStates = nfa.getFinalStates();

    // Create new final state.
    NFA::State* newFinalState = nfa.createState(true,AutomataOperator::getID(),nfa.startState->graphName);

    // The old final states will not be accepted
    // and we create an edge between every
    // one of them and the new final state.
    for (vector<NFA::State*>::iterator i = finalStates.begin();
            i < finalStates.end(); i++)
    {
        NFA::State* state = (*i);
        state->accepted = false;
        newFinalState->graphName=state->graphName;
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

NFA AutomataOperator::orMainGraph(NFA nfa1, NFA nfa2)
{
    nfa1.allStates.insert(nfa1.allStates.end(), nfa2.allStates.begin(),
                          nfa2.allStates.end());
    nfa1.addEdge(nfa1.startState, nfa2.startState, "L");
    return nfa1;
}


vector<vector<int>> AutomataOperator::NFAToDFATable(vector<vector<set<int>>> nfaTransTable ,NFA *nfa) {

    // declaring variables
    map<set<int>, int> dfaStatesMap; // mapping each state of dfa into one integer
    int counter = 0; // size of the dfa trans table
    queue<set<int>> toBeProcessed; // sets that not determined yet for each input
    vector<vector<int>> dfaTransTable; // the final trans table that will be returned
    set<int> firstCell = nfaTransTable[0][0]; // first set of states, Start state and its closures

    // set the first set of states in the queue
    toBeProcessed.push(firstCell);
    vector<int> temp (nfa->allInputs.size()-1, -1);
    dfaTransTable.insert(dfaTransTable.begin() + counter, temp); // init the row of the table
    dfaStatesMap[firstCell] = counter++;

    set<int> currentSet;
    while (!toBeProcessed.empty()) {
        currentSet = toBeProcessed.front();
        toBeProcessed.pop();

        set<int> nextSet; // to get each new set of next state closures

        // loop on each input 'i' except lambda input '0'; to get the next state
        for (int input = 1; input < nfa->allInputs.size(); input++) {
            for (auto state : currentSet)
                nextSet.insert(nfaTransTable[state][input].begin(), nfaTransTable[state][input].end());
            nextSet = getClosures(nextSet, nfaTransTable);


            if (dfaStatesMap.count(nextSet) == 0) { // this new state is not put into the dfa map before
                // init the row of the table
                vector<int> temp (nfa->allInputs.size()-1, -1);
                dfaTransTable.insert(dfaTransTable.begin() + counter, temp);
                dfaStatesMap[nextSet] = counter++;
                toBeProcessed.push(nextSet);
            }

            // set the cell in the dfa trans table
            dfaTransTable[dfaStatesMap[currentSet]][input-1] = dfaStatesMap[nextSet];
            nextSet.clear();
        }
    }

    return dfaTransTable;
}

set<int> AutomataOperator::getClosures(set<int> oldSet, vector<vector<set<int>>> nfaTransTable) {
    // get set of closures of a set oldSet
    set<int> newSet;
    for(auto it : oldSet)
        newSet.insert(nfaTransTable[it][0].begin(), nfaTransTable[it][0].end());
    if(newSet == oldSet) // base case that the set of closures is the same
        return newSet;
    else // if new states are added to the set, get their closures also
        return getClosures(newSet, nfaTransTable);
}
