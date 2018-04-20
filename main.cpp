#include <iostream>
#include "Lexical/LexicalAnalyzer.h"
#include "Parser/ParserGenerator.h"

using namespace std;

int main() {
    cout << "Welcome to our compiler. It will work isa, enjoy! ^_^" << endl;

    LexicalAnalyzer analyzer;
    vector<string> lexicalTokens = analyzer.startLexical();

    ParserGenerator parser;
    parser.startParser(lexicalTokens);

    return 0;
}
