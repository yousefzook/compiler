/*
 * Symbol.h
 *
 *  Created on: Apr 18, 2018
 *      Author: aboelhamd
 */

#ifndef SYMBOL_H_
#define SYMBOL_H_
#include <string>

using namespace std;

class Symbol
{

public:
    // This is a pure virtual destructor to make this class abstract
    // virtual ~Symbol()=0;
//    struct SymbolState
//    {
//        string name;
//        bool terminal;
//    };


//    SymbolState * createSymbolState(string name, bool terminal);
//    string getName();
//    bool isTerminal();

//protected:
    string name;
    bool terminal;
};

#endif /* SYMBOL_H_ */
