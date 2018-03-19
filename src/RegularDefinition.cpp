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

NFA* RegularDefinition::handleClosure(NFA* closureGraph)
{
    return AutomataOperator::closureOperation(closureGraph);
}

NFA* RegularDefinition::handlePositiveClosure(NFA* closureGraph)
{
    return AutomataOperator::positiveClosureOperation(closureGraph);
}

NFA* RegularDefinition::handleOr(vector<string>conditions)
{
    NFA* orGraph,*temp2;
    indexExp++;
    string condition=conditions[indexExp];
    if((condition[0]>=65&&condition[0]<=90)||(condition[0]>=97&&condition[0]<=128))
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
    //if(indexExp==conditions.size()-1)
    return orGraph;
}

NFA* RegularDefinition::handleBrackets(vector<string> conditions)
{
    NFA* bracketGraph,*temp2;
    indexExp++;
    string condition;
    while (conditions[indexExp]!=")")
    {
        condition=conditions[indexExp];
        if((condition[0]>=65&&condition[0]<=90)||(condition[0]>=97&&condition[0]<=128))
        {
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
        cout<<"Done"<<endl;
        return RegularDefinition::handleClosure(bracketGraph);
    }
    if(conditions[indexExp+1]=="+")
    {
        indexExp++;
        return RegularDefinition::handlePositiveClosure(bracketGraph);
    }
    return bracketGraph;
}



void RegularDefinition::createSubGraph(string name,vector<string> conditions)
{
    NFA largeGraph;
    NFA *largeGraphPointer,*temp;
    indexExp=0;
    string condition;
    while(indexExp>=0&&indexExp!=conditions.size())
    {
        condition=conditions[indexExp];
        if((condition[0]>=65&&condition[0]<=90)||(condition[0]>=97&&condition[0]<=128))
        {
            if(condition[condition.size()-1]=='*')
            {
                condition.erase(condition.size() - 1);
                temp=handleClosure(AutomataOperator::createBasicGraph(condition));
                largeGraphPointer=AutomataOperator::andOperation(largeGraphPointer,temp);
            }
            else if(condition[condition.size()-1]=='+')
            {
                condition.erase(condition.size() - 1);
                temp=handlePositiveClosure(AutomataOperator::createBasicGraph(condition));
                largeGraphPointer=AutomataOperator::andOperation(largeGraphPointer,temp);
            }
            else
            {
                temp=AutomataOperator::createBasicGraph(condition);
                largeGraphPointer=AutomataOperator::andOperation(largeGraphPointer,temp);
            }
        }
        else if(condition=="(")
        {
            cout<<"sent"<<endl;
            temp=handleBrackets(conditions);
            cout<<"returned"<<endl;
            largeGraphPointer=AutomataOperator::andOperation(largeGraphPointer,temp);
        }
        else if(condition==".")
        {
            temp=AutomataOperator::createBasicGraph(condition);
            largeGraphPointer=AutomataOperator::andOperation(largeGraphPointer,temp);
        }
        else if(condition=="|")
        {
            temp=handleOr(conditions);
            indexExp--;
            largeGraphPointer=AutomataOperator::orOperation(largeGraphPointer,temp);
        }
        indexExp++;
    }
    RegularDefinition::mainGraphV.push_back(largeGraph);
}

