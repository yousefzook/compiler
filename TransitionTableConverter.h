#ifndef TRANSITIONTABLECONVERTER_H
#define TRANSITIONTABLECONVERTER_H

#include "NFA.h"
#include <vector>
#include <string>

using namespace std;

class TransitionTableConverter
{
    public:
        TransitionTableConverter();
        virtual ~TransitionTableConverter();
        vector<vector<int>> NFAToTable(NFA * nfa);
        NFA tableToNFA(vector<vector<int>> table);
        void initInputsMap(vector<string> * inputs);
        void initStatesMap(vector<graph::State*> * states);
    protected:
    private:
};

#endif // TRANSITIONTABLECONVERTER_H
