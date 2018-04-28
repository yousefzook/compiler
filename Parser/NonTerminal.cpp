/*
 * NonTerminal.cpp
 *
 *  Created on: Apr 19, 2018
 *      Author: aboelhamd
 */

#include "NonTerminal.h"

/*
 * Default instructor, take name of the non terminal
 * */
NonTerminal::NonTerminal(string name) {
    this->name = name;
    terminal = false;
}