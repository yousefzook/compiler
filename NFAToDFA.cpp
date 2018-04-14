//
// Created by yousef on 14/04/18.
//

#include <queue>
#include <iostream>
#include "NFAToDFA.h"



/*
 * Convert given grouped nfa to dfa and return it
 * */
DFA convertToDFA() {

    GroupedNFA *nfa = GroupedNFA::getInstance();
    DFA dfa;
    // declaring variables
    map<set<int>, int> dfaStatesMap; // mapping each state of dfa into one integer
    int counter = 0; // size of the dfa trans table
    queue<set<int>> toBeProcessed; // sets that not determined yet for each input
    // first set of states, Start state and its closures
    // in nfa table, start state is the last row
    set<int> firstCell = nfa->transTable[nfa->transTable.size()-1][0];

    // set the first set of states in the queue
    toBeProcessed.push(firstCell);
    vector<int> temp (nfa->allInputs.size()-1, -1);
    dfa.transTable.insert(dfa.transTable.begin() + counter, temp); // init the row of the table
    string acceptedName = editAcceptedDFAStates(firstCell); // check if the set has an accepted state
    if(!acceptedName.empty())
        dfa.acceptedStates[counter] = acceptedName;
    dfaStatesMap[firstCell] = counter++;

    while (!toBeProcessed.empty()) {
        set<int> currentSet;
        currentSet = toBeProcessed.front();
        toBeProcessed.pop();

        set<int> nextSet; // to get each new set of next state closures

        // loop on each input 'i' except lambda input '0'; to get the next state
        for (int input = 1; input < nfa->allInputs.size(); input++) {
            for (auto state : currentSet)
                nextSet.insert(nfa->transTable[state][input].begin(), nfa->transTable[state][input].end());
            nextSet = getClosures(nextSet);


            if (dfaStatesMap.count(nextSet) == 0) { // this new state is not put into the dfa map before
                // init the row of the table
                vector<int> temp (nfa->allInputs.size()-1, -1);
                dfa.transTable.insert(dfa.transTable.begin() + counter, temp);
                string acceptedName = editAcceptedDFAStates(nextSet); // check if the set has an accepted state
                if(acceptedName.empty())
                    dfa.acceptedStates[counter] = acceptedName;
                dfaStatesMap[nextSet] = counter++;
                toBeProcessed.push(nextSet);
            }

            // set the cell in the dfa trans table
            dfa.transTable[dfaStatesMap[currentSet]][input-1] = dfaStatesMap[nextSet];
            nextSet.clear();
        }
    }

    return dfa;
}

/*
 * If the set of states given has an accepted state
 * then put this set id in the acceptedStates map in DFA
 * */
string editAcceptedDFAStates(set<int> set){
    GroupedNFA *nfa = GroupedNFA::getInstance();
    for(auto stateInt: set){
        GroupedNFA::State* state = nfa->statesMap.valueForKey(stateInt);
        if(state->accepted)
            return nfa->acceptedStatesName[state];
    }
    return "";
}

/*
 * returns a set of closures of a given set
 * */
set<int> getClosures(set<int> set){

    std::set<int> sss;
    std::set<int> newSet;
    GroupedNFA *nfa = GroupedNFA::getInstance();
    for(auto iter : set)
        newSet.insert(nfa->transTable[iter][0].begin(), nfa->transTable[iter][0].end());
    if(newSet == set) // base case that the set of closures is the same
        return newSet;
    else // if new states are added to the set, get their closures also
        return getClosures(newSet);

}
