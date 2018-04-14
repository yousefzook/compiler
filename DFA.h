//
// Created by yousef on 27/03/18.
//

#ifndef CLEAN_COMPILER_DFA_H
#define CLEAN_COMPILER_DFA_H

#include <set>
#include <vector>
#include <string>
#include <map>

using namespace std;

class DFA {

public:
    vector<vector<int>> transTable;
    // each accepted state with it's token -name-
    map<int, string> acceptedStates;

    void minimizeDFA();

};


#endif //CLEAN_COMPILER_DFA_H
