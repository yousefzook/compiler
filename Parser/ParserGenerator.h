//
// Created by yousef on 20/04/18.
//

#ifndef CLEAN_COMPILER_PARSERGENERATOR_H
#define CLEAN_COMPILER_PARSERGENERATOR_H


#include <vector>
#include <map>
#include <unordered_set>
#include <set>

using namespace std;

class ParserGenerator {
public:
    void startParser(vector<string>);

    struct nonTerminalAttributes {
        set<string> first;
        set<string> follow;
        vector<vector<string>> productions;
    };
private:

    unordered_set<string> terminals;
    map<string, nonTerminalAttributes> nonTerminals;
    string startNonTerminal;

    void initFirst(string nonTerminal);

    void initFollow(string nonTerminal);

    void generateFirst();

    void generateFollow();

    void readProductionsFile();

    bool isTerminal(string symbol);

};


#endif //CLEAN_COMPILER_PARSERGENERATOR_H
