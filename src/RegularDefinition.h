/*
 * RegularDefinition.h
 *
 *  Created on: Mar 16, 2018
 *      Author: Rizk
 */

#include "RuleParser.h"

#include <string>
#include <map>
#include <vector>
using namespace std;

#ifndef REGULARDEFINITION_H_
#define REGULARDEFINITION_H_

class RegularDefinition {
public:
	RegularDefinition();
	virtual ~RegularDefinition();

	bool compare(string type, char c);

private:
	std::map<string, string > definitions;
	std::vector<string> keyword;
	//std::map<string, vector<string>> operators;
	std::vector<string> punctuation;

};


#endif /* REGULARDEFINITION_H_ */
