//
// Created by yousef on 13/04/18.
//

#include <iostream>
#include "GroupedNFA.h"

GroupedNFA *GroupedNFA::groupedNFA = 0;

/*
 * Convert grouped NFA from graph to transition table
 * */
void GroupedNFA::buildNFATransTable() {
    initAllInputsVector();
    initInputsMap();
    initStatesMap();

    for (auto state: allStates) {
        // get src index in the table
        int srcInt = *statesMap.keysForValue(state).begin();

        // initialize each row with empty sets
        set<int> emptySet;
        vector<set<int>> emptyRow(allInputs.size() + 1, emptySet);
        transTable.insert(transTable.begin() + srcInt, emptyRow);

        // init the lambda transition with the state itself
        transTable[srcInt][0].insert(srcInt);

        // for each state loop on all edges it has
        vector<pair<State *, string>> nextStates = state->nextStates;
        for (auto nextState: nextStates) {

            State *dest = nextState.first;
            string trans = nextState.second;

            // get table indecies of destination and transition
            int destInt = *statesMap.keysForValue(dest).begin();
            int transInt = *inputsMap.keysForValue(trans).begin();

            // add the destination to the set of the destinations of the state
            transTable[srcInt][transInt].insert(destInt);

        }

    }
    prettyPrintTransTable();
}

/*
 * map each input for an int value
 * */
void GroupedNFA::initInputsMap() {

    // set the first input index is lambda , i.e. \L = 0
    inputsMap.set(0, "\\L");
    // map each input for an int value
    int counter = 1;
    for (auto input: allInputs) {
        cout << input << "  " << counter << endl;
        inputsMap.set(counter++, input);
    }
}

/*
 * map each state for an int value
 * */
void GroupedNFA::initStatesMap() {
    int counter = 0;
    for (auto state: GroupedNFA::allStates)
        GroupedNFA::statesMap.set(counter++, state);
}

void GroupedNFA::initAllInputsVector() {

    // get all possible inputs as a set
    set<string> allInputsSet;
    for (auto state: allStates) {
        for (auto edge: state->nextStates)
            if (edge.second != "\\L")
                allInputsSet.insert(edge.second);
    }

    // put each possible input in allInputs vector
    for (auto input: allInputsSet)
        allInputs.push_back(input);

}


GroupedNFA *GroupedNFA::getInstance() {
    if (groupedNFA == 0) {
        groupedNFA = new GroupedNFA();
    }
    return groupedNFA;
}


/*
 * private counstructor for skeleton implementation
 * */
GroupedNFA::GroupedNFA() {}

void GroupedNFA::prettyPrintTransTable() {
    cout << endl;
    cout << "States size: " << allStates.size() << endl;
    cout << "Inputs size: " << allInputs.size() << endl;
    for (auto input: allInputs)
        cout << input << "   ";
    cout << endl<< "-------------------------------------------------------------------------" << endl;
    for (int i = 0; i < transTable.size(); i++) {
        cout<<i<<" :: ";
        for (int j = 0; j < transTable[0].size(); j++) {
            if (transTable[i][j].empty())
                cout << "__";
            else {
                for (auto nextState: transTable[i][j])
                    cout << nextState << ',';
            }
            cout << "   ";
        }
        cout << endl;
    }
}