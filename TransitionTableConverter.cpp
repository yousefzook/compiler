#include "TransitionTableConverter.h"


TransitionTableConverter::TransitionTableConverter() {
    //ctor
}

TransitionTableConverter::~TransitionTableConverter() {
    //dtor
}

// initializing static members
//vector<graph::State *> graph::allStates;
/*
vector<string> graph::allInputs;
*/
Bimap<int, graph::State *> TransitionTableConverter::statesMap;
Bimap<int, string> TransitionTableConverter::inputsMap;
vector<vector<set<int>>> TransitionTableConverter::transTable;


void TransitionTableConverter::NFAToTable(NFA *nfa) {

    graph::State *dest, *src;
    string trans;
    int destInt, srcInt, transInt;

    for (auto iter: nfa->allStates) {

        // get src index in the table
        src = iter;
        srcInt = *TransitionTableConverter::statesMap.keysForValue(src).begin();
        // initialize each row with empty sets
        set<int> emptySet;
        vector<set<int>> emptyRow(nfa->allInputs.size(), emptySet);
        transTable.insert(transTable.begin()+srcInt,emptyRow);
        // init the lambda transition with the state itself
        TransitionTableConverter::transTable[srcInt][0].insert(srcInt);

        // for each state loop on all edges it has
        vector<pair<graph::State *, string>> nextStates = iter->nextStates;
        for (auto iter2: nextStates) {

            dest = iter2.first;
            trans = iter2.second;

            // get table indecies
            destInt = *TransitionTableConverter::statesMap.keysForValue(dest).begin();
            transInt = *TransitionTableConverter::inputsMap.keysForValue(trans).begin();

            // add the destination to the set of the destinations of the state
            TransitionTableConverter::transTable[srcInt][transInt].insert(destInt);

        }

    }
}

NFA TransitionTableConverter::tableToNFA(vector<vector<set<int>>> *table) {

}

void TransitionTableConverter::initInputsMap(vector<string> *inputs) {

    // set the first input index is lambda , i.e. /L = 0
    TransitionTableConverter::inputsMap.set(0,"L");

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

void TransitionTableConverter::initAllInputsVector(NFA * nfa){

    // get all possible inputs as a set
    set<string> allInputsSet;
    for(auto s: nfa->allStates){
        for(auto edge: s->nextStates)
            if(edge.second != "L")
                allInputsSet.insert(edge.second);
    }

    // put each possible input in allInputs vector
    for(auto input: allInputsSet)
        nfa->allInputs.push_back(input);

}
