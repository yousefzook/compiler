/*
 * ParsingTable.cpp
 *
 *  Created on: Apr 19, 2018
 *      Author: aboelhamd
 */

#include "ParsingTable.h"
#include <iostream>

// All the arguments must be passed by value not by reference because I may modify them
map<string, map<string, int> > ParsingTable::constructTable(
        set<Terminal*> terminals, set<NonTerminal*> nonTerminals,
        map<NonTerminal*, vector<vector<Symbol*> > > productions) {

    map<string, map<string, int> > parsingTable;

    // Build internal (terminals) map for each nonterminal
    for (auto nonTerminal : nonTerminals) {
        // The internal map in the parsing table
        // initially we will make all the entries error.
        map<string, int> terminalMap;
        for (auto terminal : terminals) {
            if (terminal->getName() != "\\L")
                terminalMap[terminal->getName()] = ERROR;
        }

        // Let production be : T => T'E | E | aT'
        // we take each ORed production like : T=> T'E
        // and perform the parsing table rules
        vector<vector<Symbol*> > production = productions[nonTerminal];
        for (unsigned i = 0; i < production.size(); i++) {
            // We take only the first symbol from each ORed production
            // Because the FIRST of the production is the FIRST of the
            // first symbol. FIRST(T'E) == FIRST(T')
            Symbol* firstSymbol = production[i].front();

            if (firstSymbol->isTerminal()) {
                // If first symbol is terminal, we just put it to the map
                // with the production.
                Terminal* firstTerminal = (Terminal*) firstSymbol;

                if (firstTerminal->getName() == "\\L") {
                    // If epsilon is the terminal, we get the follow terminals of
                    // the first nonterminal and put them with the epsilon production.
                    set<Terminal*> followTerminals = nonTerminal->follow;
                    for (auto followTerminal : followTerminals) {
                        if (terminalMap[followTerminal->getName()] == ERROR)
                            terminalMap[followTerminal->getName()] = i;
                        else {
                            cout << "There is ambiguity at the production of ";
                            cout << "NonTerminal: " << nonTerminal->getName() << endl;
                            cout << " At Terminal: " << followTerminal->getName() << endl;
                            exit(1);
                        }
                    }
                } else {
                    // If terminal is not epsilon, put the terminal as usual.
                    if (terminalMap[firstTerminal->getName()] == ERROR)
                        terminalMap[firstTerminal->getName()] = i;
                    else {
                        cout << "There is ambiguity at the production of ";
                        cout << "NonTerminal: " << nonTerminal->getName() << endl;
                        cout << " At Terminal: " << firstTerminal->getName() << endl;
                        exit(1);
                    }
                }
            } else {
                // If first symbol is nonterminal, we take the FIRST of it
                // which is all terminals and we put them with production
                NonTerminal* firstNonTerminal = (NonTerminal*) firstSymbol;
                set<Terminal*> firstTerminals = firstNonTerminal->first;

                for (auto firstTerminal : firstTerminals) {

                    if (firstTerminal->getName() == "\\L") {
                        // If epsilon is the terminal, we get the follow terminals of
                        // the first nonterminal and put them with the epsilon production.
                        set<Terminal*> followTerminals = nonTerminal->follow;
                        for (auto followTerminal : followTerminals) {
                            if (terminalMap[followTerminal->getName()] == ERROR)
                                terminalMap[followTerminal->getName()] = i;
                            else {
                                cout << "There is ambiguity at the production of ";
                                cout << "NonTerminal: " << nonTerminal->getName() << endl;
                                cout << " At Terminal: " << followTerminal->getName() << endl;
                                exit(1);
                            }
                        }
                    } else {
                        // If terminal is not epsilon, put the terminal as usual.
                        if (terminalMap[firstTerminal->getName()] == ERROR)
                            terminalMap[firstTerminal->getName()] = i;
                        else {
                            cout << "There is ambiguity at the production of ";
                            cout << "NonTerminal: " << nonTerminal->getName() << endl;
                            cout << " At Terminal: " << firstTerminal->getName() << endl;
                            exit(1);
                        }
                    }
                }

            }

        }
        // Put 'synch' in the follow the terminals which has no production.
        set<Terminal*> followTerminals = nonTerminal->follow;
        for (auto followTerminal : followTerminals) {
            if (terminalMap[followTerminal->getName()] == ERROR)
                terminalMap[followTerminal->getName()] = SYNCH;
        }

        // Put the inner map in the parsing table
        parsingTable[nonTerminal->getName()] = terminalMap;
    }

    return parsingTable;
}