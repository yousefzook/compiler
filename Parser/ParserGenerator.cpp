//
// Created by yousef on 20/04/18.
//

#include "ParserGenerator.h"
#include "ParsingTable.h"

/*
 * Start Parser work
 * */
void ParserGenerator::startParser(vector<string> lexicalTokens) {

    readProductionsFile();
    /*
     * Now terminals, nonTerminals and productions map are  initialized
     * */

    initFirst();
    initFollow();

    ParsingTable::getInstance()->
            constructTable(terminals, nonTerminals, first, follow, productions);




}


/*
 * init follow map
 * */
void ParserGenerator::initFollow() {

}

/*
 * init first map
 * */
void ParserGenerator::initFirst() {

}

/*
 * read productions file and init the
 *  productions map and terminals, nonTerminals vectors
 * */
void ParserGenerator::readProductionsFile() {

}