//
// Created by yousef on 13/04/18.
//

#include "GroupedNFA.h"

GroupedNFA *GroupedNFA::groupedNFA = 0;

GroupedNFA *GroupedNFA::getInstance() {
    if (groupedNFA == 0) {
        groupedNFA = new GroupedNFA;
    }
    return groupedNFA;
}