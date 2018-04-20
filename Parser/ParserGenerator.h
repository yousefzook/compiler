//
// Created by yousef on 20/04/18.
//

#ifndef CLEAN_COMPILER_PARSERGENERATOR_H
#define CLEAN_COMPILER_PARSERGENERATOR_H


#include <vector>
#include <map>
#include "Terminal.h"
#include "NonTerminal.h"

class ParserGenerator {
public:
    void startParser(vector<string>);

private:
    vector<Terminal> terminals;
    vector<NonTerminal> nonTerminals;
    map<NonTerminal, vector<Terminal> > first;
    map<NonTerminal, vector<Terminal> > follow;
    map<NonTerminal, vector<vector<Symbol *>>> productions;

    void initFirst();

    void initFollow();

    void readProductionsFile();

};


#endif //CLEAN_COMPILER_PARSERGENERATOR_H
