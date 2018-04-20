/*
 * ParsingTable.cpp
 *
 *  Created on: Apr 19, 2018
 *      Author: aboelhamd
 */

#include "ParsingTable.h"
#include <iostream>

// All the arguments must be passed by value not by reference because I may modify them
map<NonTerminal*, map<Terminal*, int> > ParsingTable::constructTable(
		vector<Terminal*> terminals, vector<NonTerminal*> nonTerminals,
		map<NonTerminal*, vector<Terminal*> > first,
		map<NonTerminal*, vector<Terminal*> > follow,
		map<NonTerminal*, vector<vector<Symbol*> > > productions) {

	map<NonTerminal*, map<Terminal*, int> > parsingTable;

	// Build internal (terminals) map for each nonterminal
	for (unsigned x = 0; x < nonTerminals.size(); x++) {
		NonTerminal* nonTerminal = nonTerminals[x];

		// The internal map in the parsing table
		// initially we will make all the entries error.
		map<Terminal*, int> terminalMap;
		for (unsigned i = 0; i < terminals.size(); i++) {
			if (terminals[i]->getName() != "L")
				terminalMap[terminals[i]] = ERROR;
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

				if (firstTerminal->getName() == "L") {
					// If epsilon is the terminal, we get the follow terminals of
					// the first nonterminal and put them with the epsilon production.
					vector<Terminal*> followTerminals = follow[nonTerminal];
					for (unsigned k = 0; k < followTerminals.size(); k++) {
						terminalMap[followTerminals[k]] = i;
					}
				} else {
					// If terminal is not epsilon, put the terminal as usual.
					terminalMap[firstTerminal] = i;
				}
			} else {
				// If first symbol is nonterminal, we take the FIRST of it
				// which is all terminals and we put them with production
				NonTerminal* firstNonTerminal = (NonTerminal*) firstSymbol;
				vector<Terminal*> firstTerminals = first[firstNonTerminal];

				for (unsigned j = 0; j < firstTerminals.size(); j++) {
					Terminal* firstTerminal = firstTerminals[j];

					if (firstTerminal->getName() == "L") {
						// If epsilon is the terminal, we get the follow terminals of
						// the first nonterminal and put them with the epsilon production.
						vector<Terminal*> followTerminals = follow[nonTerminal];
						for (unsigned k = 0; k < followTerminals.size(); k++) {
							terminalMap[followTerminals[k]] = i;
						}
					} else {
						// If terminal is not epsilon, put the terminal as usual.
						terminalMap[firstTerminal] = i;
					}
				}

			}

		}
		// Put 'synch' in the follow the terminals which has no production.
		vector<Terminal*> followTerminals = follow[nonTerminal];
		for (unsigned k = 0; k < followTerminals.size(); k++) {
			if (terminalMap[followTerminals[k]] == ERROR)
				terminalMap[followTerminals[k]] = SYNCH;
		}

		// Put the inner map in the parsing table
		parsingTable[nonTerminal] = terminalMap;
	}

	return parsingTable;
}
