//
// Created by yousef on 13/04/18.
//

#ifndef CLEAN_COMPILER_GROUPEDNFA_H
#define CLEAN_COMPILER_GROUPEDNFA_H
#include <string>
using namespace std;
#include <vector>
#include "Graph.h"

class GroupedNFA {

public:
    vector<Graph::State*> allStates;
    vector<string> allInputs;
};


#endif //CLEAN_COMPILER_GROUPEDNFA_H
