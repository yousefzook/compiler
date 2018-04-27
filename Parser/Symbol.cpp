/*
 * Symbol.cpp
 *
 *  Created on: Apr 18, 2018
 *      Author: aboelhamd
 */

#include "Symbol.h"
#include "ParsingTable.h"


Symbol::~Symbol() {

}

string Symbol::getName() {
    return name;
}

bool Symbol::isTerminal() {
    return terminal;
}