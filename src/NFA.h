/*
 * NFA.h
 *
 *  Created on: Mar 16, 2018
 *      Author: yousef
 */
#include <vector>
#include "Graph.h"

using namespace std;

#ifndef NFA_H_
#define NFA_H_

class NFA: public Graph{
public:
	NFA();
	virtual ~NFA();

	vector<State *>  getClosures(State * state);
};

#endif /* NFA_H_ */
