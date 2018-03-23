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
#include <map>
#include <bits/stdc++.h>
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


void RuleParser::split (string &txt, vector<string> &strs1, char ch)
{
    string token;
    stringstream ss(txt);
    while (getline(ss,token,ch))
    {
        strs1.push_back(token);
    }
}

string RuleParser::removeWhiteSpaces(string str)
{
    vector <string> vector2;
    RuleParser::split(str,vector2,' ');
    for(int j=0; j<vector2.size(); j++)
    {
        char t=vector2[j][0];
        if(!(t<=32))
        {
            return vector2[j];
        }
    }
    return "";
}


int RuleParser::definitionRange(string &str, string &result)
{
    vector <string> vector1;
    RuleParser::split(str,vector1,'-');
    vector <string> vector2;
    if(vector1.size()==1)
    {
        result=RuleParser::removeWhiteSpaces(vector1[0]);
        return 2;
    }
    string startRange,endRange,temp;
    bool check_first_part=true;
    for (int i=0; i<vector1.size(); i++)
    {
        temp=RuleParser::removeWhiteSpaces(vector1[i]);
        if(temp=="")
        {
            continue;
        }
        else if(check_first_part)
        {
            check_first_part=false;
            startRange=temp;
        }
        else
            endRange=temp;
    }
    for(int k=startRange[0]; k<=endRange[0]; k++)
    {
        char element=k;
        result.push_back(element);
    }
    return 1;
}

void RuleParser::keyWordParse(string line)
{
    line.erase(0, 1);
    line.erase(line.size() - 1);
    vector <string> newKeyword;
    RuleParser::split(line,newKeyword,' ');
    //sent vector
    for(int i=0; i<newKeyword.size(); i++)
    {
        string temp=RuleParser::removeWhiteSpaces(newKeyword[i]);
        if(temp!="")
            RegularDefinition::setKeywords(temp);
    }
}

string RuleParser::removeBackSlash(string op)
{
    string newString;
    for(int i=0; i<op.size(); i++)
    {
//    cout<<op.size()<<"enter"<<endl;
        if(op[i]!='\\')
            newString.push_back(op[i]);
    }
    return newString;
}

void RuleParser::operatorsParse(string line)
{
    string key ;
    string value;
    vector<string> values;
    bool keyValid=true;
    for (int i=0; i<line.size(); i++)
    {
        if(line[i]==' ')//|| line[i]=='|')
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
    vector <string>tempValues;

    for(int i=0; i<values.size(); i++)
    {
        tempValues.push_back(RuleParser::removeBackSlash(values[i]));
    }
    //send values and key
    RegularDefinition::createSubGraph(key,tempValues);
    RegularDefinition::setOperators(key,tempValues);

}

void RuleParser::definitionsParse(string line)
{
    vector <string> define;
    string result;
    RuleParser::split(line,define,'=');
    string key=define[0];
    key=RuleParser::removeWhiteSpaces(key);
    string vv=define[1];
    define.clear();
    if(key.find(" ")!=string::npos)
    {
        RuleParser::split( key, define, ' ' );
    }
    define.clear();
    RuleParser::split(vv,define,'|');
    for (int i=0; i<define.size(); i++)
    {
        int check=definitionRange(define[i],result);
        if(check==2)
            RegularDefinition::setUnMatchedDefinitions(key,result);
    }
    RegularDefinition::setDefinitions(key,result);
    // cout<<result<<endl;
}

void RuleParser::punctuationParse(string line)
{
    line.erase(0, 1);
    line.erase(line.size() - 1);
    vector<string> punc;
    RuleParser::split(line,punc,' ');
    RegularDefinition::setPunctuation(punc);
    // send punc
}

bool RuleParser::checkOperators(string line)
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

bool RuleParser::checkExpression(string line)
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

string RuleParser::addSpace(string exp)
{
    string output;
    for(int i=0; i<exp.size(); i++)
    {
        if(exp[i]=='('||exp[i]==')'||exp[i]=='.'||exp[i]=='|'||exp[i]==':')
        {
            output.push_back(' ');
            output.push_back(exp[i]);
            output.push_back(' ');
        }
        else
            output.push_back(exp[i]);
    }
    return output;
}

void RuleParser::regularExpressionParse(string line)
{
    vector<string> v1;
    split(line,v1,':');
    string name=v1[0];
    name = removeWhiteSpaces(name);
    string exp=v1[1];
    exp=RuleParser::addSpace(exp);
    v1.clear();
    split(exp,v1,' ');
    vector<string> conditions;
    for (int i=0; i<v1.size(); i++)
    {
        v1[i]=removeWhiteSpaces(v1[i]);
        if(v1[i]!="")
            conditions.push_back(v1[i]);
    }
    for(int i=0; i<conditions.size(); i++)
    {
        if(conditions[i]=="("||conditions[i]=="."||conditions[i]==")"
                ||conditions[i]=="*"||conditions[i]=="+"||conditions[i]=="|")
            continue;
        else
        {
            typedef std::vector<std::pair<string, string> > MyClassPairs;

            for( MyClassPairs::iterator it = RegularDefinition::unMatchedDefinition.begin();
                    it != RegularDefinition::unMatchedDefinition.end(); ++it )
            {
                string p_a = it->first;
                string p_b = it->second;
                if(conditions[i]==p_a)
                    conditions[i]=p_b;
            }
        }
    }
    RegularDefinition::createSubGraph(name,conditions);
}


void RuleParser::parseLine(string line)
{
    if (line[0] == '{')
    {
        RuleParser::keyWordParse(line);
    }
    else if (line[0] == '[')
    {
        RuleParser::punctuationParse(line);
    }
    else if(RuleParser::checkOperators(line))
    {
        RuleParser::operatorsParse(line);
    }
    else if(RuleParser::checkExpression(line))
    {
        // expression work
        RuleParser::regularExpressionParse(line);
    }
    else if(line=="\L")
    {
        //lamda symbol
    }
    else
    {
        RuleParser::definitionsParse(line);
    }

}
