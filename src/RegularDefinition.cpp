/*
 * RegularDefinition.cpp
 *
 *  Created on: Mar 16, 2018
 *      Author: yousef
 */

#include "RegularDefinition.h"

#include <string>
#include <map>
#include <vector>

using namespace std;

RegularDefinition::RegularDefinition()
{
// TODO Auto-generated constructor stub
    string key="E";
    string value="e";
    RegularDefinition::definition.push_back(std::make_pair(key,value) );
    key="L";
    value="";
    RegularDefinition::definition.push_back(std::make_pair(key,value) );
}

RegularDefinition::~RegularDefinition()
{
    // TODO Auto-generated destructor stub
}

bool compare(string type, char c)
{
    // to be implemented
    return 0;
}

void RegularDefinition::setKeywords(string keyword)
{
    RegularDefinition::keywords.push_back(keyword);
}

void RegularDefinition::setOperators(string key,vector<string>values)
{
    RegularDefinition::operators.insert(make_pair(key,values));
}

void RegularDefinition::setDefinitions(string key,string value)
{
    RegularDefinition::definition.push_back(std::make_pair(key,value) );
}

void RegularDefinition::setUnMatchedDefinitions(string key,string value)
{

    RegularDefinition::unMatchedDefinition.push_back(std::make_pair(key,value) );
}

void RegularDefinition::setPunctuation(vector<string>punc)
{
    RegularDefinition::punctuation.insert(RegularDefinition::punctuation.end(), punc.begin(), punc.end());
}

NFA RegularDefinition::handleClosure(NFA closureGraph)
{
    cout<<"clousere ////"<<endl;
    return AutomataOperator::closureOperation(closureGraph);
}

NFA RegularDefinition::handlePositiveClosure(NFA closureGraph)
{
    return AutomataOperator::positiveClosureOperation(closureGraph);
}

NFA RegularDefinition::handleOr(vector<string>conditions)
{
    NFA orGraph,temp2;
    orGraph.startState->id=AutomataOperator::getID();
    cout<<"orGraph ID "<<orGraph.startState->id<<"++++++++++++++++++"<<endl;

    indexExp++;
    string condition=conditions[indexExp];
    if((condition[0]>=65&&condition[0]<=90)||(condition[0]>=97&&condition[0]<=122))
    {
        if(condition[condition.size()-1]=='*')
        {
            condition.erase(condition.size() - 1);
            temp2=handleClosure(AutomataOperator::createBasicGraph(condition));
            orGraph=AutomataOperator::andOperation(orGraph,temp2);
        }
        else if(condition[condition.size()-1]=='+')
        {
            condition.erase(condition.size() - 1);
            temp2=handlePositiveClosure(AutomataOperator::createBasicGraph(condition));
            orGraph=AutomataOperator::andOperation(orGraph,temp2);
        }
        else
        {
            temp2=AutomataOperator::createBasicGraph(condition);
            orGraph=AutomataOperator::andOperation(orGraph,temp2);
        }
    }
    indexExp++;
    condition=conditions[indexExp];
    while(indexExp!=conditions.size()&&condition=="." )
    {
        temp2=AutomataOperator::createBasicGraph(condition);
        orGraph=AutomataOperator::andOperation(orGraph,temp2);
        indexExp++;
        condition=conditions[indexExp];
        temp2=AutomataOperator::createBasicGraph(condition);
        orGraph=AutomataOperator::andOperation(orGraph,temp2);
        indexExp++;
        if(indexExp==conditions.size())
            break;
        condition=conditions[indexExp];
    }
    return orGraph;
}

NFA RegularDefinition::handleBrackets(vector<string> conditions)
{
    NFA bracketGraph,temp2;
    bracketGraph.startState->id=AutomataOperator::getID();
    cout<<"bracket ID "<<bracketGraph.startState->id<<"++++++++++++++++++++++++"<<endl;
    indexExp++;
    string condition;
    while (conditions[indexExp]!=")")
    {
        condition=conditions[indexExp];
        if((condition[0]>=65&&condition[0]<=90)||(condition[0]>=97&&condition[0]<=122))
        {
            int t=condition[0];
            if(condition[condition.size()-1]=='*')
            {
                condition.erase(condition.size() - 1);
                temp2=handleClosure(AutomataOperator::createBasicGraph(condition));
                bracketGraph=AutomataOperator::andOperation(bracketGraph,temp2);
            }
            else if(condition[condition.size()-1]=='+')
            {
                condition.erase(condition.size() - 1);
                temp2=handlePositiveClosure(AutomataOperator::createBasicGraph(condition));
                bracketGraph=AutomataOperator::andOperation(bracketGraph,temp2);
            }
            else
            {
                temp2=AutomataOperator::createBasicGraph(condition);
                bracketGraph=AutomataOperator::andOperation(bracketGraph,temp2);
            }
        }
        else if(condition=="(")
        {
            temp2=handleBrackets(conditions);
            bracketGraph=AutomataOperator::andOperation(bracketGraph,temp2);
        }
        else if(condition==".")
        {
            temp2=AutomataOperator::createBasicGraph(condition);
            bracketGraph=AutomataOperator::andOperation(bracketGraph,temp2);
        }
        else if(condition=="|")
        {
            temp2=handleOr(conditions);
            indexExp--;
            bracketGraph=AutomataOperator::orOperation(bracketGraph,temp2);
        }
        indexExp++;
        if(indexExp==conditions.size())
            break;
        condition=conditions[indexExp];
    }
    if(indexExp==conditions.size()-1)
        return bracketGraph;

    if(conditions[indexExp+1]=="*")
    {
        indexExp++;
        return RegularDefinition::handleClosure(bracketGraph);
    }
    cout<<"done holloe"<<endl;
    if(conditions[indexExp+1]=="+")
    {
        indexExp++;
        return RegularDefinition::handlePositiveClosure(bracketGraph);
    }
    if(conditions[indexExp]==")"||indexExp==conditions.size())
        return bracketGraph;


    return bracketGraph;
}



void RegularDefinition::createSubGraph(string name,vector<string> conditions)
{
    NFA largeGraph,temp;
    largeGraph.startState->id=AutomataOperator::getID();
    cout<<"largeGraph ID "<<largeGraph.startState->id<<"++++++++++++++++++"<<endl;

    indexExp=0;
    string condition;
    while(indexExp>=0&&indexExp!=conditions.size())
    {
        condition=conditions[indexExp];
        if((condition[0]>=65&&condition[0]<=90)||(condition[0]>=97&&condition[0]<=122))
        {
            if(condition[condition.size()-1]=='*')
            {
                condition.erase(condition.size() - 1);
                temp=handleClosure(AutomataOperator::createBasicGraph(condition));
                largeGraph=AutomataOperator::andOperation(largeGraph,temp);
            }
            else if(condition[condition.size()-1]=='+')
            {
                condition.erase(condition.size() - 1);
                temp=handlePositiveClosure(AutomataOperator::createBasicGraph(condition));
                largeGraph=AutomataOperator::andOperation(largeGraph,temp);
            }
            else
            {
                temp=AutomataOperator::createBasicGraph(condition);
                largeGraph=AutomataOperator::andOperation(largeGraph,temp);
            }
        }
        else if(condition=="(")
        {
            temp=handleBrackets(conditions);
            largeGraph=AutomataOperator::andOperation(largeGraph,temp);
        }
        else if(condition==".")
        {
            temp=AutomataOperator::createBasicGraph(condition);
            largeGraph=AutomataOperator::andOperation(largeGraph,temp);
        }
        else if(condition=="|")
        {
            temp=handleOr(conditions);
            indexExp--;
            largeGraph=AutomataOperator::orOperation(largeGraph,temp);
        }
        indexExp++;
    }

    for (vector<graph::State*>::iterator i = largeGraph.allStates.begin(); i != largeGraph.allStates.end();
            i++)
    {
        cout<<"Node Name:  "<<(*i)->id<<"*******size of vector: "<<"---"<<(*i)->nextStates.size()<<endl;

    }

    cout <<"-----------------------------------------------------"<<endl;
    for (vector<graph::State*>::iterator i = largeGraph.allStates.begin(); i != largeGraph.allStates.end();
            i++)
    {
        cout<<"Node Name:  "<<(*i)->id<<" size of vector: "<<"---"<<(*i)->nextStates.size()<<endl;
//        cout<<<endl;
        for ( vector < pair<graph::State*,string > >::const_iterator it = (*i)->nextStates.begin() ;

                it != (*i)->nextStates.end () ;  // Use (), and assuming itt was a typo
                it++)
        {
            cout << it->first->id<<"---------"<<it->second<<endl;; // Use ->
        }
    }

    cout<<"----------------------------------------------------------"<<endl;

    RegularDefinition::mainGraphV.push_back(largeGraph);
}

