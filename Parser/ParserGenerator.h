//
// Created by yousef on 20/04/18.
//

#ifndef CLEAN_COMPILER_PARSERGENERATOR_H
#define CLEAN_COMPILER_PARSERGENERATOR_H

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <stack>
#include <fstream>
#include <sstream>
#include "Symbol.h"

using namespace std;

class ParserGenerator
{
public:

    void startParser(vector<string>);

private:

    ifstream readFile;
    vector<Symbol> terminals;
    vector<Symbol> nonTerminals;
    map<Symbol, vector<Symbol> > first;
    map<Symbol, vector<Symbol> > follow;
    void initFirst();

    void initFollow();

    void readProductionsFile();



    /************************************************************************************************/
    set<string> terminalSet;/**use set to avoid duplicated values*/
    set<string> nonTerminalSet;
    vector<Symbol> productionTemp;/**just use as atemp for data*/
    vector <vector<Symbol>> rowsTemp;/**just use as atemp for data*/
    map<string, vector<vector<Symbol>>> productions;
    string previousNonTerminal;/** contain the previous nonterminal state of the previous line if the new line*/
    stack<vector< int>> leftFactorProduc;/** store the numbers of production which had matched the left factor*/
    char validChar=97;
    Symbol epsilon; /**epsilon = \\L **/



    void parseLine(string line);

    void productionLine(string line);

    void continueProductionLine(string line);

    void productionParse1(string nonTerminalState,string str2);

    void productionParse2(string line);

    void split (string &txt, vector<string> &strs1, char ch);

    int getType(string line);

    /**
    *remove the white spaces from start and the end of the line
    */
    string removeWhiteSpaces(string line);

    void print();

    Symbol createSymbol(string name, bool terminal);

    /**
    * pop all element from the stack
    */
    void emptyLeftFactorStack();

    string getRandomString();/***to rename the new sambol with names not redundant */

    /**
    *check if the number in vector
    */
    bool inVector(int number,vector<int>numbers);

    void leftFactorAll();

    /**
    *remove left factor
    */
    void leftFactor(string nonTeminalName);

    /**
    *remove left recursion
    */
    void leftRecursion(string nonterminalName);

};


#endif //CLEAN_COMPILER_PARSERGENERATOR_H
