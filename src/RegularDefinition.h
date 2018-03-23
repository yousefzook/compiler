/*
 * RegularDefinition.h
 *
 *  Created on: Mar 16, 2018
 *      Author: Rizk
 */

#include "graph.h"
#include "AutomataOperator.h"

#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

#ifndef REGULARDEFINITION_H_
#define REGULARDEFINITION_H_

class RegularDefinition: public AutomataOperator
{
public:
    RegularDefinition();
    virtual ~RegularDefinition();

    bool compare(string type, char c);
    void setKeywords(string keyword);
    void setOperators(string key,vector<string>values);
    void setDefinitions(string key,string value);
    void setUnMatchedDefinitions(string key,string value);
    void setPunctuation(vector<string>punc);
    void createSubGraph(string name,vector<string> conditions);
    string L="";
    string E="e";
    vector< pair<string, string> > unMatchedDefinition;


    NFA handleClosure(NFA closureGraph);
    NFA handlePositiveClosure(NFA closureGraph);
    NFA handleOr(string key,vector<string>conditions);
    NFA handleBrackets(string key,vector<string> conditions);
    vector<NFA> mainGraphV;
private:
    vector< pair<string, string> > definition;
    vector<string> keywords;
    map <string, vector<string> > operators;
    vector<string> punctuation;
    int indexExp;
};


#endif /* REGULARDEFINITION_H_ */
