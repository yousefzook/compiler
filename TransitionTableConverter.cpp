#include "TransitionTableConverter.h"


TransitionTableConverter::TransitionTableConverter() {
    //ctor
}

TransitionTableConverter::~TransitionTableConverter() {
    //dtor
}

// initializing static members
vector<graph::State *> graph::allStates;
vector<string> graph::allInputs;
Bimap<int, graph::State *> TransitionTableConverter::statesMap;
Bimap<int, string> TransitionTableConverter::inputsMap;
vector<vector<set<int>>> TransitionTableConverter::transTable;

vector<vector<set<int>>> TransitionTableConverter::NFAToTable(NFA *nfa) {

    graph::State *dest, *src;
    string trans;
    int destInt, srcInt, transInt;
    set<int> *cell; // pointer for a cell in the table rows -set type-

    for (vector<graph::State *>::iterator iter = graph::allStates.begin(); iter != graph::allStates.end(); ++iter) {

        // get src index in the table
        src = *iter;
        srcInt = *TransitionTableConverter::statesMap.keysForValue(src).begin();
        // initialize each row with empty sets
        set<int> emptySet;
        vector<set<int>> emptyRow(graph::allInputs.size(), emptySet);
        transTable[srcInt] = emptyRow;
        // init the lambda transition with the state itself
        cell = &TransitionTableConverter::transTable[srcInt][0];
        cell->insert(srcInt);

        // for each state loop on all edges it has
        graph::State *temp = *iter;
        vector<pair<graph::State *, string>> nextStates = temp->nextStates;
        for (vector<pair<graph::State *, string>>::iterator iter2 = nextStates.begin();
             iter2 != nextStates.end(); ++iter2) {

            dest = iter2->first;
            trans = iter2->second;

            // get table indecies
            destInt = *TransitionTableConverter::statesMap.keysForValue(dest).begin();
            transInt = *TransitionTableConverter::inputsMap.keysForValue(trans).begin();

            // add the destination to the set of the destinations of the state
            cell = &TransitionTableConverter::transTable[srcInt][transInt];
            cell->insert(destInt);

        }

    }
}

NFA TransitionTableConverter::tableToNFA(vector<vector<set<int>>> *table) {

}

void TransitionTableConverter::initInputsMap(vector<string> *inputs) {

    // set the first input index is lambda , i.e. /L = 0
    TransitionTableConverter::inputsMap.set(0,"\\L");

    // map each input for an int value
    int counter = 0;
    for(auto it: *inputs)
        TransitionTableConverter::inputsMap.set(counter++, it);
}

void TransitionTableConverter::initStatesMap(vector<graph::State *> *states) {
    // map each state for an int value
    int counter = 0;
    for(auto it: *states)
        TransitionTableConverter::statesMap.set(counter++, it);
}
