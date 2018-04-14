//
// Created by yousef on 27/03/18.
//

#include <iostream>
#include "DFA.h"
#include "GroupedNFA.h"


void DFA::minimizeDFA() {

}

void DFA::prettyPrintTransTable() {
    cout << endl;
    cout<<"\t\t\t\t\t\t\t\tDFA TABLE"<<endl;
    cout<<"     "<<"\t";
    for(int i = 0; i < GroupedNFA::getInstance()->allInputs.size(); i++)
        cout<<GroupedNFA::getInstance()->allInputs[i]<<"\t";
    cout <<endl<< "-------------------------------------------------------------------------" << endl;
    for (int i = 0; i < transTable.size(); i++) {
        if(i<10)
            cout<<"0";
        cout<<i<<" ::\t";
        for (int j = 0; j < transTable[0].size(); j++) {
            cout<<transTable[i][j];
            cout << "\t";
        }
        cout << endl;
    }
}