################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/BT_actions.c \
../Sources/Events.c \
../Sources/Ultrasonic.c \
../Sources/main.c \
../Sources/sa_mtb.c 

OBJS += \
./Sources/BT_actions.o \
./Sources/Events.o \
./Sources/Ultrasonic.o \
./Sources/main.o \
./Sources/sa_mtb.o 

C_DEPS += \
./Sources/BT_actions.d \
./Sources/Events.d \
./Sources/Ultrasonic.d \
./Sources/main.d \
./Sources/sa_mtb.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/%.o: ../Sources/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"/home/charly/workspace.kds/Kinetis-ARM/medidorDistancia/Static_Code/PDD" -I"/home/charly/workspace.kds/Kinetis-ARM/medidorDistancia/Static_Code/IO_Map" -I"/home/charly/workspace.kds/Kinetis-ARM/medidorDistancia/Sources" -I"/home/charly/workspace.kds/Kinetis-ARM/medidorDistancia/Generated_Code" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


