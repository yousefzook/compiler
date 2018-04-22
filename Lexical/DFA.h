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

class DFA
{

public:
    vector<vector<int>> transTable;

    // each accepted state with it's token -name-
    map<int, string> acceptedStates;

    vector<int> setIndex; //index of each set as it becomes the same index of the new states of the new dfa table
    vector<vector<vector<int>>> equivSets; //hold subsets of each level of partitioning
    int counter; //keep track of current level we currently in partitioning ,
    vector<int> markingVec; //show wether this state is already taken in a set or not (in actual code initialize it to be (# of states,0))

    void minimizeDFA();


    void prettyPrintTransTable();


private:
    int check_status(int statusIndex);

    void print_accepted_Map();

    void init_DFA();

    void print_subsets(vector<vector<int>> arr);

    void partition();

    vector<vector<int>> subset(vector<int> equivSet);

    void build_min_DFA();
};


#endif //CLEAN_COMPILER_DFA_H
