cmake_minimum_required(VERSION 3.8)
project(compiler)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        AutomataOperator.cpp
        AutomataOperator.h
        Bimap.h
        CompilerMain.cpp
        DFA.cpp
        DFA.h
        graph.cpp
        graph.h
        LexecialGenerator.cpp
        LexecialGenerator.h
        NFA.cpp
        NFA.h
        RegularDefinition.cpp
        RegularDefinition.h
        RuleParser.cpp
        RuleParser.h
        TransitionTableConverter.cpp
        TransitionTableConverter.h)

add_executable(compiler ${SOURCE_FILES})