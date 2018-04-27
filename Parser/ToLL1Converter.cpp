//
// Created by yousef on 27/04/18.
//

#include <iostream>
#include "ToLL1Converter.h"
#include <algorithm>
#include <fstream>
#include <sstream>

/*
 * start LL1 converter
 * */
void ToLL1Converter::startLL1Converter(set<string> * nonTerminals,
                                       map<string, vector<vector<string>>> * productions) {

    this->productions = *productions;
    this->nonTerminals = *nonTerminals;

    cout<<endl<<endl<<"---------------------------------------Parser Output-----------------------------"<<endl;
    print_productions();
    eliminate_ind_LR();

    print_productions();

    eliminate_ind_LF();
    print_productions();

    nonTerminals = &this->nonTerminals;
    productions = &this->productions;


}


void ToLL1Converter::eliminate_ind_LF() {
    bool changed = true; //detect change happening to productions ,(if substitution happens)
    vector<vector<string>> rulesI; //rules of Ai
    string Ai; //takes value of each nonTeminal

    for (auto nonTerminal: nonTerminals) { //for each nonTerminal
        while (changed) { //if productions keep changing
            Ai = nonTerminal;
            rulesI = productions[Ai]; //get productions of Ai
            changed = false;   //restore changed to false , only changed if accepted condition in the below for
            for (auto ruleI:rulesI) { //for each rule of Ai production
                string Aj = ruleI[0]; //get first symbol of that rule
                if (is_nonTerminal(Aj)) //(get_nonTerminal_index(Aj) > get_nonTerminal_index(Ai)))
                    //check if it's nonTerminal or has lower level than Ai (to substitute it in Ai)
                {
                    changed = true; // since we are here the map is guranteed to be changed
                    vector<string> newRule = remove_nonTerminal(
                            ruleI); // remove Aj from the rule it's found in and store that rule as betaJ
                    remove_rule(Ai, ruleI); // remove the rule that Aj is preceeding from productions of Ai

                    //this is the subtitution part
                    //for each rule (ruleJ) of Aj rules,add to productions of Ai new rule (ruleJ betaJ)
                    for (auto ruleJ:productions[Aj]) { //for each rule of Aj rules,add to produc
                        vector<string> tempRule = ruleJ;
                        for (auto k:newRule)
                            tempRule.push_back(k);
                        if (!is_duplicate_rule(Ai,
                                               tempRule)) //make sure that is no duplicate rule,if so it could cause non stop in LF algorithm
                            productions[Ai].push_back(tempRule);
                    }
                }
            }
        }
        changed = true; //re init changed for next nonTerminal


        // after substitution we should check for left factoring in Ai then , solve immediate left recursion in Ai
        string tempAi1;
        string tempAi2 = Ai;
        // this checks if left_factoring produced new non terminal,if true then keep left factoring the new resulting
        // nonTerms until new changes happen(left factoring returns the same nonTerminal paramater as output)

        do {
            tempAi1 = tempAi2;
            tempAi2 = eliminate_imm_LF(tempAi1);
            if (tempAi1 != tempAi2)
                nonTerminals.insert(tempAi2);
        } while (tempAi1 != tempAi2);
        //eliminate_imm_LR(Ai);
    }
}


void ToLL1Converter::eliminate_ind_LR() {
    //sort_nonTerminals();
    bool changed = true; //detect change happening to productions ,(if substitution happens)
    vector<vector<string>> rulesI; //rules of Ai
    string Ai; //takes value of each nonTeminal



    for (auto nonTerminal: nonTerminals) { //for each nonTerminal
        while (changed) { //if productions keep changing
            Ai = nonTerminal;
            rulesI = productions[Ai]; //get productions of Ai
            changed = false;   //restore changed to false , only changed if accepted condition in the below for
            //for (auto ruleI:rulesI) { //for each rule of Ai production
            int AiRulesSize = rulesI.size();
            for (int l = 0; l < AiRulesSize; l++) {
                vector<string> ruleI = rulesI[l];
                string Aj = ruleI[0]; //get first symbol of that rule
                if (is_nonTerminal(Aj) && (get_nonTerminal_index(Aj) < get_nonTerminal_index(Ai)))
                    //check if it's nonTerminal or has lower level than Ai (to substitute it in Ai)
                {
                    changed = true; // since we are here the map is guranteed to be changed
                    vector<string> newRule = remove_nonTerminal(
                            ruleI); // remove Aj from the rule it's found in and store that rule as betaJ
                    //if(!remove_rule(Ai,ruleI)) // remove the rule that Aj is preceeding from productions of Ai
                    remove_rule(Ai, ruleI);
                    //l--; // decrement the counter since we removed element from the vector already,decrement if removed wasn't the last element

                    //this is the subtitution part
                    //for each rule (ruleJ) of Aj rules,add to productions of Ai new rule (ruleJ betaJ)
                    for (auto ruleJ:productions[Aj]) { //for each rule of Aj rules,add to produc
                        vector<string> tempRule = ruleJ;
                        for (auto k:newRule)
                            tempRule.push_back(k);
                        if (!is_duplicate_rule(Ai, tempRule))
                            productions[Ai].push_back(tempRule);
                    }
                }
            }
        }
        changed = true; //re init changed for next nonTerminal


        // after substitution we should check for left factoring in Ai then , solve immediate left recursion in Ai
        string tempAi1;
        string tempAi2 = Ai;
        // this checks if left_factoring produced new non terminal,if true then keep left factoring the new resulting
        // nonTerms until new changes happen(left factoring returns the same nonTerminal paramater as output)

        do {
            tempAi1 = tempAi2;
            tempAi2 = eliminate_imm_LF(tempAi1);

            /* if(tempAi1 != tempAi2)
                 nonTerminals.push_back(tempAi2);*/

        } while (tempAi1 != tempAi2);

        eliminate_imm_LR(Ai);
    }
}


void ToLL1Converter::print_productions() {
    map<string, vector<vector<string>>>::iterator itr;
    for (itr = productions.begin(); itr != productions.end(); ++itr) {
        cout << itr->first << " => ";;
        for (int i = 0; i < itr->second.size(); i++) {
            for (int j = 0; j < itr->second[i].size(); j++) {
                cout << itr->second[i][j] << " ";
            }
            if (i != itr->second.size() - 1)
                cout << " | ";
        }
        cout << "" << endl;
    }
    cout << endl;
}


void ToLL1Converter::eliminate_imm_LR(string nonTerminalName) {
    vector<string> productionTemp;/**just use as atemp for data*/
    vector<vector<string>> rowsTemp;/**just use as atemp for data*/

    if (!productions.count(nonTerminalName))/** return if there is no key in map with this name*/
        return;
    //leftFactor(nonTerminalName); /** remove any left factor in production*/
    bool existResursion = false; /** detect if any left resursion*/

    int productionNumber = 0;
    for (productionNumber = 0; productionNumber < productions[nonTerminalName].size(); productionNumber++) {
        if (productions[nonTerminalName][productionNumber][0] == nonTerminalName) {
            existResursion = true;
            break;
        }
    }
    if (!existResursion)
        return;
    string newNonTerminal = getRandomString(nonTerminalName);
    while (is_nonTerminal(newNonTerminal))
        newNonTerminal = getRandomString(newNonTerminal);

    /** remove the nonterminal name  from its production  */
    productions[nonTerminalName][productionNumber].erase(productions[nonTerminalName][productionNumber].begin());

    vector<string> nonTerminalRule = productions[nonTerminalName][productionNumber]; //handled mistake here
    productions[nonTerminalName].erase(productions[nonTerminalName].begin() + productionNumber);

    for (int iteration = 0; iteration < productions[nonTerminalName].size(); iteration++) {
        if (productions[nonTerminalName][iteration][0] == epsilon)
            continue;
        /**add the new symbol ( A` ) to all productions */
        productions[nonTerminalName][iteration].push_back(newNonTerminal);
    }
    /** insert the symbol   &A` to the new non terminal state in map */
    if (!nonTerminalRule.empty()) {// handle mistake of empty followers of nonTeminal in Rule
        nonTerminalRule.push_back(newNonTerminal);
        rowsTemp.push_back(nonTerminalRule);
    }
    productionTemp.push_back(epsilon);/** add epslon value */
    rowsTemp.push_back(productionTemp);
    productions.insert(std::make_pair(newNonTerminal, rowsTemp));

    /**remove the production with left recursion from the vector of productions */
    //productions[nonTerminalName].
    //      erase(productions[nonTerminalName].begin()+productionNumber);
    if (!productions[nonTerminalName].size()) // handle mistake of empty production
        productions[nonTerminalName].push_back({newNonTerminal});
    /**reset temp data structure used*/
    rowsTemp.clear();
    productionTemp.clear();
}

string ToLL1Converter::eliminate_imm_LF(string nonTerminalName) {
    bool newNonTerminalAdded = false;
    string newNonTerminal;
    vector<string> productionTemp;/**just use as atemp for data*/
    vector<vector<string>> rowsTemp;/**just use as atemp for data*/

    if (!productions.count(nonTerminalName))
        return nonTerminalName;

    for (int productionNumber = 0; productionNumber < productions[nonTerminalName].size(); productionNumber++) {
        int element = 0;/**number of eement in one production*/
        bool indicateNotMatch = false;/** getout from loop if there is not match in level this of itration*/

        for (element = 0; element < productions[nonTerminalName][productionNumber].size(); element++) {
            vector<int> matchFactor;/**factor contain the number of production which match the left factor*/

            /**compare the the element of each production to all elements in other productions at the same index*/
            for (int vectorNumber = 0; vectorNumber < productions[nonTerminalName].size(); vectorNumber++) {

                if (vectorNumber == productionNumber || element >= productions[nonTerminalName][vectorNumber].size()
                    || (leftFactorProduc.size() != 0 && !inVector(vectorNumber, leftFactorProduc.top())))
                    continue;

                /**match the two elements are equal in two different productions */
                if (productions[nonTerminalName][vectorNumber][element] ==
                    productions[nonTerminalName][productionNumber][element])
                    matchFactor.push_back(vectorNumber);

            }
            if (matchFactor.size() == 0)/**detect no match in this level */
            {
                indicateNotMatch = true;
                break;
            }

            /**add all numbers of the productions that matched this production at this element **/
            leftFactorProduc.push(matchFactor);
            matchFactor.clear();
        }
        if (leftFactorProduc.size() == 0)/**there is no element matched any prodctios */
            continue;

        if (indicateNotMatch) {
            /** "element -1" because it breaks from loop after last element matched */
            if (element - 1 < 0)
                continue;
        } else {
            /**this indicate that there is error in the looping because i must equal to the size of productions  */
            if (element != productions[nonTerminalName][productionNumber].size())
                continue;
        }
        element--;/**ecause it breaks from loop after last element matched*/

        vector<int> tos = (vector<int>) leftFactorProduc.top();/**vector getnumber of productions in the last level of elements matched*/

        newNonTerminal = getRandomString(nonTerminalName);
        while (is_nonTerminal(newNonTerminal))
            newNonTerminal = getRandomString(newNonTerminal);
        newNonTerminalAdded = true;

        /**
        *handle first production in vector of vectors
        *
        *the number of elements after the matched element is zero so add only epsilon in the new nonTerminal */
        if (element + 1 >= productions[nonTerminalName][productionNumber].size())
            productionTemp.push_back(epsilon);
        else {
            /**add all elements after matched to the new nonTerminal */
            for (int i = element + 1; i < productions[nonTerminalName][productionNumber].size(); i++)
                productionTemp.push_back(productions[nonTerminalName][productionNumber][i]);


            /** remove them from the start production*/
            productions[nonTerminalName][productionNumber].erase(
                    productions[nonTerminalName][productionNumber].begin() + element + 1,
                    productions[nonTerminalName][productionNumber].end());
        }

        /**add this production to the new nonTerminal vector*/
        productions[nonTerminalName][productionNumber].push_back(newNonTerminal);

        rowsTemp.push_back(productionTemp);
        productions.insert(std::make_pair(newNonTerminal, rowsTemp));
        rowsTemp.clear();
        productionTemp.clear();

        /**handle all productions in vector of vectors*/
        int mapsize = productions[nonTerminalName].size();
        for (int productionNumber2 = 0; productionNumber2 < mapsize; productionNumber2++) {
            if (inVector(productionNumber2, tos)) {
                if (element + 1 >= productions[nonTerminalName][productionNumber2].size())//mistake here
                    productionTemp.push_back(epsilon);
                else {
                    for (int i = element + 1; i < productions[nonTerminalName][productionNumber2].size(); i++)
                        productionTemp.push_back(productions[nonTerminalName][productionNumber2][i]);
                }
                productions[newNonTerminal].push_back(productionTemp);
                productionTemp.clear();
            }
        }
        /**this to handle removing from the vector of vector in the original nonTerminal
        * by add all the not matched to the end of the vector
        *then remove from the start to the old size so the unwanted productions only still
         */
        for (int productionNumber2 = 0; productionNumber2 < mapsize; productionNumber2++) {
            if (!inVector(productionNumber2, tos)) {
                productions[nonTerminalName].push_back(productions[nonTerminalName][productionNumber2]);
            }
        }
        /**remove from first tho the old size of vector */
        productions[nonTerminalName].erase(productions[nonTerminalName].begin(),
                                           productions[nonTerminalName].begin() + mapsize);

        emptyLeftFactorStack();
    }
    if (newNonTerminalAdded)
        return newNonTerminal;
    return nonTerminalName;
}

void ToLL1Converter::emptyLeftFactorStack() {
    while (leftFactorProduc.size() > 0)
        leftFactorProduc.pop();
}


bool ToLL1Converter::inVector(int number, vector<int> numbers) {
    for (int i = 0; i < numbers.size(); i++) {
        if (number == numbers[i])
            return true;
    }
    return false;
}

string ToLL1Converter::getRandomString(string nonTerminalName) {
    string s = nonTerminalName;
    s += "`";
    return s;
}


bool ToLL1Converter::is_duplicate_rule(string nonTerminalName, vector<string> newRule) {
    vector<vector<string>>::iterator ruleIndex;
    ruleIndex = find(productions[nonTerminalName].begin(), productions[nonTerminalName].end(), newRule);
    if (ruleIndex != productions[nonTerminalName].end())
        return true;
    return false;
}

bool ToLL1Converter::remove_rule(string nonTerminal,
                                 vector<string> rule) { //made it bool to know if last element is removed or else so to handle the counter on the vector
    bool lastRemoved = false;
    vector<vector<string>>::iterator ruleIndex;
    ruleIndex = find(productions[nonTerminal].begin(), productions[nonTerminal].end(), rule);
    if (distance(productions[nonTerminal].begin(), ruleIndex) == (productions[nonTerminal].size() - 1))
        lastRemoved = true;
    productions[nonTerminal].erase(ruleIndex);
    return lastRemoved;
}

vector<string> ToLL1Converter::remove_nonTerminal(vector<string> rule) {
    vector<string> temp = rule;
    temp.erase(temp.begin());
    return temp;
}

int ToLL1Converter::get_nonTerminal_index(string nonTerminal) {
    return distance(productions.begin(), productions.find(nonTerminal));
}

bool ToLL1Converter::is_nonTerminal(string sympol) {
    if (productions.find(sympol) != productions.end())
        return 1;
    return 0;
}