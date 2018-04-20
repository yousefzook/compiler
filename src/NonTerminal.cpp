/*
 * NonTerminal.cpp
 *
 *  Created on: Apr 19, 2018
 *      Author: aboelhamd
 */

#include "NonTerminal.h"

NonTerminal::NonTerminal(string name) {
	this->name = name;
	terminal = false;
}

bool NonTerminal::operator<(const NonTerminal nonTerminal) const {
	return true;
}
