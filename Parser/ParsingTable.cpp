/*
 * ParsingTable.cpp
 *
 *  Created on: Apr 19, 2018
 *      Author: aboelhamd
 */

#include "ParsingTable.h"

ParsingTable *ParsingTable::parsingTable = 0;

// All the arguments must be passed by value not by reference because I may modify them
void ParsingTable::constructTable(
        vector<Terminal> terminals, vector<NonTerminal> nonTerminals,
        map<NonTerminal, vector<Terminal> > first,
        map<NonTerminal, vector<Terminal> > follow,
        map<NonTerminal, vector<vector<Symbol *> > > productions) {

    map<NonTerminal, map<Terminal, int> > parsingTable;

    // Build internal (terminals) map for each nonterminal
    for (unsigned x = 0; x < nonTerminals.size(); x++) {
        NonTerminal nonTerminal = nonTerminals[x];

        // The internal map in the parsing table
        // initially we will make all the entries error.
        map<Terminal, int> terminalMap;
        for (unsigned i = 0; i < terminals.size(); i++) {
            if (terminals[i].getName() != "L")
                terminalMap.insert(
                        pair<Terminal, int>(terminals[i], (int) ERROR));
        }

        // Let production be : T => T'E | E | aT'
        // we take each ORed production like : T=> T'E
        // and perform the parsing table rules
        vector<vector<Symbol *> > production = productions[nonTerminal];
        for (unsigned i = 0; i < production.size(); i++) {
            // We take only the first symbol from each ORed production
            // Because the FIRST of the production is the FIRST of the
            // first symbol. FIRST(T'E) == FIRST(T')
            Symbol *firstSymbol = production[i].front();

            if (firstSymbol->isTerminal()) {
                // If first symbol is terminal, we just put it to the map
                // with the production.
                Terminal *firstTerminal = (Terminal *) firstSymbol;
                terminalMap.insert(pair<Terminal, int>(*firstTerminal, i));
            } else {
                // If first symbol is nonterminal, we take the FIRST of it
                // which is all terminals and we put them with production
                NonTerminal *firstNonTerminal = (NonTerminal *) firstSymbol;
                vector<Terminal> firstTerminals = first[*firstNonTerminal];

                for (unsigned j = 0; j < firstTerminals.size(); j++) {
                    Terminal firstTerminal = firstTerminals[j];

                    vector<Terminal> followTerminals = follow[*firstNonTerminal];

                    if (firstTerminal.getName() == "L") {
                        // If epsilon is the terminal, we get the follow terminals of
                        // the first nonterminal and put them with the epsilon production.

                        for (unsigned k = 0; k < followTerminals.size(); k++) {
                            terminalMap.insert(
                                    pair<Terminal, int>(followTerminals[k], i));
                        }
                    } else {
                        // If terminal is not epsilon, put the terminal as usual
                        // and we put 'synch' in the follow the terminal.
                        terminalMap.insert(
                                pair<Terminal, int>(firstTerminal, i));

                        for (unsigned k = 0; k < followTerminals.size(); k++) {
                            terminalMap.insert(
                                    pair<Terminal, int>(followTerminals[k],
                                                        (int) SYNCH));
                        }
                    }

                }
            }

        }

        // Put the inner map in the parsing table
        parsingTable.insert(
                pair<NonTerminal, map<Terminal, int> >(nonTerminal,
                                                       terminalMap));
    }

    this->table = parsingTable;
}


ParsingTable *ParsingTable::getInstance(){
    if (parsingTable == 0) {
        parsingTable = new ParsingTable();
    }
    return parsingTable;
}

/*
 * private counstructor for skeleton implementation
 * */
ParsingTable::ParsingTable(){}
