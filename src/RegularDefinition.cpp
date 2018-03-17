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
    // RegularDefinition::keyword.insert(RegularDefinition::keyword.end(), keywords.begin(), keywords.end());
    RegularDefinition::keywords.push_back(keyword);
}

void RegularDefinition::setOperators(string key,vector<string>values)
{
    RegularDefinition::operators.insert(make_pair(key,values));
}

void RegularDefinition::setDefinitions(string key,string value)
{
    RegularDefinition::definition.insert ( std::pair<string,string>(key,value) );
}

void RegularDefinition::setPunctuation(vector<string>punc)
{
    RegularDefinition::punctuation.insert(RegularDefinition::punctuation.end(), punc.begin(), punc.end());
}


