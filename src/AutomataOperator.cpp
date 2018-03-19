/*
 * AutomateOperator.cpp
 *
 *  Created on: Mar 16, 2018
 *      Author: yousef
 */

#include "AutomataOperator.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

AutomataOperator::AutomataOperator()
{
    // TODO Auto-generated constructor stub

}

AutomataOperator::~AutomataOperator()
{
    // TODO Auto-generated destructor stub
}

NFA* AutomataOperator::createBasicGraph(string value)
{
    NFA newGraph;
    vector<pair<graph::State*,string> >prev;
    prev.push_back(std::make_pair(newGraph.startState,value));
    vector<pair<graph::State*,string> >next;
    newGraph.createState(prev,next,true);
    NFA *largeGraphPointer=&newGraph;
    return largeGraphPointer;
}

NFA* AutomataOperator::orOperation(NFA* nfa1, NFA* nfa2)
{

    // [TODO] --- to be implemented .....

    return nfa1;
}

NFA* AutomataOperator::andOperation(NFA* nfa1, NFA* nfa2)
{

    // [TODO] --- to be implemented .....

    return 0;
}

NFA* AutomataOperator::closureOperation(NFA* nfa1)
{

    // [TODO] --- to be implemented .....
NFA *R;
    return R;
}


NFA* AutomataOperator::positiveClosureOperation(NFA* nfa1)
{

    // [TODO] --- to be implemented .....


    return 0;
}

NFA* AutomataOperator::optionalOperation(NFA* nfa1, NFA* nfa2)
{

    // [TODO] --- to be implemented .....

    return 0;
}
/*
DFA* NFAToDFA(NFA* nfa)
{

    // [TODO] --- to be implemented .....

    return 0;
}*/
