#ifndef TRANSITIONTABLECONVERTER_H
#define TRANSITIONTABLECONVERTER_H

#include "Bimap.h"
#include "NFA.h"
#include <vector>
#include <string>
#include <set>

using namespace std;

class TransitionTableConverter
{
    public:
        TransitionTableConverter();
        virtual ~TransitionTableConverter();
        vector<vector<set<int>>> NFAToTable(NFA * nfa);
        NFA tableToNFA(vector<vector<set<int>>> * table);
        void initInputsMap(vector<string> * inputs);
        void initStatesMap(vector<graph::State*> * states);
        void initAllInputsVector(NFA * nfa);

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
        static vector<vector<set<int>>> transTable;

        static Bimap <int, graph::State *> statesMap;
        static Bimap <int, string> inputsMap;

    protected:
    private:
        void initLambdaCol();
};

#endif // TRANSITIONTABLECONVERTER_H
