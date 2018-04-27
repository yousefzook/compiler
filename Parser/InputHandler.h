//
// Created by yousef on 27/04/18.
//

#ifndef CLEAN_COMPILER_INPUTHANDLER_H
#define CLEAN_COMPILER_INPUTHANDLER_H

#include <string>
#include <vector>
#include <stack>
#include <set>
#include <map>
#include "Symbol.h"
#include "NonTerminal.h"

using namespace std;

class InputHandler {

public:
    void startParserInputHandler(   set<Terminal *> * terminals,
                                    set<NonTerminal *> * nonTerminals,
                                    map<NonTerminal *, vector<vector<Symbol*>>> * productions,
                                    NonTerminal * startNonTerminal,
                                    map<string, vector<vector<string>>> * productionsStr);
private:

    map<string, vector<vector<string>>> productions;
    set<string> terminalSet;/**use set to avoid duplicated values*/
    set<string> nonTerminalSet;
    vector<string> productionTemp;/**just use as atemp for data*/
    vector<vector<string>> rowsTemp;/**just use as atemp for data*/
    string previousNonTerminal;/** contain the previous nonterminal state of the previous line if the new line*/
    string startNonTerminalString;

    void InitGeneratorMaps(set<Terminal *> * terminals,
                           set<NonTerminal *> * nonTerminals,
                           map<NonTerminal *, vector<vector<Symbol*>>> * productions,
                           NonTerminal * startNonTerminal);

    void parseLine(string line);

    Symbol * findSymbol(string str, set<Terminal *> *terminals, set<NonTerminal *> *nonTerminals);

    void productionLine(string line);

    void continueProductionLine(string line);

    void productionParse1(string nonTerminalState, string str2);

    void productionParse2(string line);

    void split(string &txt, vector<string> &strs1, char ch);

    int getType(string line);

    string removeWhiteSpaces(string line);
};


#endif //CLEAN_COMPILER_INPUTHANDLER_H
