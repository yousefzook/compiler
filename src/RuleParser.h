/*
 * RuleParser.h
 *
 *  Created on: Mar 16, 2018
 *      Author: yousef
 */

#ifndef RULEPARSER_H_
#define RULEPARSER_H_

#include "RegularDefinition.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class RuleParser: public RegularDefinition
{
public:
    RuleParser();
    virtual ~RuleParser();
    void parseLine(string line);

private:
    void keyWordParse(string line);
    void split (string &txt, vector<string> &strs1, char ch);
    string removeWhiteSpaces(string str);
    bool checkOperators(string line);
    void operatorsParse(string line);
    bool checkExpression(string line);
    void definitionsParse(string line);
    void definitionRange(string &str, string &result);
    void punctuationParse(string line);

};

/*
 * [TODO] to be implemented ...........
*/

#endif /* RULEPARSER_H_ */
