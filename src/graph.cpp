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
    // initialize startState
    startState = createState(false,555555);

}

graph::~graph()
{
    // TODO Auto-generated destructor stub
}

/* There will not be a physical edge , we just put
 * the destination state and its transition in
 * the source state nextStates vector
 *  */
void graph::addEdge(State* srcState, State* destState, string transition)
{
    srcState->nextStates.push_back(pair<State*, string>(destState, transition));
}

/* Initialize a new state and add it states vector.
 * */
graph::State* graph::createState(bool accepted,int id)
{
    State* newState = new State();
    newState->id=id;
    newState->accepted = accepted;
    allStates.push_back(newState);

    return newState;
}

/* Get all final states
 * */
vector<graph::State*> graph::getFinalStates()
{
    vector<State*> finalStates;
    for (vector<State*>::iterator i = allStates.begin(); i != allStates.end();
            i++)
    {
        if ((*i)->accepted == true)
        {
            finalStates.push_back((*i));
        }
    }
    return finalStates;
}
