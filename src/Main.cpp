#include <iostream>
#include "LexicalAnalyzer.h"
#include "Symbol.h"
#include "Terminal.h"
#include "NonTerminal.h"
#include "ParsingTable.h"

using namespace std;

int main() {

	// NonTerminals
	NonTerminal* E = new NonTerminal("bexpr");
	NonTerminal* nE = new NonTerminal("bexpr''");
	NonTerminal* T = new NonTerminal("bterm");
	NonTerminal* nT = new NonTerminal("bterm'");
	NonTerminal* P = new NonTerminal("bfactor");

	// Terminals
	Terminal* leftBracket = new Terminal("(");
	Terminal* rightBracket = new Terminal(")");
	Terminal* Not = new Terminal("not");
	Terminal* Or = new Terminal("or");
	Terminal* And = new Terminal("and");
	Terminal* True = new Terminal("true");
	Terminal* False = new Terminal("false");
	Terminal* dollar = new Terminal("$");
	Terminal* epsilon = new Terminal("L");

	// preparing nonterminals
	vector<NonTerminal*> nonTerminals;
	nonTerminals.push_back(E);
	nonTerminals.push_back(nE);
	nonTerminals.push_back(T);
	nonTerminals.push_back(nT);
	nonTerminals.push_back(P);

	// preparing terminals
	vector<Terminal*> terminals;
	terminals.push_back(leftBracket);
	terminals.push_back(rightBracket);
	terminals.push_back(Not);
	terminals.push_back(Or);
	terminals.push_back(And);
	terminals.push_back(True);
	terminals.push_back(False);
	terminals.push_back(dollar);
	terminals.push_back(epsilon);

	// preparing first terminal vectors
	vector<Terminal*> Efirst;
	Efirst.push_back(Not);
	Efirst.push_back(leftBracket);
	Efirst.push_back(True);
	Efirst.push_back(False);

	vector<Terminal*> nEfirst;
	nEfirst.push_back(Or);
	nEfirst.push_back(epsilon);

	vector<Terminal*> Tfirst;
	Tfirst.push_back(Not);
	Tfirst.push_back(leftBracket);
	Tfirst.push_back(True);
	Tfirst.push_back(False);

	vector<Terminal*> nTfirst;
	nTfirst.push_back(And);
	nTfirst.push_back(epsilon);

	vector<Terminal*> Pfirst;
	Pfirst.push_back(Not);
	Pfirst.push_back(leftBracket);
	Pfirst.push_back(True);
	Pfirst.push_back(False);

	// preparing first
	map<NonTerminal*, vector<Terminal*> > first;
	first[E] = Efirst;
	first[nE] = nEfirst;
	first[T] = Tfirst;
	first[nT] = nTfirst;
	first[P] = Pfirst;

	// preparing follow terminal vectors
	vector<Terminal*> Efollow;
	Efollow.push_back(dollar);
	Efollow.push_back(rightBracket);

	vector<Terminal*> nEfollow;
	nEfollow.push_back(dollar);
	nEfollow.push_back(rightBracket);

	vector<Terminal*> Tfollow;
	Tfollow.push_back(Or);
	Tfollow.push_back(dollar);
	Tfollow.push_back(rightBracket);

	vector<Terminal*> nTfollow;
	nTfollow.push_back(Or);
	nTfollow.push_back(dollar);
	nTfollow.push_back(rightBracket);

	vector<Terminal*> Pfollow;
	Pfollow.push_back(And);
	Pfollow.push_back(Or);
	Pfollow.push_back(dollar);
	Pfollow.push_back(rightBracket);

	// preparing follow
	map<NonTerminal*, vector<Terminal*> > follow;
	follow[E] = Efollow;
	follow[nE] = nEfollow;
	follow[T] = Tfollow;
	follow[nT] = nTfollow;
	follow[P] = Pfollow;

	// preparing productions and symbols vectors
	vector<vector<Symbol*> > Eproduction;

	vector<Symbol*> E1;
	E1.push_back(T);
	E1.push_back(nE);
	Eproduction.push_back(E1);

	vector<vector<Symbol*> > nEproduction;

	vector<Symbol*> nE1;
	nE1.push_back(Or);
	nE1.push_back(T);
	nE1.push_back(nE);
	nEproduction.push_back(nE1);

	vector<Symbol*> nE2;
	nE2.push_back(epsilon);
	nEproduction.push_back(nE2);

	vector<vector<Symbol*> > Tproduction;

	vector<Symbol*> T1;
	T1.push_back(P);
	T1.push_back(nT);
	Tproduction.push_back(T1);

	vector<vector<Symbol*> > nTproduction;

	vector<Symbol*> nT1;
	nT1.push_back(And);
	nT1.push_back(P);
	nT1.push_back(nT);
	nTproduction.push_back(nT1);

	vector<Symbol*> nT2;
	nT2.push_back(epsilon);
	nTproduction.push_back(nT2);

	vector<vector<Symbol*> > Pproduction;

	vector<Symbol*> P1;
	P1.push_back(Not);
	P1.push_back(P);
	Pproduction.push_back(P1);

	vector<Symbol*> P2;
	P2.push_back(leftBracket);
	P2.push_back(E);
	P2.push_back(rightBracket);
	Pproduction.push_back(P2);

	vector<Symbol*> P3;
	P3.push_back(True);
	Pproduction.push_back(P3);

	vector<Symbol*> P4;
	P4.push_back(False);
	Pproduction.push_back(P4);

	// preparing productions
	map<NonTerminal*, vector<vector<Symbol*> > > productions;
	productions[E] = Eproduction;
	productions[nE] = nEproduction;
	productions[T] = Tproduction;
	productions[nT] = nTproduction;
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
