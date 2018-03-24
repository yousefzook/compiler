/*
 * DFA.cpp
 *
 *  Created on: Mar 16, 2018
 *      Author: yousef
 */

#include <iostream>
#include <set>
#include "DFA.h"
#include "TransitionTableConverter.h"

DFA::DFA() {
    // TODO Auto-generated constructor stub
}

DFA::~DFA() {
    // TODO Auto-generated destructor stub
}

vector<vector<int>> DFA::minimize(vector<vector<int>> dfaOld) {
    set<int> equivalentStates;
    bool same; // to indicate if the dfa is at it's minimal form
    while (!same) {
        same = true;
        for (int i = 0; i < dfaOld.size()-1; i++) { // for each state except the last state
            for (int j = i + 1; j < dfaOld.size(); j++) { // loop to find similarities
                if (dfaOld[i] == dfaOld[j] && sameType(i,j)){
                    equivalentStates.insert(j);
                    dfaOld.erase(dfaOld.begin()+j);
                    j--; // decrement j as the size is decremented by 1
                }
            }
            if(equivalentStates.empty()) // no change should be done if no equivalents
                continue;
            for (int row = 0; row < dfaOld.size(); row++) { // loop to remove similarities
                for (int col = 0; col < dfaOld.front().size(); col++) {
                    if (equivalentStates.find(dfaOld[row][col]) != equivalentStates.end()){
                        // replace the state with the other state
                        dfaOld[row][col] = i;
                        same = false;
                    }
                }
            }
            equivalentStates.clear();
        }
    }
    return dfaOld;
}

bool DFA::sameType(int s0, int s1){
    State* state0 = TransitionTableConverter::statesMap.valueForKey(s0);
    State* state1 = TransitionTableConverter::statesMap.valueForKey(s1);
    if(state0->accepted == state1->accepted)
        return true;
    return false;
}

