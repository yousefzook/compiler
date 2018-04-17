cmake_minimum_required(VERSION 3.8)
project(clean_compiler)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp NFA.cpp NFA.h DFA.cpp DFA.h Graph.cpp Graph.h RulesParser.cpp RulesParser.h LexicalAnalyzer.cpp LexicalAnalyzer.h GroupedNFA.cpp GroupedNFA.h NFAOperator.cpp NFAOperator.h Bimap.h NFAToDFA.cpp NFAToDFA.h)
add_executable(clean_compiler ${SOURCE_FILES})