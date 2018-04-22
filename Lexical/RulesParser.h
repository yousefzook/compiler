//
// Created by yousef on 27/03/18.
//

#ifndef CLEAN_COMPILER_RULESPARSER_H
#define CLEAN_COMPILER_RULESPARSER_H

#include<string>
#include<vector>
#include <map>

using namespace std;


class RulesParser
{
public:
    void
    parseLine(string line, map<string, string> *definitions, map<string, string> *regexs, vector<string> *punctuations,
              vector<string> *keyWords);

private:
    void constDefsParse(string line, vector<string> *constDefs);

    void regularsParse(string line, map<string, string> *regMap, char delimiter);

    int getType(string line);

    vector<string> split(string &txt, char ch);
};


#endif //CLEAN_COMPILER_RULESPARSER_H
