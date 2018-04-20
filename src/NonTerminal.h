/*
 * NonTerminal.h
 *
 *  Created on: Apr 19, 2018
 *      Author: aboelhamd
 */

#ifndef NONTERMINAL_H_
#define NONTERMINAL_H_

#include "Symbol.h"

class NonTerminal: public Symbol {
public:
	NonTerminal(string name);

	// comparator for the map, order by inserting
	bool operator<(const NonTerminal nonTerminal) const;
};

#endif /* NONTERMINAL_H_ */

