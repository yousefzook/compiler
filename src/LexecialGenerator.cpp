/*
 * LexecialGenerator.cpp
 *
 *  Created on: Mar 16, 2018
 *      Author: Rizk
 */

#include "LexecialGenerator.h"
#include "RuleParser.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;


LexecialGenerator::LexecialGenerator()
{
    // TODO Auto-generated constructor stub

}

LexecialGenerator::~LexecialGenerator()
{
    // TODO Auto-generated destructor stub
}

void LexecialGenerator::readRuleFile()
{
    ifstream myReadFile("/home/rizk/Desktop/rules.txt");
    string output;

    for( string line; getline( myReadFile, line ); )
    {
//        cout << line<<endl;
        RuleParser::parseLine(line);
    }
    myReadFile.close();
}

void LexecialGenerator::readProgramFile()
{


}

void LexecialGenerator::startLexical()
{
    readRuleFile();
    readProgramFile();
    NFA test=createMainGraph();
}

NFA LexecialGenerator::createMainGraph()
{
    NFA mainGraph;

    for(int i=0; i<RegularDefinition::mainGraphV.size(); i++)
    {
        // cout<<"main Graph start state : "<<mainGraph.startState->id<<"  Graph i :"<<mainGraphV[i].startState->id<<endl;
        mainGraph=AutomataOperator::orOperation(mainGraph,mainGraphV[i]);
    }
    //    cout<<"----------------------------------------------------------------"<<endl;
//    cout<<"Graph Information"<<endl;
//    cout<<"-----------------:"<<endl;
//    for (vector<graph::State*>::iterator i = mainGraph.allStates.begin(); i != mainGraph.allStates.end();
//            i++)
//    {
//        cout<<"Node Name:  "<<(*i)->id<<"*******size of vector: "<<"---"<<(*i)->nextStates.size()<<endl;
//
//    }
//
//    cout <<"-----------------------------------------------------"<<endl;
//    for (vector<graph::State*>::iterator i = mainGraph.allStates.begin(); i != mainGraph.allStates.end();
//            i++)
//    {
//        cout<<"Node Name:  "<<(*i)->id<<" size of vector: "<<"---"<<(*i)->nextStates.size()<<endl;
////        cout<<<endl;
//        for ( vector < pair<graph::State*,string > >::const_iterator it = (*i)->nextStates.begin() ;
//
//                it != (*i)->nextStates.end () ;  // Use (), and assuming itt was a typo
//                it++)
//        {
//            cout << it->first->id<<"---------"<<it->second<<endl;; // Use ->
//        }
//    }
//
//    cout<<"----------------------------------------------------------"<<endl;
    return mainGraph;

}

/*
 * [TODO] to be implemented ...........
 */

