/*
 * AutomateOperator.h
 *
 *  Created on: Mar 16, 2018
 *      Author: yousef
 */
#include "NFA.h"
#include "DFA.h"
#include <set>
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
	vector<vector<int>> NFAToDFATable(vector<vector<set<int>>>);
private:
	set<int> getClosures(set<int>, vector<vector<set<int>>>);
};

#endif /* AUTOMATAOPERATOR_H_ */
