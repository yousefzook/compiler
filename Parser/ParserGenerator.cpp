//
// Created by yousef on 20/04/18.
//

#include "ParserGenerator.h"
#include "ParsingTable.h"

/*
 * Start Parser work
 * */
void ParserGenerator::startParser(vector<string> lexicalTokens)
{

    epsilon=createSymbol("\L",true);
    readProductionsFile();
    /*
     * Now terminals, nonTerminals and productions map are  initialized
     * */
    print();
    cout<<"--------------------------------"<<endl;
//    leftFactorAll();
    initFirst();
    initFollow();
    string s="A";
    leftRecursion(s);
    cout<<"-----------------------"<<endl;
//    leftFactor(s);
    print();
//
//    ParsingTable::getInstance()->
//    constructTable(terminals, nonTerminals, first, follow, productions2);




}


/*
 * init follow map
 * */
void ParserGenerator::initFollow()
{

}

/*
 * init first map
 * */
void ParserGenerator::initFirst()
{

}

/*
 * read productions file and init the
 *  productions map and terminals, nonTerminals vectors
 * */
void ParserGenerator::readProductionsFile()
{

    readFile.open("/home/rizk/Public/workspace/compiler2/tests/teste.txt");
    string line;
    while (getline(readFile, line))
        parseLine(line);
    readFile.close();
}


void ParserGenerator::parseLine(string line)
{
    line = removeWhiteSpaces(line);
    int type = getType(line);
    switch (type)
    {
    case 1: // new production line
        productionLine(line);
        break;
    case 2: // continue previous production line
        continueProductionLine(line);
        break;

    default: // error in line
        cout << "Bad line in rules file!" << endl;
    }

}


void ParserGenerator::productionLine(string line)
{
    productionTemp.clear();

    if(line[0]=='#')
        line.erase(0, 1);

    line=removeWhiteSpaces(line);
    int eqPos = line.find('=');    /**split string on = */
    string str1 = removeWhiteSpaces(line.substr (0,eqPos));
    string str2 = removeWhiteSpaces(line.substr (eqPos+1,line.size()));
    previousNonTerminal=str1;
    nonTerminalSet.insert(str1);
    productionParse1(str1,str2);

}


void ParserGenerator::continueProductionLine(string line)
{
    if(productions.count(previousNonTerminal))
    {
        productionParse1(previousNonTerminal,line);
    }
}

void ParserGenerator::productionParse1(string nonTerminalState,string str)
{
    vector <string> productionVec;
    split(str,productionVec,'|');/**split string on '|' */
    int i=0;
    /**handel the first production added to the vector of vector  in the map */
    if(productionVec.size()>0)
    {
        productionParse2(productionVec[0]);
        rowsTemp.push_back(productionTemp);
        if(!productions.count(nonTerminalState))
        {
            productions.insert(std::make_pair(nonTerminalState,rowsTemp));
        }
        productionTemp.clear();
        i++;
    }
    /**the rest elements*/
    while(i<productionVec.size())
    {
        productionParse2(productionVec[i]);
        productions[nonTerminalState].push_back(productionTemp);
        productionTemp.clear();
        i++;
    }
    rowsTemp.clear();
}


void  ParserGenerator::productionParse2(string line)
{
    string current;
    int i=0;
    bool ter=false;
    bool nonTer=true;
    while(i<line.size())
    {
        if(line[i]=='\''&& !ter)/**detect start character of terminal symbol*/
        {
            nonTer=false;
            ter=true;
            i++;
            continue;
        }
        else if(current.size()>0 && (line[i]==' ' || i == line.size()-1 )&& nonTer)/**detect start character of nonterminal symbol*/
        {
            current.push_back(line[i]);
            current=removeWhiteSpaces(current);
            nonTerminalSet.insert(current);
            Symbol nonTerminalState=createSymbol(current,false);
            productionTemp.push_back(nonTerminalState);
            current.clear();
        }
        else if(line[i]=='\'' && ter && current.size()>0 )/**end character of terminal symbol */
        {
            ter=false;
            nonTer=true;
            current=removeWhiteSpaces(current);
            terminalSet.insert(current);
            Symbol terminalState=createSymbol(current,true);
            productionTemp.push_back(terminalState);
            current.clear();
        }
        else if(line[i] != ' ')
            current.push_back(line[i]);

        i++;
    }
    if(current.size()>0)/**detect if non terminal symbols not added to the production*/
    {
        current=removeWhiteSpaces(current);
        nonTerminalSet.insert(current);
        Symbol nonTerminalState=createSymbol(current,false);
        productionTemp.push_back(nonTerminalState);
        current.clear();
    }

}


string ParserGenerator::removeWhiteSpaces(string line)
{
    while (line[0]==' ')
        line.erase(0, 1);
    while(line[line.size()-1]==' ')
        line.erase(line.size() - 1);
    return line;
}

int ParserGenerator::getType(string line)
{
    if(line[0]=='#')
        return 1;/**if  start with # new non terminal */
    else
        return 2;/**else continue to the previous line */
}


void ParserGenerator::split (string &txt, vector<string> &strs1, char ch)
{
    string token;
    stringstream ss(txt);
    while (getline(ss,token,ch))
    {
        token=removeWhiteSpaces(token);
        if(token!="")
            strs1.push_back(token);
    }
}

Symbol ParserGenerator::createSymbol(string name, bool terminal)
{
    Symbol newSymbol;
    newSymbol.terminal =terminal;
    newSymbol.name =name;
    return newSymbol;
}

void ParserGenerator::print()
{
    std::map<string, vector<vector<Symbol >>>::iterator itr;
    for (itr=productions.begin(); itr!=productions.end(); ++itr)
    {
        cout<<itr->first<<" => ";     ;
        for(int i=0; i<itr->second.size(); i++)
        {
            for(int j=0; j<itr->second[i].size(); j++)
            {
                cout<<itr->second[i][j].name<<" ";
            }
            cout<<  " | ";
        }
        cout<<""<<endl;
    }
//    std::set<string>::iterator it;
//    for (it=terminalSet.begin(); it!=terminalSet.end(); ++it)
//        std::cout << *it<<endl;
//    cout<<"-----------------------"<<endl;
//
//    string prev=*(nonTerminalSet.begin());
//    for (it=nonTerminalSet.begin(); it!=nonTerminalSet.end(); ++it)
//    {
//        std::cout << prev<<"."<<"-----"<<*it<<"."<<endl;
//        if(prev==*it)
//            cout<<"done"<<endl;
//        prev=*it;
//
//    }

}


void ParserGenerator::leftRecursion(string nonTeminalName)
{
    if(!productions.count(nonTeminalName))/** return if there is no key in map with this name*/
        return;
    leftFactor(nonTeminalName); /** remove any left factor in production*/
    bool existResursion=false; /** detect if any left resursion*/

    int productionNumber=0;
    for(productionNumber=0; productionNumber < productions[nonTeminalName].size(); productionNumber++)
    {
        if( productions[nonTeminalName][productionNumber][0].name==nonTeminalName)
        {
            existResursion=true;
            break;
        }
    }
    if(!existResursion)
        return ;
    Symbol newNonTerminal = createSymbol(getRandomString(),false);

    /** remove the nonterminal name  from its production  */
    productions[nonTeminalName][productionNumber].erase(productions[nonTeminalName][productionNumber].begin());

    for(int iteration=0; iteration < productions[nonTeminalName].size(); iteration++)
    {
        if( productions[nonTeminalName][iteration][0].name==epsilon.name)
            continue;
        /**add the new symbol ( A` ) to all productions */
        productions[nonTeminalName][iteration].push_back(newNonTerminal);
    }
    /** insert the symbol   &A` to the new non terminal state in map */
    rowsTemp.push_back(productions[nonTeminalName][productionNumber]);
    productionTemp.push_back(epsilon);/** add epslon value */
    rowsTemp.push_back(productionTemp);
    productions.insert(std::make_pair(newNonTerminal.name,rowsTemp));

    /**remove the production with left recursion from the vector of productions */
    productions[nonTeminalName].
    erase(productions[nonTeminalName].begin()+productionNumber);

    /**reset temp data structure used*/
    rowsTemp.clear();
    productionTemp.clear();
}

void ParserGenerator::leftFactor(string nonTeminalName)
{
    if(!productions.count(nonTeminalName))
        return ;

    for(int productionNumber=0; productionNumber < productions[nonTeminalName].size(); productionNumber++)
    {
        int element=0;/**number of eement in one production*/
        bool indicateNotMatch=false;/** getout from loop if there is not match in level this of itration*/

        for(element=0; element<productions[nonTeminalName][productionNumber].size(); element++)
        {
            vector <int> matchFactor;/**factor contain the number of production which match the left factor*/

            /**compare the the element of each production to all elements in other productions at the same index*/
            for(int vectorNumber=0; vectorNumber < productions[nonTeminalName].size(); vectorNumber++)
            {

                if(vectorNumber==productionNumber||element>=productions[nonTeminalName][vectorNumber].size()
                        ||(leftFactorProduc.size()!=0 && ! inVector(vectorNumber,leftFactorProduc.top())))
                    continue;

                /**match the two elements are equal in two different productions */
                if(productions[nonTeminalName][vectorNumber][element].name==
                        productions[nonTeminalName][productionNumber][element].name)
                    matchFactor.push_back(vectorNumber);

            }
            if(matchFactor.size()==0)/**detect no match in this level */
            {
                indicateNotMatch=true;
                break;
            }

            /**add all numbers of the productions that matched this production at this element **/
            leftFactorProduc.push(matchFactor);
            matchFactor.clear();
        }
        if(leftFactorProduc.size()==0)/**there is no element matched any prodctios */
            continue;

        if(indicateNotMatch)
        {
            /** "element -1" because it breaks from loop after last element matched */
            if(element-1<0)
                continue;
        }
        else
        {
            /**this indicate that there is error in the looping because i must equal to the size of productions  */
            if(element!=productions[nonTeminalName][productionNumber].size())
                continue;
        }
        element--;/**ecause it breaks from loop after last element matched*/

        vector <int> tos= leftFactorProduc.top();/**vector getnumber of productions in the last level of elements matched*/

        Symbol newNonTerminal = createSymbol(getRandomString(),false);


        /**
        *handle first production in vector of vectors
        *
        *the number of elements after the matched element is zero so add only epsilon in the new nonTerminal */
        if(element +1>=productions[nonTeminalName][productionNumber].size())
            productionTemp.push_back(epsilon);
        else
        {
            /**add all elements after matched to the new nonTerminal */
            for(int i=element+1; i<productions[nonTeminalName][productionNumber].size(); i++)
                productionTemp.push_back(productions[nonTeminalName][productionNumber][i]);

            /** remove them from the start production*/
            productions[nonTeminalName][productionNumber].erase(
                productions[nonTeminalName][productionNumber].begin()+element+1,productions[nonTeminalName][productionNumber].end());
        }

        /**add this production to the new nonTerminal vector*/
        productions[nonTeminalName][productionNumber].push_back(newNonTerminal);

        rowsTemp.push_back(productionTemp);
        productions.insert(std::make_pair(newNonTerminal.name,rowsTemp));
        rowsTemp.clear();
        productionTemp.clear();

        /**handle all productions in vector of vectors*/
        int mapsize=productions[nonTeminalName].size();
        for(int productionNumber2=0; productionNumber2 < mapsize; productionNumber2++)
        {
            if(inVector(productionNumber2,tos))
            {
                if(element +1>=productions[nonTeminalName][productionNumber].size())
                    productionTemp.push_back(epsilon);
                else
                {
                    for(int i=element+1; i<productions[nonTeminalName][productionNumber2].size(); i++)
                        productionTemp.push_back(productions[nonTeminalName][productionNumber2][i]);
                }
                productions[newNonTerminal.name].push_back(productionTemp);
                productionTemp.clear();
            }
        }
        /**this to handle removing from the vector of vector in the original nonTerminal
        * by add all the not matched to the end of the vector
        *then remove from the start to the old size so the unwanted productions only still
         */
        for(int productionNumber2=0; productionNumber2 < mapsize; productionNumber2++)
        {
            if(!inVector(productionNumber2,tos))
            {
                productions[nonTeminalName].push_back(productions[nonTeminalName][productionNumber2]);
            }
        }
        /**remove from first tho the old size of vector */
        productions[nonTeminalName].erase(productions[nonTeminalName].begin(),productions[nonTeminalName].begin()+ mapsize);

        emptyLeftFactorStack();
    }
}

void ParserGenerator::leftFactorAll()
{
    std::map<string, vector<vector<Symbol >>>::iterator itr;
    for (itr=productions.begin(); itr!=productions.end(); ++itr)
    {
        for(int productionNumber=0; productionNumber < itr->second.size(); productionNumber++)
        {
            int element=0;
            bool exit=false;
            for(element=0; element<itr->second[productionNumber].size(); element++)
            {
                vector <int> matchFactor;
                for(int vectorNumber=0; vectorNumber < itr->second.size(); vectorNumber++)
                {
                    if(vectorNumber==productionNumber||element>=itr->second[vectorNumber].size()
                            ||(leftFactorProduc.size()!=0 && ! inVector(vectorNumber,leftFactorProduc.top())))
                        continue;

                    if(itr->second[vectorNumber][element].name==itr->second[productionNumber][element].name)
                        matchFactor.push_back(vectorNumber);

                }
                if(matchFactor.size()==0)
                {
                    exit=true;
                    break;
                }
                leftFactorProduc.push(matchFactor);
                matchFactor.clear();
            }
            if(leftFactorProduc.size()==0)
                continue;

            if(exit)
            {
                if(element-1<0)
                    continue;

                else
                    element--;
            }
            else
            {
                if(element!=itr->second[productionNumber].size())
                    continue;
                element--;
                cout<<"here"<<endl;
            }
            vector <int> tos= leftFactorProduc.top();

            Symbol newNonTerminal = createSymbol(getRandomString(),false);

            if(element +1>=itr->second[productionNumber].size())
                productionTemp.push_back(epsilon);

            else
            {
                for(int i=element+1; i<itr->second[productionNumber].size(); i++)
                    productionTemp.push_back(itr->second[productionNumber][i]);

                itr->second[productionNumber].erase(
                    itr->second[productionNumber].begin()+element+1,itr->second[productionNumber].end());
            }

            itr->second[productionNumber].push_back(newNonTerminal);

            rowsTemp.push_back(productionTemp);
            productions.insert(std::make_pair(newNonTerminal.name,rowsTemp));
            rowsTemp.clear();
            productionTemp.clear();
            int mapsize=itr->second.size();
            for(int productionNumber2=0; productionNumber2 < mapsize; productionNumber2++)
            {
                if(inVector(productionNumber2,tos))
                {
                    if(element +1>=itr->second[productionNumber].size())
                        productionTemp.push_back(epsilon);
                    else
                    {
                        for(int i=element+1; i<itr->second[productionNumber2].size(); i++)
                            productionTemp.push_back(itr->second[productionNumber2][i]);
                    }
                    productions[newNonTerminal.name].push_back(productionTemp);
                    productionTemp.clear();
                }
            }
            for(int productionNumber2=0; productionNumber2 < mapsize; productionNumber2++)
            {
                if(!inVector(productionNumber2,tos))
                {
                    itr->second.push_back(itr->second[productionNumber2]);
                }
            }
            itr->second.erase(itr->second.begin(),itr->second.begin()+ mapsize);

            emptyLeftFactorStack();
        }
    }
}


void ParserGenerator::emptyLeftFactorStack()
{
    while(leftFactorProduc.size()>0)
        leftFactorProduc.pop();
}


bool ParserGenerator::inVector(int number,vector<int>numbers)
{
    for(int i=0; i<numbers.size(); i++)
    {
        if(number==numbers[i])
            return true;
    }
    return false;
}

char genRandom()  // Random string generator function.
{

    char alphanum[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    int stringLength = sizeof(alphanum) - 1;

    return alphanum[rand() % stringLength];
}

string ParserGenerator::getRandomString()
{
    srand(time(0));
    string s;
    for(int z=0; z < 6; z++)
    {
        s.push_back(genRandom());
    }
    s.push_back(validChar);
    validChar++;
    cout<<"new nonTerminal name : "<<s<<endl;
    return s;
}

















