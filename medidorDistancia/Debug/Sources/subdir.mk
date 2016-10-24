################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/Events.c \
../Sources/Ultrasonic.c \
../Sources/main.c 

OBJS += \
./Sources/Events.o \
./Sources/Ultrasonic.o \
./Sources/main.o 

C_DEPS += \
./Sources/Events.d \
./Sources/Ultrasonic.d \
./Sources/main.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/%.o: ../Sources/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"/home/karl/workspace.kds/Kinetis-ARM/medidorDistancia/Static_Code/PDD" -I"/home/karl/workspace.kds/Kinetis-ARM/medidorDistancia/Static_Code/IO_Map" -I"/home/karl/workspace.kds/Kinetis-ARM/medidorDistancia/Sources" -I"/home/karl/workspace.kds/Kinetis-ARM/medidorDistancia/Generated_Code" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


