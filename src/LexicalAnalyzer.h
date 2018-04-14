//
// Created by yousef on 27/03/18.
//


using namespace std;

#ifndef CLEAN_COMPILER_LEXICALANALYZER_H
#define CLEAN_COMPILER_LEXICALANALYZER_H

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include "NFA.h"
#include <stack>

class LexicalAnalyzer {

public:
    LexicalAnalyzer();

    map<string, string> definitions;
    vector<string> keyWords;
    vector<string> punctuations;
    map<string, NFA> regexsNFAs;

    void startLexical();

private:
    ifstream rulesFile;
    map<string, string> regexs;
    map<string, vector<string> > tokenizedRegexs;
    map<char, int> operationsPriority;
    stack<NFA> inputStack;
    stack<char> operationStack;

    void doOperationInTOS();

    void finishBrackets();

    void pushOperation(char operation);

    void buildNFAs();

    void initOperationsMap();

    void readRulesFile();

    void relaxDefinitions();

    void tokenizeRegexs();

    string getEqualValue(string token, string lhs);

    void substituteRHS(map<string, string>::reverse_iterator defPair);

};


#endif //CLEAN_COMPILER_LEXICALANALYZER_H
