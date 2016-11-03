################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Generated_Code/Cpu.c \
../Generated_Code/KSDK1.c \
../Generated_Code/PE_LDD.c \
../Generated_Code/Pwm1.c \
../Generated_Code/PwmLdd1.c \
../Generated_Code/SERVO1.c \
../Generated_Code/SERVO1_TimerUnit.c \
../Generated_Code/Vectors.c \
../Generated_Code/WAIT1.c 

OBJS += \
./Generated_Code/Cpu.o \
./Generated_Code/KSDK1.o \
./Generated_Code/PE_LDD.o \
./Generated_Code/Pwm1.o \
./Generated_Code/PwmLdd1.o \
./Generated_Code/SERVO1.o \
./Generated_Code/SERVO1_TimerUnit.o \
./Generated_Code/Vectors.o \
./Generated_Code/WAIT1.o 

C_DEPS += \
./Generated_Code/Cpu.d \
./Generated_Code/KSDK1.d \
./Generated_Code/PE_LDD.d \
./Generated_Code/Pwm1.d \
./Generated_Code/PwmLdd1.d \
./Generated_Code/SERVO1.d \
./Generated_Code/SERVO1_TimerUnit.d \
./Generated_Code/Vectors.d \
./Generated_Code/WAIT1.d 


# Each subdirectory must supply rules for building sources it contributes
Generated_Code/%.o: ../Generated_Code/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"/home/charly/workspace.kds/Kinetis-ARM/ServoMotor/Static_Code/PDD" -I"/home/charly/workspace.kds/Kinetis-ARM/ServoMotor/Static_Code/IO_Map" -I"/home/charly/workspace.kds/Kinetis-ARM/ServoMotor/Sources" -I"/home/charly/workspace.kds/Kinetis-ARM/ServoMotor/Generated_Code" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


