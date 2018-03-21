/*
 * graph.cpp
 *
 *  Created on: Mar 16, 2018
 *      Author: yousef
 */

#include "graph.h"

#include <string>

graph::graph() {
	// TODO Auto-generated constructor stub
	start_state = nullptr;
}

graph::~graph() {
	// TODO Auto-generated destructor stub
}

void graph::addEdge(State *src,State *dest, string value){
	src_v.push_back(src);
	dest_v.push_back(dest);
	value_v.push_back(value);
}
void graph::createState(bool acceptance){
	State state;
	state.acceptance = acceptance;
}
