#ifndef TRANSITIONTABLECONVERTER_H
#define TRANSITIONTABLECONVERTER_H

#include "Bimap.h"
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
        NFA tableToNFA(vector<vector<int>> * table);
        void initInputsMap(vector<string> * inputs);
        void initStatesMap(vector<graph::State*> * states);

        /*
        * transition table:
        *   src is used as row inex
        *   transition value is used as col index
        *   dest is set in each cell
        *
        *       letter | digit | ...
        * s0      s2   |  s1   | ..
        * s1        .
        * .             .
        * .                 .
        */
        static vector<vector<int>> transTable;

        static Bimap <int, graph::State *> statesMap;
        static Bimap <int, string> inputsMap;

    protected:
    private:
};

#endif // TRANSITIONTABLECONVERTER_H
