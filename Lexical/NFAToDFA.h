//
// Created by yousef on 14/04/18.
//

#ifndef CLEAN_COMPILER_NFATODFA_H
#define CLEAN_COMPILER_NFATODFA_H

#include "DFA.h"
#include "GroupedNFA.h"

DFA convertToDFA();
set<int> getClosures(set<int> set);
string editAcceptedDFAStates(set<int> set);
#endif //CLEAN_COMPILER_NFATODFA_H
