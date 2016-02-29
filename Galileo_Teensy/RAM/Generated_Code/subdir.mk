################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Generated_Code/Cpu.c" \
"../Generated_Code/PE_LDD.c" \
"../Generated_Code/Vectors.c" \

C_SRCS += \
../Generated_Code/Cpu.c \
../Generated_Code/PE_LDD.c \
../Generated_Code/Vectors.c \

OBJS += \
./Generated_Code/Cpu.o \
./Generated_Code/PE_LDD.o \
./Generated_Code/Vectors.o \

C_DEPS += \
./Generated_Code/Cpu.d \
./Generated_Code/PE_LDD.d \
./Generated_Code/Vectors.d \

OBJS_QUOTED += \
"./Generated_Code/Cpu.o" \
"./Generated_Code/PE_LDD.o" \
"./Generated_Code/Vectors.o" \

C_DEPS_QUOTED += \
"./Generated_Code/Cpu.d" \
"./Generated_Code/PE_LDD.d" \
"./Generated_Code/Vectors.d" \

OBJS_OS_FORMAT += \
./Generated_Code/Cpu.o \
./Generated_Code/PE_LDD.o \
./Generated_Code/Vectors.o \


# Each subdirectory must supply rules for building sources it contributes
Generated_Code/Cpu.o: ../Generated_Code/Cpu.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/Cpu.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/Cpu.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/PE_LDD.o: ../Generated_Code/PE_LDD.c
	@echo 'Building file: $<'
	@echo 'Executing target #6 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/PE_LDD.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/PE_LDD.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/Vectors.o: ../Generated_Code/Vectors.c
	@echo 'Building file: $<'
	@echo 'Executing target #7 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/Vectors.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/Vectors.o"
	@echo 'Finished building: $<'
	@echo ' '


