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
    };

    /*
     * Create a state , given its previous and next states
     * and if it's accepted or not
     * */
    State* createState(vector<pair<State*, string> > prevStates,
                       vector<pair<State*, string> > nextStates, bool accepted);

    State * startState;
    string grapgName;
private:
};
#endif
