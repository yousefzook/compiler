/*
 * Terminal.h
 *
 *  Created on: Apr 19, 2018
 *      Author: aboelhamd
 */

#ifndef TERMINAL_H_
#define TERMINAL_H_

#include "Symbol.h"

class Terminal: public Symbol {
public:
    Terminal(string name);
    // comparator for the map, order by inserting
    bool operator<(const Terminal terminal) const;
};

#endif /* TERMINAL_H_ */