////
//// Created by yousef on 27/03/18.
////
//
//#include "RulesParser.h"
//#include <iostream>
//#include <sstream>
//#include "NFA.h"
//
//void RulesParser::parseLine(string line, map<string, string> *definitions,
//		map<string, string> *regexs, vector<string> *punctuations,
//		vector<string> *keyWords) {
//	int type = getType(line);
//	switch (type) {
//	case 1: // key words line
//		constDefsParse(line, keyWords);
//		break;
//	case 2: // punctuations line
//		constDefsParse(line, punctuations);
//		break;
//	case 3: // regex line
//		regularsParse(line, regexs, ':');
//		break;
//	case 4: // definitoins line
//		regularsParse(line, definitions, '=');
//		break;
//	default: // error in line
//		cout << "Bad line in rules file!" << endl;
//	}
//
//}
//
//void RulesParser::regularsParse(string line, map<string, string> *regMap,
//		char delimiter) {
//	int eqPos = line.find('=');
//	string lhs, rhs;
//	int i = 0;
//	while (line[i] != delimiter) {
//		if (line[i] != ' ')
//			lhs.push_back(line[i]);
//		i++;
//	}
//	i++;
//	while (line[i] == ' ')
//		i++;
//	rhs = line.substr(i);
//
//	regMap->insert(make_pair(lhs, rhs));
//}
//
///*
// * Parse line of constant definitions and push it into the vector of key words
// * or punctuations thorugh constDefs pointer
// */
//void RulesParser::constDefsParse(string line, vector<string> *constDefs) {
//	line.erase(0, 1); // erase from char number 0 till char number 1
//	line.erase(line.size() - 1); // erase from char number line.size() - 1 till end of line
//	vector<string> keyWordsTemp;
//	keyWordsTemp = split(line, ' ');
//	for (auto keyWord : keyWordsTemp)
//		constDefs->push_back(keyWord);
//}
//
///*
// * Split string txt at char ch and return vector of tokens
// */
//vector<string> RulesParser::split(string &txt, char ch) {
//	string token;
//	vector<string> result;
//	stringstream ss(txt);
//	while (getline(ss, token, ch))
//		if (token != "")
//			result.push_back(token);
//
//	return result;
//}
//
///*
// * Function return line type as follow:
// * if key words line : return 1
// * if punctuations line : return 2
// * if regex line : return 3
// * if definition line : return 4
// * else return error code = -1
// */
//int RulesParser::getType(string line) {
//
//	if (line[0] == '{')
//		return 1;
//
//	if (line[0] == '[')
//		return 2;
//
//	if (line.find(':') != string::npos) {
//		int pos = line.find(':');
//		if (line[pos - 1] != '\\') // if euqal then this mean is put as token, e.x. colon = \:
//			return 3;
//	}
//
//	if (line.find('=') != string::npos)
//		return 4;
//
//	return -1;
//}
//
