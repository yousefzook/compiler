//============================================================================
// Name        : compilerMain.cpp
// Author      : Yousef Zook
// Version     :
// Copyright   : Your copyright notice
// Description : Compiler in C++, Ansi-style
//============================================================================

#include <iostream>
#include "DFA.h"

using namespace std;

int main() {
	cout << "Test if compiled" << endl;
	vector<vector<int>> dfaOld;
	vector<vector<int>> newOld;
	vector<int> temp, temp1, temp2, temp3;
	temp.push_back(1);
	temp.push_back(2);
	temp.push_back(3);
	temp1.push_back(11);
	temp1.push_back(12);
	temp1.push_back(13);
	temp2.push_back(1);
	temp2.push_back(2);
	temp2.push_back(3);
	temp3.push_back(11);
	temp3.push_back(12);
	temp3.push_back(13);
	dfaOld.push_back(temp);
	dfaOld.push_back(temp1);
	dfaOld.push_back(temp2);
	dfaOld.push_back(temp3);
	temp.clear();
	temp.push_back(101);
	temp.push_back(100);
	temp.push_back(99);
	dfaOld.push_back(temp);

	cout<<"oldddd \n";
	for(auto it: dfaOld){
		for(auto itt: it){
			cout<<"fuck up output: ";
			cout<< itt;
			cout<<"\n";
		}
	}

	cout<<"\nFucken Bitch the new fucken table of fucken dfa in the fucken project\n\n";
	DFA dfa;
	newOld = dfa.minimize(dfaOld);
	for(auto it: newOld){
		for(auto itt: it){
			cout<<"fuck up output: ";
			cout<< itt;
			cout<<"\n";
		}
	}
	return 0;
}
