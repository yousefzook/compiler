/*
 * DFA.h
 *
 *  Created on: Mar 16, 2018
 *      Author: yousef
 */

#include "Graph.h"

#ifndef DFA_H_
#define DFA_H_

class DFA: public Graph{
public:
	DFA();
	virtual ~DFA();

	DFA* minimize(DFA* dfa);
};

#endif /* DFA_H_ */
