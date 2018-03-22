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

vector<vector<int>> AutomataOperator::NFAToDFA(vector<vector<set<int>>> nfaTransTable) {

    // declaring variables
    map<set<int>, int> dfaStatesMap; // mapping each state of dfa into one integer
    int counter = 0; // size of the dfa trans table
    queue<set<int>> toBeProcessed; // sets that not determined yet for each input
    vector<vector<int>> dfaTransTable; // the final trans table that will be returned
    set<int> firstCell = nfaTransTable[0][0]; // first set of states, Start state and its closures

    // set the first set of states in the queue
    toBeProcessed.push(firstCell);

    set<int> currentSet;
    while (!toBeProcessed.empty()) {
        currentSet = toBeProcessed.front();
        toBeProcessed.pop();

        set<int> nextSet; // to get each new set of next state closures

        // loop on each input 'i' to get the next state
        for (int input = 0; input < TransitionTableConverter::inputsMap.size(); input++) {
            for (auto state : currentSet)
                nextSet.insert(nfaTransTable[state][input].begin(), nfaTransTable[state][input].end());
            nextSet = getClosures(nextSet);


            if (dfaStatesMap.count(nextSet) == 0) { // this new state is not put into the dfa map before
                dfaStatesMap[nextSet] = counter++;
                toBeProcessed.push(nextSet);
            }

            // set the cell in the dfa trans table
            dfaTransTable[dfaStatesMap[currentSet]][input] = dfaStatesMap[nextSet];
        }
    }

    return dfaTransTable;
}

set<int> AutomataOperator::getClosures(set<int>) {
    // to be implemented ......
}