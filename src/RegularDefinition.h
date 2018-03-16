/*
 * RegularDefinition.h
 *
 *  Created on: Mar 16, 2018
 *      Author: yousef
 */

#include <string>
#include <map>
using namespace std;

#ifndef REGULARDEFINITION_H_
#define REGULARDEFINITION_H_

class RegularDefinition {
public:
	RegularDefinition();
	virtual ~RegularDefinition();

	bool compare(string type, char c);

private:
	std::map<string, string> definitions;
};

#endif /* REGULARDEFINITION_H_ */
