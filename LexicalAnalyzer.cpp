//
// Created by yousef on 27/03/18.
//

#include "LexicalAnalyzer.h"
#include "RulesParser.h"

void LexicalAnalyzer::startLexical() {

    readRulesFile();
    // now this.keyWords, this.punctuations vectors and this.definitions map and this.regexs map are set




}

/*
 * Read rules file and pass it to the parser and fill regex and definitions maps
 */
void LexicalAnalyzer::readRulesFile() {
    rulesFile.open("/home/yousef/tests/rules.txt");
    string line;
    RulesParser rParser;
    while (getline(rulesFile, line))
        rParser.parseLine(line, &this->definitions, &this->regexs, &this->punctuations, &this->keyWords);
    rulesFile.close();
}