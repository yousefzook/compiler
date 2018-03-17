/*
 * LexecialGenerator.cpp
 *
 *  Created on: Mar 16, 2018
 *      Author: Rizk
 */

#include "LexecialGenerator.h"
#include "RuleParser.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;


LexecialGenerator::LexecialGenerator()
{
    // TODO Auto-generated constructor stub

}

LexecialGenerator::~LexecialGenerator()
{
    // TODO Auto-generated destructor stub
}

void LexecialGenerator::readRuleFile()
{
    ifstream myReadFile("/home/rizk/Desktop/rules.txt");
    string output;

    for( string line; getline( myReadFile, line ); )
    {
        //cout << line<<endl;
        RuleParser::parseLine(line);
    }
    myReadFile.close();
}

void LexecialGenerator::readProgramFile()
{


}

void LexecialGenerator::startLexical()
{
    readRuleFile();
    readProgramFile();
}

/*
 * [TODO] to be implemented ...........
 */

