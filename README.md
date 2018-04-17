# CS321 Compiler Project
A compiler with Lexical and Parser generators implemented with C++ and tested on Java language rules.
---
## 1. Lexical Generator
Lexical Generator is the first phase in compilers, which generate a lexical automata that checks for lexical in the program according to a given rules file.
Rules file has the punctations, regular definitions and expressoins

The lexical analyzer generator is required to automatically construct a lexical analyzer from
a regular expression description of a set of tokens. The tool is required to construct a
nondeterministic finite automata (NFA) for the given regular expressions, combine these
NFAs together with a new starting state, convert the resulting NFA to a DFA, minimize it
and emit the transition table for the reduced DFA together with a lexical analyzer program
that simulates the resulting DFA machine.

**Lexical Rules:**
* The tokens of the given language are: identifiers, numbers, keywords, operators and
punctuation symbols.
* The token id matches a letter followed by zero or more letters or digits.
* The token num matches an unsigned integer or a floating- point number. The number
consists of one or more decimal digits, an optional decimal point followed by one or
more digits and an optional exponent consisting of an E followed by one or more digits.
* Keywords are reserved. The given keywords are: int, float, boolean, if, else, while.
* Operators are: +, -, *, /, =, <=, <, >, >=, !=, ==
* Punctuation symbols are parentheses, curly brackets, commas and semicolons.
* Blanks between tokens are optional.

**Lexical Rules Input File Format:**
* Lexical rules input file is a text file.
* Regular definitions are lines in the form LHS = RHS
* Regular expressions are lines in the form LHS: RHS
* Keywords are enclosed by { } in separate lines.
* Punctuations are enclosed by [ ] in separate lines
* \L represents Lambda symbol.
* The following symbols are used in regular definitions and regular expressions with the
meaning discussed in class: - | + * ( )
* Any reserved symbol needed to be used within the language, is preceded by an
escape backslash character.

---
## Before running:
#### Edits required:
1. Edit rules file Path with your own path in `LexicalGenerator.cpp` file in line 294 `readRulesFile` function >> 
```C++
readFile.open("/home/yousef/tests/rules.txt");
```
2. Edit input file Path with your own path in `LexicalGenerator.cpp` file in line 57 `readTestFile` function >>
```C++
readFile.open("/home/yousef/tests/input.txt");
```
3. Edit output file Path with your own path in `TestProgram.cpp` file in line 323 `executeTokensFile` function >>
```C++
outfile.open("/home/yousef/tests/tokens.txt");
```
---
## Assumptions:
* Rules File should be separated by spaces between each expression and letter or word. For example, If there is a regular definition defined as 
`digit = 0-9` and a regular experssion that is `x : digityz` The lexical generator will consider `digityz` as a word not as `digit` and then `yz`
* (https://en.wikipedia.org/wiki/Maximal_munch)[Maximal Munch] and Priority -in case of tie, first priority rule will be considerd- rules are appiled.
* Only `positive clousre +`, `kleene closure *`, `ORing |` and `Concatenation .` are applied, but is very easy to add more operators in the code, just to the next:
  * edit in `LexicalAnalyzer` files >> `initOperationsMap` and `doOperationInTOS` functions
  * add the operator function in `NFAOperator`
  
---
## Contributers:
1. (https://github.com/aboelhamd)[Abo-ElHamd Ali]
2. (https://github.com/AhmedMahmoudRizk)[Ahmed Rizk]
3. (https://github.com/yahia-elshahawy)[Yahia ElShahawy]

