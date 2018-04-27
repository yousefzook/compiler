//
// Created by yousef on 20/04/18.
//

#include <algorithm>
#include "ParserGenerator.h"
#include "InputHandler.h"
#include "ParserTracer.h"

/*
 * Start Parser work
 * */
void ParserGenerator::startParser(vector<string> lexicalTokens) {

    InputHandler inputHandler;
    inputHandler.startParserInputHandler(&terminals, &nonTerminals,
                                         &productions, startNonTerminal, &productionsStr);
    /*
     * Now terminals set, nonTerminals  set, Productions map, startNonTerminal are  initialized
     * */

    generateFirst();
    generateFollow();

    ParsingTable parsingTable;
    map<string, map<string, int>> table = parsingTable.constructTable(terminals, nonTerminals, productions);

    ParserTracer parser;
    parser.start(lexicalTokens, table, productionsStr, startNonTerminal->getName());


}


/*
 * init follow map
 * */
void ParserGenerator::generateFollow() {
    for (auto nonTerminal: nonTerminals)
        initFollow(nonTerminal);

}

/*
 * return follow of the given nonTerminal after initializing it
 * */
void ParserGenerator::initFollow(NonTerminal *nonTerminal) {

//    struct nonTerminalAttributes *attributes = &nonTerminals[nonTerminal];
    if (!nonTerminal->follow.empty())
        return;

    for (auto nonTerminalIter: nonTerminals) {

        vector<vector<Symbol *>> productions = this->productions[nonTerminalIter];

        NonTerminal *lhsNonTerminal = nonTerminalIter; // left hand side non terminal
        for (auto production: productions) {

            std::vector<Symbol *>::iterator it = find(production.begin(), production.end(), (Symbol *) nonTerminal);
            if (it == production.end())
                // the production doesn't contain the nonterminal so skip it
                continue;

            if (it + 1 == production.end()) { // the nonTerm is at end of production
                if (lhsNonTerminal == nonTerminal)
                    continue;
                else {
                    initFollow(lhsNonTerminal);
                    for (auto value: lhsNonTerminal->follow)
                        nonTerminal->follow.insert(value);
                }
            }
//            production.at(it - production.begin() + 1);
        }
    }


}

/*
 * initialze first for each non terminal
 * */
void ParserGenerator::generateFirst() {

    for (auto nonTerminal: nonTerminals)
        initFirst(nonTerminal);

}

/*
 * return first of the given nonTerminal after initializing it
 * */
void ParserGenerator::initFirst(NonTerminal *nonTerminal) {


    if (!nonTerminal->first.empty())
        return;

    vector<vector<Symbol *>> nonTerminalProductions = productions[nonTerminal];
    int iter = 0;

    for (auto production: nonTerminalProductions) {

        Symbol *symbol = production[iter];
        string symbolStr = symbol->getName();
        if (symbolStr == "\\L" || isTerminal(symbolStr)) // if terminal or lambda, push it
            nonTerminal->first.insert((Terminal *) symbol);

        else { // if non terminal, get first of this nonterminal
            NonTerminal *nonTerminal1 = (NonTerminal *) symbol;
            initFirst(nonTerminal1);
            for (auto value: nonTerminal1->first)
                nonTerminal->first.insert(value);

            while (iter < production.size() &&
                   find(nonTerminal1->first.begin(),
                        nonTerminal1->first.end(), getEpsilonPtr()) != nonTerminal1->first.end()) {
                // while having lambda and still there exist symbols, push first of the next symbol

                symbol = production[++iter];
                if (symbol->getName() == "\\L" || isTerminal(symbol->getName())) { // if terminal or lambda, push it
                    nonTerminal->first.insert((Terminal *) symbol);
                    break;
                }
                nonTerminal1 = (NonTerminal *) symbol;
                initFirst(nonTerminal1);
                for (auto value: nonTerminal1->first)
                    nonTerminal->first.insert(value);
            }
        }
    }
}

/*
 * if given symbol is terminal , return true else return false
 * */
bool ParserGenerator::isTerminal(string symbol) {
    for (auto terminal: terminals)
        if (terminal->getName() == symbol)
            return true;
    return false;
}

Terminal *ParserGenerator::getEpsilonPtr() {
    for (auto terminal: terminals)
        if (terminal->getName() == "\\L")
            return terminal;
    return NULL;
}
