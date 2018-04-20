#include <iostream>
#include "LexicalAnalyzer.h"
#include "Symbol.h"
#include "Terminal.h"
#include "NonTerminal.h"
#include "ParsingTable.h"

using namespace std;

int main() {

	// NonTerminals
	NonTerminal* E = new NonTerminal("E");
	NonTerminal* nE = new NonTerminal("E'");
	NonTerminal* T = new NonTerminal("T");
	NonTerminal* nT = new NonTerminal("T'");
	NonTerminal* F = new NonTerminal("F");

	// Terminals
	Terminal* id = new Terminal("id");
	Terminal* plus = new Terminal("+");
	Terminal* asterix = new Terminal("*");
	Terminal* leftBracket = new Terminal("(");
	Terminal* rightBracket = new Terminal(")");
	Terminal* dollar = new Terminal("$");
	Terminal* epsilon = new Terminal("L");

	// preparing nonterminals
	vector<NonTerminal*> nonTerminals;
	nonTerminals.push_back(E);
	nonTerminals.push_back(nE);
	nonTerminals.push_back(T);
	nonTerminals.push_back(nT);
	nonTerminals.push_back(F);

	// preparing terminals
	vector<Terminal*> terminals;
	terminals.push_back(id);
	terminals.push_back(plus);
	terminals.push_back(asterix);
	terminals.push_back(leftBracket);
	terminals.push_back(rightBracket);
	terminals.push_back(dollar);
	terminals.push_back(epsilon);

	// preparing first terminal vectors
	vector<Terminal*> Efirst;
	Efirst.push_back(leftBracket);
	Efirst.push_back(id);

	vector<Terminal*> nEfirst;
	nEfirst.push_back(plus);
	nEfirst.push_back(epsilon);

	vector<Terminal*> Tfirst;
	Tfirst.push_back(leftBracket);
	Tfirst.push_back(id);

	vector<Terminal*> nTfirst;
	nTfirst.push_back(asterix);
	nTfirst.push_back(epsilon);

	vector<Terminal*> Ffirst;
	Ffirst.push_back(leftBracket);
	Ffirst.push_back(id);

	// preparing first
	map<NonTerminal*, vector<Terminal*> > first;
	first[E] = Efirst;
	first[nE] = nEfirst;
	first[T] = Tfirst;
	first[nT] = nTfirst;
	first[F] = Ffirst;

	// preparing follow terminal vectors
	vector<Terminal*> Efollow;
	Efollow.push_back(dollar);
	Efollow.push_back(rightBracket);

	vector<Terminal*> nEfollow;
	nEfollow.push_back(dollar);
	nEfollow.push_back(rightBracket);

	vector<Terminal*> Tfollow;
	Tfollow.push_back(plus);
	Tfollow.push_back(dollar);
	Tfollow.push_back(rightBracket);

	vector<Terminal*> nTfollow;
	nTfollow.push_back(plus);
	nTfollow.push_back(dollar);
	nTfollow.push_back(rightBracket);

	vector<Terminal*> Ffollow;
	Ffollow.push_back(plus);
	Ffollow.push_back(asterix);
	Ffollow.push_back(dollar);
	Ffollow.push_back(rightBracket);

	// preparing follow
	map<NonTerminal*, vector<Terminal*> > follow;
	follow[E] = Efollow;
	follow[nE] = nEfollow;
	follow[T] = Tfollow;
	follow[nT] = nTfollow;
	follow[F] = Ffollow;

	// preparing productions and symbols vectors
	vector<vector<Symbol*> > Eproduction;

	vector<Symbol*> E1;
	E1.push_back(T);
	E1.push_back(nE);
	Eproduction.push_back(E1);

	vector<vector<Symbol*> > nEproduction;

	vector<Symbol*> nE1;
	nE1.push_back(plus);
	nE1.push_back(T);
	nE1.push_back(nE);
	nEproduction.push_back(nE1);

	vector<Symbol*> nE2;
	nE2.push_back(epsilon);
	nEproduction.push_back(nE2);

	vector<vector<Symbol*> > Tproduction;

	vector<Symbol*> T1;
	T1.push_back(F);
	T1.push_back(nT);
	Tproduction.push_back(T1);

	vector<vector<Symbol*> > nTproduction;

	vector<Symbol*> nT1;
	nT1.push_back(asterix);
	nT1.push_back(F);
	nT1.push_back(nT);
	nTproduction.push_back(nT1);

	vector<Symbol*> nT2;
	nT2.push_back(epsilon);
	nTproduction.push_back(nT2);

	vector<vector<Symbol*> > Fproduction;

	vector<Symbol*> F1;
	F1.push_back(leftBracket);
	F1.push_back(E);
	F1.push_back(rightBracket);
	Fproduction.push_back(F1);

	vector<Symbol*> F2;
	F2.push_back(id);
	Fproduction.push_back(F2);

	// preparing productions
	map<NonTerminal*, vector<vector<Symbol*> > > productions;
	productions[E] = Eproduction;
	productions[nE] = nEproduction;
	productions[T] = Tproduction;
	productions[nT] = nTproduction;
	productions[F] = Fproduction;

	map<NonTerminal*, map<Terminal*, int> > parsingTable =
			ParsingTable::constructTable(terminals, nonTerminals, first, follow,
					productions);

	for (unsigned i = 0; i < nonTerminals.size(); i++) {
		cout << nonTerminals[i]->getName() << " => ";

		for (unsigned j = 0; j < terminals.size(); j++) {
			if (terminals[j]->getName() != "L") {
				cout << " ('" << terminals[j]->getName() << "' : "
						<< parsingTable[nonTerminals[i]][terminals[j]] << ") ,";
			}
		}

		cout << endl;
	}

	Terminal t = Terminal("f");

	return 0;
}
