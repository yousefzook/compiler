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

void LexecialGenerator::startLexical()
{
    readRuleFile();
    NFA nfa = createMainGraph();
    TransitionTableConverter converter;
    converter.initAllInputsVector(&nfa);
    converter.initStatesMap(&nfa.allStates);
    converter.initInputsMap(&nfa.allInputs);

    vector<vector<set<int>>> nfaTransTable;
    converter.NFAToTable(&nfa);
    nfaTransTable = TransitionTableConverter::transTable;

    cout << "oldddd \n";
    for (auto it: nfaTransTable) {
        cout << "output: ";
        for (auto it2: it) {
            for (auto it3: it2) {
                cout << it3;
                cout<<"   ";
            }
            cout << "  ,, ";
        }
        cout<<"\n";
    }

    AutomataOperator automataOperator;
    vector<vector<int>> dfaTransTable;
    dfaTransTable = automataOperator.NFAToDFATable(nfaTransTable,&nfa);

    cout << "\n dfa from nfa is : \n\n";
    for (auto it: dfaTransTable) {
        cout << "output: ";
        for (auto it2: it) {
            cout << it2;
            cout << " , ";
        }
        cout << "\n";
    }
    readProgramFile();

}

void LexecialGenerator::readRuleFile()
{
    ifstream myReadFile("/home/yahia/Desktop/CProjects/Compiler/rules.txt");
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


NFA LexecialGenerator::createMainGraph()
{
    NFA mainGraph;

    for(int i=0; i<RegularDefinition::mainGraphV.size(); i++)
    {
        // cout<<"main Graph start state : "<<mainGraph.startState->id<<"  Graph i :"<<mainGraphV[i].startState->id<<endl;
        mainGraph=AutomataOperator::orMainGraph(mainGraph,mainGraphV[i]);
    }
    cout<<"----------------------------------------------------------------"<<endl;
    cout<<"Graph Information"<<endl;
    cout<<"all states size = "<<mainGraph.allStates.size()<<endl;
    cout<<"-----------------:"<<endl;
    for (vector<graph::State*>::iterator i = mainGraph.allStates.begin(); i != mainGraph.allStates.end();
            i++)
    {
        cout<<"Graph Name :  "<< (*i)->graphName<<"     Node Name:  "
            <<(*i)->id<<" size of vector: "<<"---"<<(*i)->nextStates.size()<<endl;
    }

    cout <<"-----------------------------------------------------"<<endl;
    for (vector<graph::State*>::iterator i = mainGraph.allStates.begin(); i != mainGraph.allStates.end();
            i++)
    {
        cout<<"Graph Name :  "<< (*i)->graphName<<"     Node Name:  "
            <<(*i)->id<<" size of vector: "<<"---"<<(*i)->nextStates.size()<<endl;

        for ( vector < pair<graph::State*,string > >::const_iterator it = (*i)->nextStates.begin() ;

                it != (*i)->nextStates.end () ;  // Use (), and assuming itt was a typo
                it++)
        {
            cout << it->first->id<<"---------"<<it->second<<endl;; // Use ->
        }
    }

    cout<<"----------------------------------------------------------"<<endl;
    return mainGraph;

}

/*
 * [TODO] to be implemented ...........
 */

