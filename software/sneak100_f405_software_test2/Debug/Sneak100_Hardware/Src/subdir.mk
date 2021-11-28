################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sneak100_Hardware/Src/sneak100_adc.c \
../Sneak100_Hardware/Src/sneak100_bluetooth.c \
../Sneak100_Hardware/Src/sneak100_display.c \
../Sneak100_Hardware/Src/sneak100_motors.c \
../Sneak100_Hardware/Src/sneak100_proximity.c 

OBJS += \
./Sneak100_Hardware/Src/sneak100_adc.o \
./Sneak100_Hardware/Src/sneak100_bluetooth.o \
./Sneak100_Hardware/Src/sneak100_display.o \
./Sneak100_Hardware/Src/sneak100_motors.o \
./Sneak100_Hardware/Src/sneak100_proximity.o 

C_DEPS += \
./Sneak100_Hardware/Src/sneak100_adc.d \
./Sneak100_Hardware/Src/sneak100_bluetooth.d \
./Sneak100_Hardware/Src/sneak100_display.d \
./Sneak100_Hardware/Src/sneak100_motors.d \
./Sneak100_Hardware/Src/sneak100_proximity.d 


# Each subdirectory must supply rules for building sources it contributes
Sneak100_Hardware/Src/sneak100_adc.o: ../Sneak100_Hardware/Src/sneak100_adc.c Sneak100_Hardware/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F405xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Moje Wyczyny/My_Poor_Projects/Sneak100_MiniSumo/minisumo-sneak100/software/sneak100_f405_software_test2/Sneak100_Hardware/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Sneak100_Hardware/Src/sneak100_adc.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Sneak100_Hardware/Src/sneak100_bluetooth.o: ../Sneak100_Hardware/Src/sneak100_bluetooth.c Sneak100_Hardware/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F405xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Moje Wyczyny/My_Poor_Projects/Sneak100_MiniSumo/minisumo-sneak100/software/sneak100_f405_software_test2/Sneak100_Hardware/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Sneak100_Hardware/Src/sneak100_bluetooth.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Sneak100_Hardware/Src/sneak100_display.o: ../Sneak100_Hardware/Src/sneak100_display.c Sneak100_Hardware/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F405xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Moje Wyczyny/My_Poor_Projects/Sneak100_MiniSumo/minisumo-sneak100/software/sneak100_f405_software_test2/Sneak100_Hardware/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Sneak100_Hardware/Src/sneak100_display.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Sneak100_Hardware/Src/sneak100_motors.o: ../Sneak100_Hardware/Src/sneak100_motors.c Sneak100_Hardware/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F405xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Moje Wyczyny/My_Poor_Projects/Sneak100_MiniSumo/minisumo-sneak100/software/sneak100_f405_software_test2/Sneak100_Hardware/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Sneak100_Hardware/Src/sneak100_motors.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Sneak100_Hardware/Src/sneak100_proximity.o: ../Sneak100_Hardware/Src/sneak100_proximity.c Sneak100_Hardware/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F405xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Moje Wyczyny/My_Poor_Projects/Sneak100_MiniSumo/minisumo-sneak100/software/sneak100_f405_software_test2/Sneak100_Hardware/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Sneak100_Hardware/Src/sneak100_proximity.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

