//
// Created by yousef on 20/04/18.
//

#include <iostream>
#include <vector>
#include <map>
#include <stack>

#include "ParserTracer.h"

using namespace std;
void ParserTracer::start(vector<string> lexicalTokens, map<string, map<string, int>> parsingTable,
                         map<string, vector<vector<string>>> productionsStr, string startState) {

    this->productions = productionsStr;
    this->parsingTable = parsingTable;

    lexicalTokens.push_back("$"); //initially push a dollar sign to stack
    init_tracerStack(startState); //push the starting state to stack

    print_stack(); //print the stack initially

    while(!tracerStack.empty()){
        for(int i = 0; i < lexicalTokens.size(); i++){

            if(!isTerminal(lexicalTokens[i]))
            {
                cout<<"ERROR: Discard \""<<lexicalTokens[i]<<"\"";
                continue;
            }

            string* stackTop = &tracerStack.top();
            if(isNonTerminal(*stackTop)){//check if top of stack is nonTerminal
                //get its production entries from parseTable
                map<string, int> parsTabEntries = parsingTable[*stackTop];

                if(parsTabEntries[lexicalTokens[i]] == ERROR){
                    //if Error found ,discard input token
                    cout<<"ERROR: Illegal\""<<*stackTop<<"\" - discard \""<<lexicalTokens[i]<<"\"";
                    cout<<endl<<endl;
                    continue;
                }
                else if(parsTabEntries[lexicalTokens[i]] == SYNCH){
                    // if synch is found pop the nonTerminal from the stack, keep current index of input tokens unchanged
                    tracerStack.pop();
                    i--;
                    print_stack();
                    continue;
                }
                else{ //if there exist a production ,pop non terminal, push equivalent production back to front
                    tracerStack.pop();
                    int indexOfProduction = parsTabEntries[lexicalTokens[i]];
                    //terminal of input used to access the map of productions in the transTable entry,the entry hold an int used to give the index of the production in the nonTerminal productions vector in productions map
                    vector<string> tempProduction = productions[*stackTop][indexOfProduction];
                    while(!tempProduction.empty())
                    {
                        string j = (string)tempProduction.back();
                        tempProduction.pop_back();

                        if(j!="L") //if not epsilon production
                            tracerStack.push(j);
                    }

                    i--; //keeps index of lexical unchanged in next iteration
                    print_stack();
                    continue;
                }
            }else{ //if top of stack is terminal
                if(*stackTop == lexicalTokens[i]){ //match input
                    if(*stackTop != "$"){
                        cout<<"Matching \""<<*stackTop<<"\""<<endl<<endl;
                        tracerStack.pop();
                        print_stack();
                        continue;
                    }else{
                        cout<<" --------------"<<endl;
                        cout<<"| Parsing Ends |"<<endl;
                        cout<<" --------------"<<endl<<endl;
                        cout<<"    (~‾▿‾)~ "<<endl;

                        tracerStack.pop();
                        print_stack();
                        continue;
                    }
                }else{ //mismatching input with top of stack terminal
                    //cout<<"ERROR:mismatch stackTop("<<*stackTop<<") and input("<<lexicalTokens[i]<<")";
                    if(*stackTop == "$")
                    {
                        while(lexicalTokens[i] != "$"){
                            cout<<"ERROR: Discard \""<<lexicalTokens[i]<<"\"";
                            cout<<endl<<endl;
                            i++;
                        }
                        i--;
                    }else{
                        cout<<"Error: Missing \""<<*stackTop<<"\" , inserted"<<endl<<endl;
                        i--;
                        tracerStack.pop();
                        print_stack();
                        continue;
                    }
                }
            }

        }
        while(!tracerStack.empty()){ //if input finished but the stack isn't empty, keep popping giving miss error
            string* stackTop = &tracerStack.top();
            cout<<"Error: Missing \""<<*stackTop<<"\" , inserted"<<endl<<endl;
            tracerStack.pop();
            print_stack();
        }

    }


}

void ParserTracer::print_stack() {
    stack<string> temp = tracerStack;
    if(!tracerStack.empty() | tracerStack.size() == 1)
    {
        for(int i = 0; i<tracerStack.size()-1;i++) {
            cout << temp.top() << " ";
            temp.pop();
        }
        cout<<endl;
    }
}

bool ParserTracer::isNonTerminal(string symbol)
{
    if(parsingTable.find(symbol) != parsingTable.end())
        return 1;
    return 0;
}
bool ParserTracer::isTerminal(string symbol)
{
    if(parsingTable.empty())
        return 0;

    std::pair<string, map<string, int>> temp = *parsingTable.begin();
    map<string, int> row = temp.second;
    if(row.find(symbol) != row.end())
        return 1;
    return 0;
}


void ParserTracer::init_tracerStack(string startState) {
    tracerStack.push("$");
    tracerStack.push(startState);
}
