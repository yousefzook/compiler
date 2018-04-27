//
// Created by yousef on 27/04/18.
//

#ifndef CLEAN_COMPILER_TOLL1CONVERTER_H
#define CLEAN_COMPILER_TOLL1CONVERTER_H

#include <string>
#include <set>
#include <vector>
#include <map>
#include <stack>
#include "NonTerminal.h"

using namespace std;

class ToLL1Converter {
public:
    void eliminate_ind_LR();

    void eliminate_ind_LF();

    void startLL1Converter(set<string> *nonTerminals,
                           map<string, vector<vector<string>>> *productions);

private:


    map<string, vector<vector<string>>> productions;
    string epsilon = "\\L";
    stack<vector<int>> leftFactorProduc;/** store the numbers of production which had matched the left factor*/
    set<string> nonTerminals;
    set<string> terminals;

    bool inVector(int number, vector<int> numbers);

    void eliminate_imm_LR(string);

    string eliminate_imm_LF(string);

    string getRandomString(string);

    void emptyLeftFactorStack();

    void print_productions();


    bool is_nonTerminal(string);

    int get_nonTerminal_index(string nonTerminal);

    vector<string> remove_nonTerminal(vector<string> rule);

    bool remove_rule(string nonTerminal, vector<string> rule);


    bool is_duplicate_rule(string nonTerminalName, vector<string> newRule);

};


#endif //CLEAN_COMPILER_TOLL1CONVERTER_H
