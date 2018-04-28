/*
 * ParsingTable.h
 *
 *  Created on: Apr 19, 2018
 *      Author: aboelhamd
 */

#ifndef PARSINGTABLE_H_
#define PARSINGTABLE_H_
#include <vector>
#include <map>
#include "Symbol.h"
#include "Terminal.h"
#include "NonTerminal.h"

using namespace std;

class ParsingTable {
public:
    static map<string, map<string, int> > constructTable(
            set<Terminal*> terminals, set<NonTerminal*> nonTerminals,
            map<NonTerminal*, vector<vector<Symbol*> > > productions);

    // These are the 3 cases of the table:
    // production (we will put the production index),
    // synchronization (-2) and error (-1).
    const static int ERROR = -1;
    const static int SYNCH = -2;
};

#endif /* PARSINGTABLE_H_ */