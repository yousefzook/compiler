#include "TransitionTableConverter.h"


TransitionTableConverter::TransitionTableConverter() {
    //ctor
}

TransitionTableConverter::~TransitionTableConverter() {
    //dtor
}

// initializing static members
vector<graph::State *> graph::allStates;
Bimap<int, graph::State *> TransitionTableConverter::statesMap;
Bimap<int, string> TransitionTableConverter::inputsMap;
vector<vector<set<int>>> TransitionTableConverter::transTable;

vector<vector<set<int>>> TransitionTableConverter::NFAToTable(NFA *nfa) {

    graph::State *dest, *src;
    string trans;
    int destInt, srcInt, transInt;

    for (vector<graph::State *>::iterator iter = graph::allStates.begin(); iter != graph::allStates.end(); ++iter) {
        src = *iter;
        // get src index in the table
        srcInt = *TransitionTableConverter::statesMap.keysForValue(src).begin();

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

            vector<set<int>>::iterator it;
            vector<set<int>> row;
            row = TransitionTableConverter::transTable[srcInt];
            it = row.begin();
            set<int> * cell = &row[transInt];
            cell->insert(destInt);
//            row.insert(it + transInt, addedDest);

        }

    }
}


NFA TransitionTableConverter::tableToNFA(vector<vector<set<int>>> *table) {

}

void TransitionTableConverter::initInputsMap(vector<string> *inputs) {
}

void TransitionTableConverter::initStatesMap(vector<graph::State *> *states) {
}
