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
    void startLexical();
    map<string,string> definitions;
    map<string,string> regexs;
    vector<string> keyWords;
    vector<string> punctuations;

private:
    ifstream rulesFile;
    void readRulesFile();
};


#endif //CLEAN_COMPILER_LEXICALANALYZER_H
