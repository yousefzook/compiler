//
// Created by yousef on 27/03/18.
//

#ifndef CLEAN_COMPILER_TESTPROGRAM_H
#define CLEAN_COMPILER_TESTPROGRAM_H

#include <iostream>
#include <stack>
#include <vector>
#include <map>
#include <iomanip>
#include <sstream>

using namespace std;


class TestProgram {
public:

    void setData(vector<string> keywords, vector<string> punctuation, vector<vector<int> > dfatable,
                 map<int, string> acceptedState);

    void executeTokensFile();

    void parseLine(string line);

    void printTokens();


private:

    stack<int> readedStates; // has all successfully traversed states
    stack<int> readedCharsIndex; //
    stack<int> acceptedStates;
    int fromLastAcceptance;
    int currentState;
    int curCharIndex;
    vector<string> keyWords;
    vector<string> punctuations;
    vector<vector<int> > dfaTable; // has minimized dfa table (final)
    map<int, string> dfaStates;
    vector<string> tokens;
    vector<string> values;

    bool charValid(char &j, string transitionToken);

    bool checkEmptyState();

    bool matchPunc(char &i);

    bool checkTokenKeyword(string token);

    void refereToEmptyState(int index, string line);

    bool checkChar(char &currChar, int index, int lineSize, string line, string value);

    string definitionRange(string &str, string &result);

    void split(string &txt, vector<string> &strs1, char ch);

    string removeWhiteSpaces(string str);

    int check_status(int statusIndex);


};


#endif //CLEAN_COMPILER_RULESPARSER_H
