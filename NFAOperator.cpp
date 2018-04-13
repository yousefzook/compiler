//
// Created by yousef on 13/04/18.
//

#include "NFAOperator.h"

NFA OR(NFA nfa1, NFA nfa2) {
    NFA temp;
    temp.name = nfa1.name + "|" + nfa2.name;
    return temp;
}

NFA AND(NFA nfa1, NFA nfa2) {
    NFA temp;
    temp.name = nfa1.name + "." + nfa2.name;
    return temp;
}

NFA kleeneClosure(NFA nfa) {
    NFA temp;
    temp.name = nfa.name + "*";
    return temp;
}

NFA positiveClosure(NFA nfa) {
    NFA temp;
    temp.name = nfa.name + "+";
    return temp;
}