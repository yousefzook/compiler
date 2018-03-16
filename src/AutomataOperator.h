/*
 * AutomateOperator.h
 *
 *  Created on: Mar 16, 2018
 *      Author: yousef
 */

#ifndef AUTOMATAOPERATOR_H_
#define AUTOMATAOPERATOR_H_

class AutomataOperator {
public:
	AutomataOperator();
	virtual ~AutomataOperator();

	NFA* orOperation(NFA* nfa1, NFA* nfa2);
	NFA* andOperation(NFA* nfa1, NFA* nfa2);
	NFA* closureOperation(NFA* nfa1, NFA* nfa2);
	NFA* positiveClosureOperation(NFA* nfa1, NFA* nfa2);
	NFA* optionalOperation(NFA* nfa1, NFA* nfa2);
	DFA* NFAToDFA(NFA* nfa);
};

#endif /* AUTOMATAOPERATOR_H_ */
