################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/Keypad_Driver.c \
../HAL/lcd_driver.c 

OBJS += \
./HAL/Keypad_Driver.o \
./HAL/lcd_driver.o 

C_DEPS += \
./HAL/Keypad_Driver.d \
./HAL/lcd_driver.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/%.o HAL/%.su HAL/%.cyclo: ../HAL/%.c HAL/subdir.mk
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -c -I../Inc -I"D:/Embedded_Systems/Workspace/STM32CubeIDE/Embedded C/Drivers/HAL/includes" -I"D:/Embedded_Systems/Workspace/STM32CubeIDE/Embedded C/Drivers/STM32_F103C6_Drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-HAL

clean-HAL:
	-$(RM) ./HAL/Keypad_Driver.cyclo ./HAL/Keypad_Driver.d ./HAL/Keypad_Driver.o ./HAL/Keypad_Driver.su ./HAL/lcd_driver.cyclo ./HAL/lcd_driver.d ./HAL/lcd_driver.o ./HAL/lcd_driver.su

.PHONY: clean-HAL

