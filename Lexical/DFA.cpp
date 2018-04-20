//
// Created by yousef on 27/03/18.
//

#include <iostream>
#include "DFA.h"
#include "GroupedNFA.h"

/*
 * Minimze DFA States
 * */
void DFA::minimizeDFA()
{
    init_DFA();
    partition();
    build_min_DFA();
    cout<<endl<<"Equivalent Subset is "<<endl;
    print_subsets(equivSets[equivSets.size()-1]);
    print_accepted_Map();
}

/*
 * init marking vector and equivalent states in DFA to minimize it
 * */
void DFA::init_DFA()
{
    vector<int> notFinal,final;

    for(int i = 0; i<transTable.size(); i++)
    {
        markingVec.push_back(0); //init marking vector too, all 0 means all set aren't taken initially
        if (check_status(i))//since state is found in map then it's accepted
        {
            setIndex.push_back(1);
            final.push_back(i);

        }
        else
        {
            setIndex.push_back(0);
            notFinal.push_back(i);

        }
    }
    equivSets.push_back({});
    if(!notFinal.empty())
        equivSets[0].push_back(notFinal);
    if(!final.empty())
        equivSets[0].push_back(final);
    counter = 0;
}

void DFA::partition()
{
    vector<vector<int>> currRow = equivSets[counter];
    bool noNewSets = false;
    vector<vector<int>> equiv;
    while(!noNewSets)  //loop as long as there is no new sets
    {
        counter ++;    //that counter keeps track of current level of partitioning
        equivSets.push_back({});    //add new empty level of partitioning
        for(auto i : currRow)
        {
            equiv = subset(i); //subset each set of current row into new subsets
            for (auto j : equiv)   //for each of these subsets
            {
                for (auto k:j)    //for each vector
                {
                    setIndex[k] = equivSets[counter].size(); //update status of each state to have index of it's curr new subset
                }
                equivSets[counter].push_back(j);
            }
        }
        if(equivSets[counter].size() == equivSets[counter-1].size())
            noNewSets = true;

        currRow = equivSets[counter];

        for(int k = 0 ; k<markingVec.size(); k++) //reinitialize the marking vector for all sets
            markingVec[k] = 0;
    }
}

/*
 * distinguish between states by next states ,
 * and if both states is accepted they are distinguishable by it's accepting string first
*/
vector<vector<int>> DFA::subset(vector<int> equivSet)
{
    vector<int> temp,nextStates1,nextStates2;
    vector<vector<int>> equivSubsets;
    bool equivFlag = true;
    for(int i = 0 ; i < equivSet.size(); i++)
    {
        if(!markingVec[equivSet[i]])  //if state is not marked(not taken before)
        {
            temp.push_back(equivSet[i]); //create a new set for it
            markingVec[equivSet[i]] = 1;  //mark it
            nextStates1 = transTable[equivSet[i]]; //get next states of the current state

            if(i!= equivSet.size()-1) //if not at the end of the set
                for(int j = i+1 ; j<equivSet.size(); j++) //loop on all next states
                {
                    if(!markingVec[equivSet[j]])   //if it's not marked then it's not taken (need to test if it's equivalent to it's prev state then)
                    {
                        if(check_status(equivSet[i]))
                            if(acceptedStates[equivSet[i]] != acceptedStates[equivSet[j]])//if both accept different cases ,distinguish
                                continue;
                        nextStates2 = transTable[equivSet[j]];
                        for (int k = 0; k < nextStates1.size(); k++)   //loop on nextStates
                        {
                            if (setIndex[nextStates1[k]] != setIndex[nextStates2[k]])   //compare that they are not equivalent
                            {
                                equivFlag = false; //as soon as i found that next states doesn't match in sets exit
                                break;
                            }
                        }
                        if (equivFlag)   // if an equivalent state of the current state is found
                        {
                            temp.push_back(equivSet[j]); // put them together in same state
                            markingVec[equivSet[j]] = 1; // mark the found equiv state as taken
                        }
                        equivFlag = true;
                    }

                }
            equivSubsets.push_back(temp);// equiv subsets has now the new equvalent set if found
            temp.clear();
        }
    }
    return equivSubsets;
}
/**
 * build the new minimized DFA table and new map of acceptance state
 */
void DFA::build_min_DFA()
{
    vector<int> minRow;
    vector<vector<int>> tempTransTable = transTable; //store prev transtable
    map<int,string> newAcceptedStates;
    transTable.clear(); //clear current transition table
    int setCount = 0;
    for(auto set : equivSets[counter]) //loop on final sets
    {
        for (auto nextState:tempTransTable[set[0]]) //loop on next states of first of each set
        {
            minRow.push_back(setIndex[nextState]); //push containing set of these next states in a row
        }
        if (check_status(set[0])) //if one of the states in a set is accepted insert it as a pair of the index of the set and string printed of it's acceptance
            newAcceptedStates.insert(pair<int,string>(setCount,acceptedStates[set[0]]));

        transTable.push_back(minRow); //push the whole row into the new DFA table
        minRow.clear(); //make sure to clear row before next iteration
        setCount++;
    }
    acceptedStates = newAcceptedStates;
}

/**
 * check if state is acceptance or not by checking whether it's in acceptedState map or not
 */
int DFA::check_status(int statusIndex)
{
    if(acceptedStates.find(statusIndex) != acceptedStates.end())
        return 1;
    return 0;
}

/*
 * print accepted states
 * */
void DFA::print_accepted_Map()
{
    cout<<endl<<"Accepted Map contains:\n";
    for (map<int,string>::iterator it = acceptedStates.begin(); it!=acceptedStates.end(); ++it)
        cout << it->first << " => " << it->second << '\n';
}

/*
 * Print subsets of DFA classes
 * */
void DFA::print_subsets(vector<vector<int>> subsetsVector)
{
    for(auto i : subsetsVector)
    {
        cout<<"{ ";
        for(auto j:i)
            cout<<j<<" ";
        cout<<"}"<<endl;
    }
}

/*
 * Pretty print the dfa in console
 * */
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
        if(check_status(i))
            cout<<"\t Accepted>> "<<acceptedStates[i];
        cout << endl;
    }
}