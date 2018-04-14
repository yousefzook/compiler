//
// Created by yousef on 13/04/18.
//

#ifndef CLEAN_COMPILER_GROUPEDNFA_H
#define CLEAN_COMPILER_GROUPEDNFA_H

#include <string>

using namespace std;

#include <vector>
#include "Graph.h"

/*
 * Grouped NFA is implemented using singleton pattern
 * */
class GroupedNFA {

public:
    static GroupedNFA *getInstance();

    vector<Graph::State *> allStates;
    vector<string> allInputs;
protected:
    GroupedNFA();

private:
    static GroupedNFA *groupedNFA;
};


#endif //CLEAN_COMPILER_GROUPEDNFA_H
