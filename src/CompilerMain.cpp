//============================================================================
// Name        : test.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "LexecialGenerator.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
/*
	ifstream myReadFile("/home/rizk/Desktop/rules.txt");
	string output;

	for( string line; getline( myReadFile, line ); )
	{
		cout << line<<endl;

	}
	myReadFile.close();*/
	startLexical();
	return 0;
}



































/*#include <iostream>
#include <vector>
#include <string>
using namespace std;


size_t split(const std::string &txt, std::vector<std::string> &strs2, char ch)
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
//    if(txt.find(ch)!= std::string::npos){
//        cout<<ch<<"lllllll"<<endl;
    strs.push_back( txt.substr( initialPos, std::min( pos, txt.size() ) - initialPos + 1 ) );
//}
    for(int i=0;i<strs.size();i++){
        if(strs[i].find(" ")==string::npos&&strs[i].find_first_not_of("\t\n ")!=string::npos)
        {
            strs2.push_back(strs[i]);
        }
    }
    return strs.size();
}



int main()
{
    string l="{ahmed i                                  f els:e while done}";
    vector<string> v;
    int x;
    if(l[0]=='{')
    {

        l.erase(0, 1);
        l.erase(l.size() - 1);
        x= split( l, v, ' ' );
//dump( cout, v );
    }
    for(int i=0; i<v.size(); i++)
    {
        //if(v[i].find_first_not_of("\t\n ")!=string::npos){
//        if(v[i].find(":")==string::npos&&v[i].find_first_not_of("\t\n ")!=string::npos)
//        {
            cout <<v[i]<<endl;
//        }
    }
    cout<<"fffffffffffffffffffffffffffffffffff"<<endl;
    for(int i=0; i<v.size(); i++)
    {
        cout<<v[i]<<endl;

    }
    return 0;
}*/
