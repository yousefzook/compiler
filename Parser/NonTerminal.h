/*
 * NonTerminal.h
 *
 *  Created on: Apr 19, 2018
 *      Author: aboelhamd
 */

#ifndef NONTERMINAL_H_
#define NONTERMINAL_H_

#include <set>
#include "Symbol.h"
#include "Terminal.h"

class NonTerminal: public Symbol {
public:
    NonTerminal(string name);
    set<Terminal *> first;
    set<Terminal *> follow;
};

#endif /* NONTERMINAL_H_ */
