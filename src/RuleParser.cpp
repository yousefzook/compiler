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
#include <sstream>
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


void split (string &txt, vector<string> &strs1, char ch)
{
    string token;
    stringstream ss(txt);
    while (getline(ss,token,ch))
    {
        strs1.push_back(token);
    }
}



void definitionRange(string &str, string &result)
{

    vector <string> vector1;
    split(str,vector1,'-');
    vector <string> vector2;
    if(vector1.size()==1)
    {
        cout<<"not match"<<endl;
        for (int i=0; i<vector1.size(); i++)
        {
            split(vector1[i],vector2,' ');
            for(int j=0; j<vector2.size(); j++)
            {
                char t=vector2[j][0];
                if((t>=48&&t<=57)||(t>=65&&t<=90)||(t>=97&&t<=128))
                {
                    result=vector2[j];
                    return;
                }
            }
        }
    }
    string part1_str,part2_str;
    bool check_first_part=true;
    for (int i=0; i<vector1.size(); i++)
    {
        split(vector1[i],vector2,' ');
        for(int j=0; j<vector2.size(); j++)
        {
            char t=vector2[j][0];
            if((t>=48&&t<=57)||(t>=65&&t<=90)||(t>=97&&t<=128))
            {
                if(check_first_part)
                {
                    part1_str=vector2[j];
                    check_first_part=false;
                }
                else
                    part2_str=vector2[j];

            }
        }
        vector2.clear();
    }
    for(int k=part1_str[0]; k<=part2_str[0]; k++)
    {
        char element=k;
        result.push_back(element);
    }
}

void keyWordParse(string line)
{
    line.erase(0, 1);
    line.erase(line.size() - 1);
    vector <string> newKeyword;
    split(line,newKeyword,' ');
    for (int i=0; i<newKeyword.size(); i++)
    {
        //  cout<<newKeyword[i]<<endl;
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
    //cout <<key <<endl;
    for(int i=0; i<values.size(); i++)
    {
        //cout <<values[i]<<endl;
    }
    //send values and key
}
void definitionsParse(string line)
{
    vector <string> define;
    string result;
    split(line,define,'=');
    string key=define[0];
    string vv=define[1];
    define.clear();
    if(key.find(" ")!=string::npos)
    {
        split( key, define, ' ' );
    }
    define.clear();
    split(vv,define,'|');
    for (int i=0; i<define.size(); i++)
    {
        definitionRange(define[i],result);
    }
    cout<<result<<endl;
}

void punctuationParse(string line)
{
    line.erase(0, 1);
    line.erase(line.size() - 1);
    vector<string> punc;
    split(line,punc,' ');
    for (int i=0; i<punc.size(); i++)
    {
//        if(punc[i]!=' ')
        //cout<<punc[i]<<endl;
    }

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




