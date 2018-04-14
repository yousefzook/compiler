//
// Created by yousef on 13/04/18.
//

#ifndef CLEAN_COMPILER_GROUPEDNFA_H
#define CLEAN_COMPILER_GROUPEDNFA_H


using namespace std;

#include <vector>
#include "Graph.h"
#include "Bimap.h"
#include <set>

/*
 * Grouped NFA is implemented using singleton pattern
 * */
class GroupedNFA : public Graph {

public:
    vector<State *> allStates;
    vector<string> allInputs;
    map<State *, string> acceptedStatesName;

    static GroupedNFA *getInstance();

    void buildNFATransTable();

    void initInputsMap();

    void initStatesMap();

    void initAllInputsVector();

    /*
    * transition table:
    *   src is used as row inex
    *   transition value is used as col index
    *   dest is set in each cell
    *
    *       letter | digit | ...
    * s0      set{2}   |  set{1}   | ..
    * s1        .
    * .             .
    * .                 .
    */
    vector<vector<set<int>>> transTable;
    Bimap<int, State *> statesMap;
    Bimap<int, string> inputsMap;

private:
    void initLambdaCol();

    GroupedNFA();

    void prettyPrintTransTable();

    static GroupedNFA *groupedNFA;
};


#endif //CLEAN_COMPILER_GROUPEDNFA_H
