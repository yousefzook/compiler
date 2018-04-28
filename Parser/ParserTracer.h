//
// Created by yousef on 20/04/18.
//

#ifndef CLEAN_COMPILER_PARSERTRACER_H
#define CLEAN_COMPILER_PARSERTRACER_H

#include "ParsingTable.h"
#include <string>
#include <vector>

using namespace std;

class ParserTracer {

public:
    void start(vector<string>, map<string, map<string, int>>, map<string,
            vector<vector<string>>> productionsStr, string startState);

private:
    void init_tracerStack(string);
    bool isNonTerminal(string); //check if NonTerminal by searching the map of parsingTable (nonterminals are keys)
    bool isTerminal(string); // check if NonTerminal by searching the entry map of parsingTable (terminals are keys)
    void print_stack(); //print content of stack other than the dollar sign after each change

    vector<string> lexicalTokens; //has tokens of the input file as outputed from lexical generator
    map<string, vector<vector<string>>> productions; //has production corresponding to each nonTerminal
    map<string, map<string, int>> parsingTable;
    stack<string> tracerStack;
    const static int ERROR = -1;
    const static int SYNCH = -2;


};


#endif //CLEAN_COMPILER_PARSERTRACER_H
