/*
 * RuleParser.h
 *
 *  Created on: Mar 16, 2018
 *      Author: yousef
 */

#ifndef RULEPARSER_H_
#define RULEPARSER_H_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class RuleParser {
public:
	RuleParser();
	virtual ~RuleParser();

};
	void split(const std::string &txt, std::vector<std::string> &strs2, char ch);
	void keyWordParse(string line);
	void operatorsParse(string line);
	void definitionsParse(string line);
	void punctuationParse(string line);
	bool checkOperators(string line);
	bool checkDefinitions(string line);

void parseLine(string line);

/*
 * [TODO] to be implemented ...........
*/

#endif /* RULEPARSER_H_ */
