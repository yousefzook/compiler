################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/AutomataOperator.cpp \
../src/CompilerMain.cpp \
../src/DFA.cpp \
../src/Graph.cpp \
../src/LexecialGenerator.cpp \
../src/NFA.cpp \
../src/RegularDefinition.cpp \
../src/RuleParser.cpp 

OBJS += \
./src/AutomataOperator.o \
./src/CompilerMain.o \
./src/DFA.o \
./src/Graph.o \
./src/LexecialGenerator.o \
./src/NFA.o \
./src/RegularDefinition.o \
./src/RuleParser.o 

CPP_DEPS += \
./src/AutomataOperator.d \
./src/CompilerMain.d \
./src/DFA.d \
./src/Graph.d \
./src/LexecialGenerator.d \
./src/NFA.d \
./src/RegularDefinition.d \
./src/RuleParser.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


