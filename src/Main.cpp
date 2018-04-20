#include <iostream>
#include "LexicalAnalyzer.h"
#include "Symbol.h"
#include "Terminal.h"
#include "NonTerminal.h"
#include "ParsingTable.h"

using namespace std;

int main() {
	cout << "Welcome to our compiler. It will work isa, enjoy! ^_^" << endl;
	NonTerminal* E = new NonTerminal("E");
	NonTerminal* nE = new NonTerminal("E'");
	NonTerminal* T = new NonTerminal("T");
	NonTerminal* nT = new NonTerminal("T'");
	NonTerminal* F = new NonTerminal("F");
	NonTerminal* nF = new NonTerminal("F'");
	NonTerminal* P = new NonTerminal("P");

	cout << nE->getName() << endl;

	vector<Terminal> terminals;
	vector<NonTerminal> nonTerminals;
	map<NonTerminal, vector<Terminal> > first;
	map<NonTerminal, vector<Terminal> > follow;
	map<NonTerminal, vector<vector<Symbol*> > > productions;

	map<NonTerminal, map<Terminal, int> > parsingTable =
			ParsingTable::constructTable(terminals, nonTerminals, first, follow,
					productions);

	return 0;
}
