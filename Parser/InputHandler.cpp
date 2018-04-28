//
// Created by yousef on 27/04/18.
//

#include <fstream>
#include <iostream>
#include <sstream>
#include "InputHandler.h"
#include "ToLL1Converter.h"


void InputHandler::InitGeneratorMaps(set<Terminal *> *terminals, set<NonTerminal *> *nonTerminals,
                                     map<NonTerminal *, vector<vector<Symbol *>>> *productions,
                                     NonTerminal *startNonTerminal) {

    ToLL1Converter converter;
    converter.startLL1Converter(&this->nonTerminalSet, &this->productions);

    startNonTerminal->setName(startNonTerminalString);
    nonTerminals->insert(startNonTerminal);
    for (auto terminal: this->terminalSet)
        terminals->insert(new Terminal(terminal));
    terminals->insert(new Terminal("\\L"));

    for (auto nonTerminal: this->nonTerminalSet){
        if(startNonTerminal->getName() == nonTerminal)
            continue;
        nonTerminals->insert(new NonTerminal(nonTerminal));
    }

    for (auto pair: this->productions) {
        NonTerminal *nonTerminal = (NonTerminal *) findSymbol(pair.first, terminals, nonTerminals);
        vector<vector<Symbol *>> tempVec;
        for (auto vec: pair.second) {
            vector<Symbol *> tempVec2;
            for (auto sym: vec) {
                Symbol *symbol = findSymbol(sym, terminals, nonTerminals);
                tempVec2.push_back(symbol);
            }
            tempVec.push_back(tempVec2);
        }
        productions->insert(std::pair<NonTerminal *, vector<vector<Symbol *>>>(nonTerminal, tempVec));
    }

}

Symbol *InputHandler::findSymbol(string str, set<Terminal *> *terminals, set<NonTerminal *> *nonTerminals) {

    for (auto nonTerminal: *nonTerminals) {
        if(nonTerminal->getName() == str)
            return nonTerminal;
    }

    for(auto terminal: *terminals){
        if(terminal->getName() == str)
            return terminal;
    }

    // the str not terminal or nonterminal
    cout << "Error in initializing sets!"<<endl;
    exit(1);
}

/*
 * read input parser rule file
 * */
void InputHandler::startParserInputHandler(set<Terminal *> *terminals,
                                           set<NonTerminal *> *nonTerminals,
                                           map<NonTerminal *, vector<vector<Symbol *>>> *productions,
                                           NonTerminal *startNonTerminal,
                                           map<string, vector<vector<string>>> * productionsStr) {
    ifstream readFile;
    readFile.open("/home/yousef/tests/parserInput.txt");
    string line;
    while (getline(readFile, line))
        parseLine(line);
    readFile.close();
    InitGeneratorMaps(terminals, nonTerminals, productions, startNonTerminal);
}

/*
 * parse given line to it's meaning
 * */
void InputHandler::parseLine(string line) {
    line = removeWhiteSpaces(line);
    int type = getType(line);
    switch (type) {
        case 1: // new production line
            productionLine(line);
            break;
        case 2: // continue previous production line
            continueProductionLine(line);
            break;

        default: // error in line
            cout << "Bad line in rules file!" << endl;
    }

}

/*
 * if a new non terminal return 1, else return 2
 * */
int InputHandler::getType(string line) {
    if (line[0] == '#')
        return 1;/**if  start with # new non terminal */
    else
        return 2;/**else continue to the previous line */
}


void InputHandler::continueProductionLine(string line) {
    if (productions.count(previousNonTerminal))
        productionParse1(previousNonTerminal, line);

}

void InputHandler::productionLine(string line) {
    productionTemp.clear();

    if (line[0] == '#')
        line.erase(0, 1);

    line = removeWhiteSpaces(line);
    int eqPos = line.find('=');    /**split string on = */
    string str1 = removeWhiteSpaces(line.substr(0, eqPos));
    if(startNonTerminalString.empty())
        startNonTerminalString = str1;
    string str2 = removeWhiteSpaces(line.substr(eqPos + 1, line.size()));
    previousNonTerminal = str1;
    nonTerminalSet.insert(str1);
    productionParse1(str1, str2);

}

/*
 * remove spaces from given line
 * */
string InputHandler::removeWhiteSpaces(string line) {
    while (line[0] == ' ')
        line.erase(0, 1);
    while (line[line.size() - 1] == ' ')
        line.erase(line.size() - 1);
    return line;
}


void InputHandler::productionParse1(string nonTerminalState, string str) {
    vector<string> productionVec;
    split(str, productionVec, '|');/**split string on '|' */
    int i = 0;
    /**handel the first production added to the vector of vector  in the map */
    if (productionVec.size() > 0) {
        productionParse2(productionVec[0]);
        rowsTemp.push_back(productionTemp);
        if (!productions.count(nonTerminalState)) {
            productions.insert(std::make_pair(nonTerminalState, rowsTemp));
        }
        productionTemp.clear();
        i++;
    }
    /**the rest elements*/
    while (i < productionVec.size()) {
        productionParse2(productionVec[i]);
        productions[nonTerminalState].push_back(productionTemp);
        productionTemp.clear();
        i++;
    }
    rowsTemp.clear();
}


void InputHandler::productionParse2(string line) {
    string current;
    int i = 0;
    bool ter = false;
    bool nonTer = true;
    while (i < line.size()) {
        if (line[i] == '\'' && !ter)/**detect start character of terminal symbol*/
        {
            nonTer = false;
            ter = true;
            i++;
            continue;
        } else if (current.size() > 0 && (line[i] == ' ' || i == line.size() - 1) &&
                   nonTer)/**detect start character of nonterminal symbol*/
        {
            current.push_back(line[i]);
            current = removeWhiteSpaces(current);
            nonTerminalSet.insert(current);
            productionTemp.push_back(current);
            current.clear();
        } else if (line[i] == '\'' && ter && current.size() > 0)/**end character of terminal symbol */
        {
            ter = false;
            nonTer = true;
            current = removeWhiteSpaces(current);
            terminalSet.insert(current);
            productionTemp.push_back(current);
            current.clear();
        } else if (line[i] != ' ')
            current.push_back(line[i]);

        i++;
    }
    if (current.size() > 0)/**detect if non terminal symbols not added to the production*/
    {
        current = removeWhiteSpaces(current);
        nonTerminalSet.insert(current);
        productionTemp.push_back(current);
        current.clear();
    }

}

void InputHandler::split(string &txt, vector<string> &strs1, char ch) {
    string token;
    stringstream ss(txt);
    while (getline(ss, token, ch)) {
        token = removeWhiteSpaces(token);
        if (token != "")
            strs1.push_back(token);
    }
}

