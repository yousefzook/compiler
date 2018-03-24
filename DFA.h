/*
 * DFA.h
 *
 *  Created on: Mar 16, 2018
 *      Author: yousef
 */
#include "graph.h"
#ifndef DFA_H_
#define DFA_H_

class DFA: public graph{
public:
	DFA();
	virtual ~DFA();

	vector<vector<int>> minimize(vector<vector<int>> dfa);

private:
	/* check if state 0 and state 1 are both accepted or not
	 * */
	bool sameType(int s0, int s1);
};

#endif /* DFA_H_ */
