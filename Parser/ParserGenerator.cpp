//
// Created by yousef on 20/04/18.
//

#include <algorithm>
#include "ParserGenerator.h"

/*
 * Start Parser work
 * */
void ParserGenerator::startParser(vector<string> lexicalTokens) {

    readProductionsFile();
    /*
     * Now terminals set, nonTerminals  map are  initialized
     * */

    generateFirst();
    generateFollow();

//    ParsingTable::getInstance()->
//            constructTable(terminals, nonTerminals, first, follow, productions);




}


/*
 * init follow map
 * */
void ParserGenerator::generateFollow() {
    for (auto pair: nonTerminals) {
        string nonTerminal = pair.first;
        initFollow(nonTerminal);
    }
}

/*
 * return follow of the given nonTerminal after initializing it
 * */
void ParserGenerator::initFollow(string nonTerminal) {

    struct nonTerminalAttributes *attributes = &nonTerminals[nonTerminal];
    if (!attributes->follow.empty())
        return;

    for (auto pair: nonTerminals) {
        vector<vector<string>> productions = pair.second.productions;
        string lhsNonTerminal = pair.first; // left hand side non terminal
        for (auto production: productions) {

            std::vector<string>::iterator it = find(production.begin(), production.end(), nonTerminal);
            if (it == production.end())
                // the production doesn't contain the nonterminal so skip it
                continue;

            if (it + 1 == production.end()) { // the nonTerm is at end of production
                if (lhsNonTerminal == nonTerminal)
                    continue;
                else {
                    initFollow(lhsNonTerminal);
                    for (auto value: nonTerminals[lhsNonTerminal].follow)
                        attributes->follow.insert(value);
                }
            }
            production.at(it - production.begin() + 1);
        }
    }


}

/*
 * initialze first for each non terminal
 * */
void ParserGenerator::generateFirst() {

    for (auto pair: nonTerminals) {
        string nonTerminal = pair.first;
        initFirst(nonTerminal);
    }
}

/*
 * return first of the given nonTerminal after initializing it
 * */
void ParserGenerator::initFirst(string nonTerminal) {

    struct nonTerminalAttributes *attributes = &nonTerminals[nonTerminal];
    if (!attributes->first.empty())
        return;
    vector<vector<string>> nonTerminalProductions = attributes->productions;
    int iter = 0;

    for (auto production: nonTerminalProductions) {

        string symbol = production[iter];
        if (symbol == "\L" || isTerminal(symbol)) // if terminal or lambda, push it
            attributes->first.insert(symbol);

        else { // if non terminal, get first of this nonterminal
            initFirst(symbol);
            for (auto value: nonTerminals[symbol].first)
                attributes->first.insert(value);

            while (iter < production.size() &&
                   find(nonTerminals[symbol].first.begin(),
                        nonTerminals[symbol].first.end(), "\L") != nonTerminals[symbol].first.end()) {
                // while having lambda and still there exist symbols, push first of the next symbol

                symbol = production[++iter];
                if (symbol == "\L" || isTerminal(symbol)) { // if terminal or lambda, push it
                    attributes->first.insert(symbol);
                    break;
                }

                initFirst(symbol);
                for (auto value: nonTerminals[symbol].first)
                    attributes->first.insert(value);
            }
        }
    }
}

/*
 * if given symbol is terminal , return true else return false
 * */
bool ParserGenerator::isTerminal(string symbol) {
    if (terminals.find(symbol) != terminals.end())
        return true;
    return false;
}

/*
 * read productions file and init the
 *  productions map and terminals, nonTerminals vectors
 * */
void ParserGenerator::readProductionsFile() {

}
