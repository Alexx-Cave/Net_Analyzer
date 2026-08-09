################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/IPaddr.cpp \
../src/Net_analyzer.cpp \
../src/tools.cpp 

CPP_DEPS += \
./src/IPaddr.d \
./src/Net_analyzer.d \
./src/tools.d 

OBJS += \
./src/IPaddr.o \
./src/Net_analyzer.o \
./src/tools.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/home/sasha/eclipse-workspace/Net_analyzer/libtui/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/IPaddr.d ./src/IPaddr.o ./src/Net_analyzer.d ./src/Net_analyzer.o ./src/tools.d ./src/tools.o

.PHONY: clean-src

