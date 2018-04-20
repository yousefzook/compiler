#include <iostream>
#include "LexicalAnalyzer.h"
#include "Symbol.h"
#include "Terminal.h"
#include "NonTerminal.h"

using namespace std;

int main() {
	cout << "Welcome to our compiler. It will work isa, enjoy! ^_^" << endl;

	Terminal* s = new Terminal("s");
	NonTerminal* E = new NonTerminal("E");

	vector<Symbol*> v;

	cout << "Is symbol s terminal ? ";
	cout << s->getName() << endl;

	cout << "Is symbol E terminal ? ";
	cout << E->isTerminal() << endl;

	return 0;
}
