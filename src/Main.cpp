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
	NonTerminal* nF = new NonTerminal("F'");
	NonTerminal* P = new NonTerminal("P");

	// Terminals
	Terminal* leftBracket = new Terminal("(");
	Terminal* rightBracket = new Terminal(")");
	Terminal* a = new Terminal("a");
	Terminal* b = new Terminal("b");
	Terminal* plus = new Terminal("+");
	Terminal* asterix = new Terminal("*");
	Terminal* Em = new Terminal("Em");
	Terminal* dollar = new Terminal("$");
	Terminal* epsilon = new Terminal("L");

	// preparing nonterminals
	vector<NonTerminal*> nonTerminals;
	nonTerminals.push_back(E);
	nonTerminals.push_back(nE);
	nonTerminals.push_back(T);
	nonTerminals.push_back(nT);
	nonTerminals.push_back(F);
	nonTerminals.push_back(nF);
	nonTerminals.push_back(P);

	// preparing terminals
	vector<Terminal*> terminals;
	terminals.push_back(leftBracket);
	terminals.push_back(rightBracket);
	terminals.push_back(a);
	terminals.push_back(b);
	terminals.push_back(plus);
	terminals.push_back(asterix);
	terminals.push_back(Em);
	terminals.push_back(dollar);
	terminals.push_back(epsilon);

	// preparing first terminal vectors
	vector<Terminal*> Efirst;
	Efirst.push_back(leftBracket);
	Efirst.push_back(a);
	Efirst.push_back(b);
	Efirst.push_back(Em);

	vector<Terminal*> nEfirst;
	nEfirst.push_back(plus);
	nEfirst.push_back(epsilon);

	vector<Terminal*> Tfirst;
	Tfirst.push_back(leftBracket);
	Tfirst.push_back(a);
	Tfirst.push_back(b);
	Tfirst.push_back(Em);

	vector<Terminal*> nTfirst;
	nTfirst.push_back(leftBracket);
	nTfirst.push_back(a);
	nTfirst.push_back(b);
	nTfirst.push_back(Em);
	nTfirst.push_back(epsilon);

	vector<Terminal*> Ffirst;
	Ffirst.push_back(leftBracket);
	Ffirst.push_back(a);
	Ffirst.push_back(b);
	Ffirst.push_back(Em);

	vector<Terminal*> nFfirst;
	nFfirst.push_back(asterix);
	nFfirst.push_back(epsilon);

	vector<Terminal*> Pfirst;
	Pfirst.push_back(leftBracket);
	Pfirst.push_back(a);
	Pfirst.push_back(b);
	Pfirst.push_back(Em);

	// preparing first
	map<NonTerminal*, vector<Terminal*> > first;
	first[E] = Efirst;
	first[nE] = nEfirst;
	first[T] = Tfirst;
	first[nT] = nTfirst;
	first[F] = Ffirst;
	first[nF] = nFfirst;
	first[P] = Pfirst;

	// preparing follow terminal vectors
	vector<Terminal*> Efollow;
	Efollow.push_back(rightBracket);
	Efollow.push_back(dollar);

	vector<Terminal*> nEfollow;
	nEfollow.push_back(rightBracket);
	nEfollow.push_back(dollar);

	vector<Terminal*> Tfollow;
	Tfollow.push_back(plus);
	Tfollow.push_back(rightBracket);
	Tfollow.push_back(dollar);

	vector<Terminal*> nTfollow;
	nTfollow.push_back(plus);
	nTfollow.push_back(rightBracket);
	nTfollow.push_back(dollar);

	vector<Terminal*> Ffollow;
	Ffollow.push_back(leftBracket);
	Ffollow.push_back(a);
	Ffollow.push_back(b);
	Ffollow.push_back(Em);
	Ffollow.push_back(plus);
	Ffollow.push_back(rightBracket);
	Ffollow.push_back(dollar);

	vector<Terminal*> nFfollow;
	nFfollow.push_back(leftBracket);
	nFfollow.push_back(a);
	nFfollow.push_back(b);
	nFfollow.push_back(Em);
	nFfollow.push_back(plus);
	nFfollow.push_back(rightBracket);
	nFfollow.push_back(dollar);

	vector<Terminal*> Pfollow;
	Pfollow.push_back(asterix);
	Pfollow.push_back(leftBracket);
	Pfollow.push_back(a);
	Pfollow.push_back(b);
	Pfollow.push_back(Em);
	Pfollow.push_back(plus);
	Pfollow.push_back(rightBracket);
	Pfollow.push_back(dollar);

	// preparing follow
	map<NonTerminal*, vector<Terminal*> > follow;
	follow[E] = Efollow;
	follow[nE] = nEfollow;
	follow[T] = Tfollow;
	follow[nT] = nTfollow;
	follow[F] = Ffollow;
	follow[nF] = nFfollow;
	follow[P] = Pfollow;

	// preparing productions and symbols vectors
	vector<vector<Symbol*> > Eproduction;

	vector<Symbol*> E1;
	E1.push_back(T);
	E1.push_back(nE);
	Eproduction.push_back(E1);

	vector<vector<Symbol*> > nEproduction;

	vector<Symbol*> nE1;
	nE1.push_back(plus);
	nE1.push_back(E);
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
	nT1.push_back(T);
	nTproduction.push_back(nT1);

	vector<Symbol*> nT2;
	nT2.push_back(epsilon);
	nTproduction.push_back(nT2);

	vector<vector<Symbol*> > Fproduction;

	vector<Symbol*> F1;
	F1.push_back(P);
	F1.push_back(nF);
	Fproduction.push_back(F1);

	vector<vector<Symbol*> > nFproduction;

	vector<Symbol*> nF1;
	nF1.push_back(asterix);
	nF1.push_back(F);
	nFproduction.push_back(nF1);

	vector<Symbol*> nF2;
	nF2.push_back(epsilon);
	nFproduction.push_back(nF2);

	vector<vector<Symbol*> > Pproduction;

	vector<Symbol*> P1;
	P1.push_back(leftBracket);
	P1.push_back(E);
	P1.push_back(rightBracket);
	Pproduction.push_back(P1);

	vector<Symbol*> P2;
	P2.push_back(a);
	Pproduction.push_back(P2);

	vector<Symbol*> P3;
	P3.push_back(b);
	Pproduction.push_back(P3);

	vector<Symbol*> P4;
	P4.push_back(Em);
	Pproduction.push_back(P4);

	// preparing productions
	map<NonTerminal*, vector<vector<Symbol*> > > productions;
	productions[E] = Eproduction;
	productions[nE] = nEproduction;
	productions[T] = Tproduction;
	productions[nT] = nTproduction;
	productions[F] = Fproduction;
	productions[nF] = nFproduction;
	productions[P] = Pproduction;

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
