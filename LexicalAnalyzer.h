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

class LexicalAnalyzer {

public:
    map<string, vector<string>> tokenizedRegexs;
    map<string, string> definitions;
    map<string, string> regexs;
    vector<string> keyWords;
    vector<string> punctuations;

    void startLexical();

private:
    ifstream rulesFile;

    void readRulesFile();

    void relaxRegexs();

    void tokenizeRegexs();

    void handlePossibleDef(string token, string lhs);
};


#endif //CLEAN_COMPILER_LEXICALANALYZER_H
