/*
 * graph.cpp
 *
 *  Created on: Mar 16, 2018
 *      Author: yousef
 */

#include "graph.h"


#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;


graph::graph()
{
    // initialize start state
    vector<pair<State*, string> > nextStates;
    vector<pair<State*, string> > prevStates;
    startState = createState(prevStates, nextStates, false);
}

graph::~graph()
{
    // TODO Auto-generated destructor stub
}

//void Graph::addEdge(State *src,State *dest, string value){
//	src_v.push_back(src);
//	dest_v.push_back(dest);
//	value_v.push_back(value);
//}
graph::State* graph::createState(vector<pair<State*, string> > prevStates,
                                 vector<pair<State*, string> > nextStates, bool accepted)
{
    State* state = new State();
    state->accepted = accepted;
    state->nextStates = nextStates;

    for (vector<pair<State*, string> >::iterator i = prevStates.begin();
            i < prevStates.end(); i++)
    {

    }
    return state;
}

//int main(int argc, char **argv) {
////	Graph* g = new Graph();
////	g->
//}

