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

	DFA* minimize(DFA* dfa);
};

#endif /* DFA_H_ */
