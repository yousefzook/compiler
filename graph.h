/*
 * graph.h
 *
 *  Created on: Mar 16, 2018
 *      Author: Yousef Zook
 */
#include <vector>
#include <string>
using namespace std;

#ifndef GRAPH_H_
#define GRAPH_H_


class graph {
public:
	graph();
	virtual ~graph();

	struct State {
        vector<pair<State*, string>> nextStates;
		bool acceptance;
	};

	void addEdge(State *s1, State *s2, string value);
	void createState(bool acceptance);

	static vector<State*> allStates;
	static vector<string> allInputs;

private:
	vector<State *> src_v;
	vector<State *> dest_v;
	vector<string> value_v;
	State * start_state;
};

#endif /* GRAPH_H_ */
