/*
 * graph.h
 *
 *  Created on: Mar 16, 2018
 *      Author: Yousef Zook
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

class graph
{
public:
    graph();
    virtual ~graph();

    struct State
    {
        vector<pair<State*, string> > nextStates;
        bool accepted;
        int id;
        string graphName;
    };

    /* Create a state choosing whether it's accepted or not.
     * */
    State* createState(bool accepted,int id, string graphName);

    /* Create an edge with a transition between two states.
     * */
    void addEdge(State* srcState, State* destState, string transition);

    /* Remove state from the graph and delete all
     * its corresponding edges.
     * */
//	void deleteState(State* state);

    /* Get all final states
     * */
    vector<State*> getFinalStates();

public:

    /* It's the user duty to use this start state
     * as the graph actual start state because
     * it will be used in other operations
     */
    State * startState;

    /* Vector contains all created states
     */
    vector<State*> allStates;
};

#endif /* GRAPH_H_ */
