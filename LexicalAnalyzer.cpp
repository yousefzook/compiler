//
// Created by yousef on 27/03/18.
//

#include "LexicalAnalyzer.h"
#include "RulesParser.h"

void LexicalAnalyzer::startLexical() {

    readRulesFile();
    // now this.keyWords, this.punctuations vectors ,
    // this.definitions map and this.regexs map are set

    // spilt each regex into vector of tokens
    tokenizeRegexs();
    
    // substitute definition with its rhs in each regex
    relaxRegexs();


}

/*
 * substitute definition with its rhs in each regex
 */
void LexicalAnalyzer::relaxRegexs() {
//    for(auto regexPair: this->regexs){
//        bool hasDefs = true;
//        while(hasDefs){
//            for(auto defPair: this->definitions){
//                if(regexPair.second.find(defPair.first) != string::npos){
//                    int pos = regexPair.second.find(defPair.first);
//                    regexPair.second.replace(pos, defPair.first.length(), defPair.second);
//                    hasDefs
//                }
//            }
//        }
//    }
}

/*
 * Function to spilt each regex into vector of tokens
 */
void LexicalAnalyzer::tokenizeRegexs() {
    for (auto regexPair: this->regexs) {
        string lhs = regexPair.first;
        string rhs = regexPair.second;
        int i = 0;
        while (i < rhs.size()) {
            if(rhs[i] == ' '){
                i++;
                continue;
            }
            string token;
            if (!isalpha(rhs[i])) { // if letter i.e. not a definition, just push it
                if (rhs[i] == '\\') {
                    if (rhs[i + 1] == 'L')
                        token.push_back(rhs[i]);
                    token.push_back(rhs[i + 1]);
                    i++;
                } else
                    token.push_back(rhs[i]);
                this->tokenizedRegexs[lhs].push_back(token);
                token.clear();
                i++;
            } else { // if a letter i.e. may be a definition
                while (isalnum(rhs[i])) {// get the whole word
                    token.push_back(rhs[i]);
                    i++;
                }
                handlePossibleDef(token, lhs);
            }
        }
    }
}

void LexicalAnalyzer::handlePossibleDef(string token, string lhs){
    for (auto defPair: this->definitions) { // compare each def with the token
        if (token == defPair.first) {
            this->tokenizedRegexs[lhs].push_back(token);
            token.clear();
            break;
        }
    }
    if (!token.empty()) // i.e. the word was not definition
        for (auto ch : token) { // push eaach char as token
            string temp;
            temp.push_back(ch);
            this->tokenizedRegexs[lhs].push_back(temp);
        }
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