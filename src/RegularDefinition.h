/*
 * RegularDefinition.h
 *
 *  Created on: Mar 16, 2018
 *      Author: Rizk
 */

#include "RuleParser.h"
#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

#ifndef REGULARDEFINITION_H_
#define REGULARDEFINITION_H_

class RegularDefinition
{
public:
    RegularDefinition();
    virtual ~RegularDefinition();

    bool compare(string type, char c);
    void setKeywords(string keyword);
    void setOperators(string key,vector<string>values);
    void setDefinitions(string key,string value);
    void setPunctuation(vector<string>punc);

private:
    map<string, string > definition;
    vector<string> keywords;
    map <string, vector<string> > operators;
    vector<string> punctuation;
};


#endif /* REGULARDEFINITION_H_ */
