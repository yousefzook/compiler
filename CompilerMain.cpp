//============================================================================
// Name        : test.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "LexecialGenerator.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
static void test();

int main()
{
    LexecialGenerator lexecialGenerator;
    lexecialGenerator.startLexical();
//    test();
    return 0;
}
static void test(){
    cout << "Test if compiled" << endl;
    vector<vector<set<int>>> dfaOld;
    vector<vector<int>> newOld;
    vector<set<int>> temp, temp1, temp2, temp3, temp4, temp5, temp6;
    temp.push_back({0, 1, 2, 4});
    temp.push_back({});
    temp.push_back({});

    temp1.push_back({1, 2});
    temp1.push_back({3});
    temp1.push_back({3});

    temp2.push_back({2, 4});
    temp2.push_back({3});
    temp2.push_back({});

    temp3.push_back({3, 6});
    temp3.push_back({4});
    temp3.push_back({5});

    temp4.push_back({4, 1});
    temp4.push_back({4});
    temp4.push_back({});

    temp5.push_back({5, 6});
    temp5.push_back({});
    temp5.push_back({4});

    temp6.push_back({6});
    temp6.push_back({});
    temp6.push_back({});

    dfaOld.push_back(temp);
    dfaOld.push_back(temp1);
    dfaOld.push_back(temp2);
    dfaOld.push_back(temp3);
    dfaOld.push_back(temp4);
    dfaOld.push_back(temp5);
    dfaOld.push_back(temp6);


    cout << "oldddd \n";
    for (auto it: dfaOld) {
        cout << "output: ";
        for (auto itt: it) {
            for (auto ittt: itt) {
                cout << ittt;
                cout<<"   ";
            }
            cout << "  ,, ";
        }
        cout<<"\n";
    }

    AutomataOperator obj;
/*
    newOld = obj.NFAToDFATable(dfaOld,);
*/

    cout << "\n dfa from nfa is : \n\n";
    for (auto it: newOld) {
        cout << "output: ";
        for (auto itt: it) {
            cout << itt;
            cout << " , ";
        }
        cout << "\n";
    }
}