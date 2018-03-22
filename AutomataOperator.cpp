/*
 * AutomateOperator.cpp
 *
 *  Created on: Mar 16, 2018
 *      Author: yousef
 */

#include <map>
#include <queue>
#include "AutomataOperator.h"
#include "TransitionTableConverter.h"

AutomataOperator::AutomataOperator() {
    // TODO Auto-generated constructor stub

}

AutomataOperator::~AutomataOperator() {
    // TODO Auto-generated destructor stub
}

NFA *AutomataOperator::orOperation(NFA *nfa1, NFA *nfa2) {

    // [TODO] --- to be implemented .....

    return 0;
}

NFA *AutomataOperator::andOperation(NFA *nfa1, NFA *nfa2) {

    // [TODO] --- to be implemented .....

    return 0;
}

NFA *AutomataOperator::closureOperation(NFA *nfa1, NFA *nfa2) {

    // [TODO] --- to be implemented .....

    return 0;
}

NFA *AutomataOperator::positiveClosureOperation(NFA *nfa1, NFA *nfa2) {

    // [TODO] --- to be implemented .....

    return 0;
}

NFA *AutomataOperator::optionalOperation(NFA *nfa1, NFA *nfa2) {

    // [TODO] --- to be implemented .....

    return 0;
}

vector<vector<int>> AutomataOperator::NFAToDFATable(vector<vector<set<int>>> nfaTransTable) {

    // declaring variables
    map<set<int>, int> dfaStatesMap; // mapping each state of dfa into one integer
    int counter = 0; // size of the dfa trans table
    queue<set<int>> toBeProcessed; // sets that not determined yet for each input
    vector<vector<int>> dfaTransTable; // the final trans table that will be returned
    set<int> firstCell = nfaTransTable[0][0]; // first set of states, Start state and its closures

    // set the first set of states in the queue
    toBeProcessed.push(firstCell);
    vector<int> temp (2, -1);
    dfaTransTable.insert(dfaTransTable.begin() + counter, temp); // init the row of the table
    dfaStatesMap[firstCell] = counter++;

    set<int> currentSet;
    while (!toBeProcessed.empty()) {
        currentSet = toBeProcessed.front();
        toBeProcessed.pop();

        set<int> nextSet; // to get each new set of next state closures

        // loop on each input 'i' except lambda input '0'; to get the next state
        for (int input = 1; input < 3; input++) {
            for (auto state : currentSet)
                nextSet.insert(nfaTransTable[state][input].begin(), nfaTransTable[state][input].end());
            nextSet = getClosures(nextSet, nfaTransTable);


            if (dfaStatesMap.count(nextSet) == 0) { // this new state is not put into the dfa map before
                // init the row of the table
                vector<int> temp (2, -1);
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