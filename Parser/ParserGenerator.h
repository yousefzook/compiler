//
// Created by yousef on 20/04/18.
//

#ifndef CLEAN_COMPILER_PARSERGENERATOR_H
#define CLEAN_COMPILER_PARSERGENERATOR_H


#include <vector>
#include <map>
#include <unordered_set>
#include <set>
#include "NonTerminal.h"

using namespace std;

class ParserGenerator {
public:
    void startParser(vector<string>);

private:

    set<Terminal *> terminals;
    set<NonTerminal *> nonTerminals;
    NonTerminal * startNonTerminal;
    map<NonTerminal *, vector<vector<Symbol*>>> productions;
    map<string, vector<vector<string>>> productionsStr;

    void initFirst(NonTerminal * nonTerminal);

    Terminal * getEpsilonPtr();
    void initFollow(NonTerminal *nonTerminal);

    void generateFirst();

    void generateFollow();

    bool isTerminal(string symbol);

};


#endif //CLEAN_COMPILER_PARSERGENERATOR_H
