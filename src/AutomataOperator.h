/*
 * AutomateOperator.h
 *
 *  Created on: Mar 16, 2018
 *      Author: yousef
 */

#ifndef AUTOMATAOPERATOR_H_
#define AUTOMATAOPERATOR_H_
#include "NFA.h"
#include "DFA.h"

class AutomataOperator
{
public:
    AutomataOperator();
    virtual ~AutomataOperator();

    NFA createBasicGraph(string key,string value);
    NFA orOperation(NFA nfa1, NFA nfa2);
    NFA andOperation(NFA nfa1, NFA nfa2);
    NFA closureOperation(NFA nfa1);
    NFA positiveClosureOperation(NFA nfa1);
    NFA optionalOperation(NFA nfa1);
    NFA orMainGraph(NFA nfa1, NFA nfa2);
    DFA* NFAToDFA(NFA* nfa);
    int getID();
    int ID;
};
#endif /* AUTOMATAOPERATOR_H_ */
