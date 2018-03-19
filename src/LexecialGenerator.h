/*
 * LexecialGenerator.h
 *
 *  Created on: Mar 16, 2018
 *      Author: yousef
 */

#ifndef LEXECIALGENERATOR_H_
#define LEXECIALGENERATOR_H_

#include "RuleParser.h"

class LexecialGenerator: public RuleParser
{
public:
    LexecialGenerator();
    virtual ~LexecialGenerator();

    void startLexical();

private:
    void readRuleFile();
    void readProgramFile();
    void createMainGraph();

};
/*
 * [TODO] to be implemented ...........
*/


#endif /* LEXECIALGENERATOR_H_ */
