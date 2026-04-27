################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../BSP/src/INA226.c \
../BSP/src/oled.c 

OBJS += \
./BSP/src/INA226.o \
./BSP/src/oled.o 

C_DEPS += \
./BSP/src/INA226.d \
./BSP/src/oled.d 


# Each subdirectory must supply rules for building sources it contributes
BSP/src/%.o BSP/src/%.su BSP/src/%.cyclo: ../BSP/src/%.c BSP/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F030x8 -c -I../Core/Inc -I"D:/Bootloader_Course/usb_c_dc_cv_power_supply/BSP/inc" -I"D:/Bootloader_Course/usb_c_dc_cv_power_supply/BSP/src" -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-BSP-2f-src

clean-BSP-2f-src:
	-$(RM) ./BSP/src/INA226.cyclo ./BSP/src/INA226.d ./BSP/src/INA226.o ./BSP/src/INA226.su ./BSP/src/oled.cyclo ./BSP/src/oled.d ./BSP/src/oled.o ./BSP/src/oled.su

.PHONY: clean-BSP-2f-src

