/*
 * RuleParser.cpp
 *
 *  Created on: Mar 16, 2018
 *      Author: yousef
 */

#include "RuleParser.h"


#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

/*
 * [TODO] to be implemented ...........
 */

RuleParser::RuleParser()
{
    // TODO Auto-generated constructor stub

}

RuleParser::~RuleParser()
{
    // TODO Auto-generated destructor stub
}


void split(const std::string &txt, std::vector<std::string> &strs2, char ch)
{
    size_t pos = txt.find( ch );
    size_t initialPos = 0;
    vector<string> strs;
    strs.clear();

    // Decompose statement
    while( pos != std::string::npos )
    {
        strs.push_back( txt.substr( initialPos, pos - initialPos ) );
        initialPos = pos + 1;
        pos = txt.find( ch, initialPos );
    }
    // Add the last one
    strs.push_back( txt.substr( initialPos, std::min( pos, txt.size() ) - initialPos + 1 ) );
    for(int i=0; i<strs.size(); i++)
    {
        if(strs[i].find(" ")==string::npos&&strs[i].find_first_not_of("\t\n ")!=string::npos)
        {
            strs2.push_back(strs[i]);
        }
    }
    //return strs.size();
}


void keyWordParse(string line)
{
    line.erase(0, 1);
    line.erase(line.size() - 1);
    vector <string> newKeyword;
    split(line,newKeyword,' ');
    for (int i=0; i<newKeyword.size(); i++)
    {
        cout<<newKeyword[i]<<endl;
    }
    //sent vector


}

void operatorsParse(string line)
{

    string key ;
    string value;
    vector<string> values;
    bool keyValid=true;
    for (int i=0; i<line.size(); i++)
    {
        if(line[i]==' '|| line[i]=='|')
        {
            if(value.size()>0)
            {
                values.push_back(value);
                value.clear();
            }
            continue;
        }
        else if(line[i]==':')
        {
            keyValid =false;
            continue;
        }
        if(keyValid)
        {
            key.push_back(line[i]);
            continue;
        }
        else
        {
            value.push_back(line[i]);
        }
    }
    if(value.size()>0)
    {
        values.push_back(value);
        value.clear();
    }
    cout <<key <<endl;
    for(int i=0; i<values.size(); i++)
    {
        cout <<values[i]<<endl;
    }
    //send values and key
}
void definitionsParse(string line) {}

void punctuationParse(string line)
{
    line.erase(0, 1);
    line.erase(line.size() - 1);
    string punc;
    for (int i=0; i<line.size(); i++)
    {
        if(line[i]!=' ')
            punc.push_back(line[i]);
    }
    cout <<punc<<endl;

    // send punc
}
bool checkOperators(string line)
{
    if(line.find(":")!=string::npos)
    {
        bool dots_detect=false;
        int i=0;
        for(i=0; i<line.size() ; i++)
        {
            if(line[i]==':')
            {
                dots_detect=true;
                break;
            }
        }
        if(!dots_detect)
            return false;
        i++;
        for(i; i<line.size(); i++)
        {
            if(line[i]==' ')
                continue;
            else if(!((line[i]>=65&&line[i]<=90)||(line[i]>=97&&line[i]<=122)))
                return true;
            return false;
        }
    }
}
bool checkExpression(string line)
{


    if(line.find(":")!=string::npos)
    {
        bool dots_detect=false;
        int i=0;
        for(i=0; i<line.size() ; i++)
        {
            if(line[i]==':')
            {
                dots_detect=true;
                break;
            }
        }
        if(!dots_detect)
            return false;
        i++;
        for(i; i<line.size(); i++)
        {
            if(line[i]==' ')
                continue;
            else if((line[i]>=65&&line[i]<=90)||(line[i]>=97&&line[i]<=122))
                return true;
            return false;
        }
    }
}

void parseLine(string line)
{



    if (line[0] == '{')
    {
        keyWordParse(line);
    }
    else if (line[0] == '[')
    {
        punctuationParse(line);
    }
    else if(checkOperators(line))
    {
        operatorsParse(line);
    }
    else if(checkExpression(line))
    {
       cout<<"match expression"<<endl;
        // expression work
    }
    else
    {
        definitionsParse(line);
    }

}




