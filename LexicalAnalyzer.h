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
    vector<string> keyWords;
    vector<string> punctuations;

    void startLexical();

private:
    ifstream rulesFile;
    map<string, string> regexs;

    void readRulesFile();

    void relaxDefinitions();

    void tokenizeRegexs();

    string getEqualValue(string token, string lhs);

    void substituteRHS(map<string, string>::reverse_iterator defPair);

};


#endif //CLEAN_COMPILER_LEXICALANALYZER_H
