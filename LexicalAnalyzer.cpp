//
// Created by yousef on 27/03/18.
//

#include "NFAOperator.h"
#include "LexicalAnalyzer.h"
#include "RulesParser.h"
#include "GroupedNFA.h"

LexicalAnalyzer::LexicalAnalyzer() {
    initOperationsMap();
}

void LexicalAnalyzer::startLexical() {

    readRulesFile();
    /**
     *  now this.keyWords, this.punctuations vectors ,
     *  this.definitions map and this.regexs map are set
     */

    // substitute definition with its rhs in each regex
    relaxDefinitions();
    // spilt each regex into vector of tokens
    tokenizeRegexs();
    // build nfa of each regex
    buildNFAs();
    // build grouped nfa
    buildGroupedNFA();
    // build transition table for grouped NFA
    GroupedNFA::getInstance()->buildNFATransTable();

//    // print definitions map
//    for (auto a: this->definitions)
//        cout << a.first << "  " << a.second << endl;
//
//    // print regexs tokenized map
//    for (auto a: this->tokenizedRegexs)
//        for (auto b: a.second)
//            cout << a.first << "  " << b << endl;


}

/*
 * build grouped nfa using regexs nfas
 * */
void LexicalAnalyzer::buildGroupedNFA() {
    GroupedNFA *groupedNFA = GroupedNFA::getInstance();
    groupedNFA->startState = groupedNFA->createState(false);
    for (auto regexsNFA: regexsNFAs) {
        NFA nfa = regexsNFA.second;
        groupedNFA->addEdge(groupedNFA->startState, nfa.startState, "\\L");
    }
}


/*
 * For each regex, build its NFA and put it in the regexsNFAs map
 * */
void LexicalAnalyzer::buildNFAs() {


    for (auto tokenizedRegex : tokenizedRegexs) { // looping on each regex
        string regexName = tokenizedRegex.first; // name of nfa = regex lhs
        vector<string> tokens = tokenizedRegex.second;

        for (int i = 0; i < tokens.size(); i++) { // looping on each token in the regex
            string token = tokens[i];
            if (token[0] == ')')
                finishBrackets();
            else if (token[0] == '(') {
                if (i != 0 && tokens[i - 1] != "|" && tokens[i - 1] != "(")// we should add '.' operation in stack
                    pushOperation('.');
                operationStack.push(token[0]);
            } else if (token == "." || !operationsPriority.count(token[0])) { // if the token not an operation
                if (i != 0 && tokens[i - 1] != "|" && tokens[i - 1] != "(") // we should add '.' operation in stack
                    pushOperation('.');

                if (token[0] == '\\' && token[1] != 'L')
                    token = token[1];
                NFA tokenNFA;
                tokenNFA.startState = tokenNFA.createState(false);
                tokenNFA.finalState = tokenNFA.createState(true);
                tokenNFA.addEdge(tokenNFA.startState, tokenNFA.finalState, token);
                tokenNFA.name = token;
                inputStack.push(tokenNFA);
            } else { // an operation
                pushOperation(token[0]);
            }

        }
        while (inputStack.size() > 1)
            doOperationInTOS();
        inputStack.top().name = regexName;
        regexsNFAs.insert(pair<string, NFA>(regexName, inputStack.top()));
        inputStack.pop();
    }
}

void LexicalAnalyzer::pushOperation(char operation) {
    if (operationStack.empty() || operationStack.top() == '(') {
        operationStack.push(operation);
    } else { // if there exist operation, check priority first
        int priority = operationsPriority[operation];
        int tosPriority = operationsPriority[operationStack.top()]; // top of stack priority
        if (priority > tosPriority) {
            operationStack.push(operation);
        } else { // here, the top operation in stack must be finished first
            doOperationInTOS();
            pushOperation(operation);
        }

    }
}

void LexicalAnalyzer::doOperationInTOS() {
    char operation = operationStack.top();
    operationStack.pop();
    NFA nfa2 = inputStack.top();
    NFA nfa1;
    inputStack.pop();
    switch (operation) {
        case '*':
            inputStack.push(kleeneClosure(nfa2));
            break;
        case '+':
            inputStack.push(positiveClosure(nfa2));
            break;
        case '.':
            nfa1 = inputStack.top();
            inputStack.pop();
            inputStack.push(AND(nfa1, nfa2));
            break;
        case '|':
            nfa1 = inputStack.top();
            inputStack.pop();
            inputStack.push(OR(nfa1, nfa2));
            break;
        default:
            cout << "Error in operations stack handling!" << endl;
    }
}

void LexicalAnalyzer::finishBrackets() {

    while (operationStack.top() != '(') {
        doOperationInTOS();
    }
    operationStack.pop(); // pop '(' form stack
}

/*
 * substitute definition with its rhs in each tokenized regex
 */
void LexicalAnalyzer::relaxDefinitions() {
    for (map<string, string>::reverse_iterator defPair = this->definitions.rbegin();
         defPair != this->definitions.rend(); ++defPair) { // loop in reversed order on definitions
        substituteRHS(defPair); // if rhs has definitions, replace the def with it's value
    }

}

/*
 * if rhs has definitions, replace the def with it's value
 * */
void LexicalAnalyzer::substituteRHS(map<string, string>::reverse_iterator defPair) {
    string rhs = defPair->second;
    rhs.insert(0, "("); // to make the def calculated first in nfa
    for (map<string, string>::reverse_iterator defPair2 = defPair;
         defPair2 != this->definitions.rend(); ++defPair2) {
        int pos = rhs.find(defPair2->first);
        if (pos != string::npos)
            rhs.replace(pos, defPair2->first.size(), defPair2->second); // replace the def in rhs with its value
    }
    rhs.push_back(')'); // to make the def calculated first in nfa

    // trim spaces before and after '-' if exists
    int dashPos = rhs.find('-');
    int i = dashPos - 1;
    if (dashPos != string::npos) {
        while (rhs[i] == ' ') {
            rhs.erase(i, 1);
            i -= 2;
        }
        dashPos = rhs.find('-');
        i = dashPos + 1;
        while (rhs[i] == ' ')
            rhs.erase(i, 1);

    }

    defPair->second = rhs;

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
            if (rhs[i] == ' ') {
                i++;
                continue;
            }
            string token;
            if (rhs[i] != '\\' && rhs[i + 1] == '-') {
                token = rhs.substr(i, 3);
                this->tokenizedRegexs[lhs].push_back(token);
                i += 3;
                continue;
            }
            if (!isalpha(rhs[i])) { // if letter i.e. not a definition, just push it
                if (rhs[i] == '\\') {
                    token.push_back(rhs[i]);
                    token.push_back(rhs[i + 1]);
                    i++;
                } else
                    token.push_back(rhs[i]);
                this->tokenizedRegexs[lhs].push_back(token);
                token.clear();
                i++;
            } else { // if a letter i.e. may be a definition
                int j = i;
                while (isalnum(rhs[j])) {// get the whole word
                    token.push_back(rhs[j]);
                    j++;
                }
                string equalValue = getEqualValue(token, lhs);

                if (equalValue == rhs.substr(i, j - i)) {
                    // this mean it is a word not definition, then push it
                    while (rhs[i] != ' ' && i < rhs.size()) {
                        token = rhs[i];
                        this->tokenizedRegexs[lhs].push_back(token);
                        i++;
                    }
                } else {
                    // this is a defintion then, replace the word with it's value
                    rhs.replace(i, j - i, equalValue);
                }

            }
        }
    }
}

string LexicalAnalyzer::getEqualValue(string token, string lhs) {
    for (auto defPair: this->definitions) { // compare each def with the token
        if (token == defPair.first)
            return this->definitions[token];
    }
    // if arrived here this means the word was not definition
    return token;
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

/*
 * Adding possible operations with an int to indicate its priority - top priority = 1 -
 * */
void LexicalAnalyzer::initOperationsMap() {
    operationsPriority.insert(pair<char, int>('*', 1)); // kleene closure
    operationsPriority.insert(pair<char, int>('+', 1)); // positive closure
    operationsPriority.insert(pair<char, int>('|', 0)); // OR
    operationsPriority.insert(pair<char, int>('.', 0)); // AND - concatenation
}