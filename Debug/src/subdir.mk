################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/DFA.cpp \
../src/Graph.cpp \
../src/GroupedNFA.cpp \
../src/LexicalAnalyzer.cpp \
../src/NFA.cpp \
../src/NFAOperator.cpp \
../src/RulesParser.cpp \
../src/main.cpp 

OBJS += \
./src/DFA.o \
./src/Graph.o \
./src/GroupedNFA.o \
./src/LexicalAnalyzer.o \
./src/NFA.o \
./src/NFAOperator.o \
./src/RulesParser.o \
./src/main.o 

CPP_DEPS += \
./src/DFA.d \
./src/Graph.d \
./src/GroupedNFA.d \
./src/LexicalAnalyzer.d \
./src/NFA.d \
./src/NFAOperator.d \
./src/RulesParser.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


