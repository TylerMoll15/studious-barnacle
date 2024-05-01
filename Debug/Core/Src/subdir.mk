################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/ApplicationCode.c \
../Core/Src/Button_Driver.c \
../Core/Src/Definitions.c \
../Core/Src/LCD_Driver.c \
../Core/Src/Menu.c \
../Core/Src/RNG.c \
../Core/Src/Scheduler.c \
../Core/Src/Timer_Driver.c \
../Core/Src/fonts.c \
../Core/Src/ili9341.c \
../Core/Src/main.c \
../Core/Src/stm32f4xx_hal_msp.c \
../Core/Src/stm32f4xx_it.c \
../Core/Src/stmpe811.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f4xx.c \
../Core/Src/touchLogic.c 

OBJS += \
./Core/Src/ApplicationCode.o \
./Core/Src/Button_Driver.o \
./Core/Src/Definitions.o \
./Core/Src/LCD_Driver.o \
./Core/Src/Menu.o \
./Core/Src/RNG.o \
./Core/Src/Scheduler.o \
./Core/Src/Timer_Driver.o \
./Core/Src/fonts.o \
./Core/Src/ili9341.o \
./Core/Src/main.o \
./Core/Src/stm32f4xx_hal_msp.o \
./Core/Src/stm32f4xx_it.o \
./Core/Src/stmpe811.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f4xx.o \
./Core/Src/touchLogic.o 

C_DEPS += \
./Core/Src/ApplicationCode.d \
./Core/Src/Button_Driver.d \
./Core/Src/Definitions.d \
./Core/Src/LCD_Driver.d \
./Core/Src/Menu.d \
./Core/Src/RNG.d \
./Core/Src/Scheduler.d \
./Core/Src/Timer_Driver.d \
./Core/Src/fonts.d \
./Core/Src/ili9341.d \
./Core/Src/main.d \
./Core/Src/stm32f4xx_hal_msp.d \
./Core/Src/stm32f4xx_it.d \
./Core/Src/stmpe811.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f4xx.d \
./Core/Src/touchLogic.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/ApplicationCode.cyclo ./Core/Src/ApplicationCode.d ./Core/Src/ApplicationCode.o ./Core/Src/ApplicationCode.su ./Core/Src/Button_Driver.cyclo ./Core/Src/Button_Driver.d ./Core/Src/Button_Driver.o ./Core/Src/Button_Driver.su ./Core/Src/Definitions.cyclo ./Core/Src/Definitions.d ./Core/Src/Definitions.o ./Core/Src/Definitions.su ./Core/Src/LCD_Driver.cyclo ./Core/Src/LCD_Driver.d ./Core/Src/LCD_Driver.o ./Core/Src/LCD_Driver.su ./Core/Src/Menu.cyclo ./Core/Src/Menu.d ./Core/Src/Menu.o ./Core/Src/Menu.su ./Core/Src/RNG.cyclo ./Core/Src/RNG.d ./Core/Src/RNG.o ./Core/Src/RNG.su ./Core/Src/Scheduler.cyclo ./Core/Src/Scheduler.d ./Core/Src/Scheduler.o ./Core/Src/Scheduler.su ./Core/Src/Timer_Driver.cyclo ./Core/Src/Timer_Driver.d ./Core/Src/Timer_Driver.o ./Core/Src/Timer_Driver.su ./Core/Src/fonts.cyclo ./Core/Src/fonts.d ./Core/Src/fonts.o ./Core/Src/fonts.su ./Core/Src/ili9341.cyclo ./Core/Src/ili9341.d ./Core/Src/ili9341.o ./Core/Src/ili9341.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/stm32f4xx_hal_msp.cyclo ./Core/Src/stm32f4xx_hal_msp.d ./Core/Src/stm32f4xx_hal_msp.o ./Core/Src/stm32f4xx_hal_msp.su ./Core/Src/stm32f4xx_it.cyclo ./Core/Src/stm32f4xx_it.d ./Core/Src/stm32f4xx_it.o ./Core/Src/stm32f4xx_it.su ./Core/Src/stmpe811.cyclo ./Core/Src/stmpe811.d ./Core/Src/stmpe811.o ./Core/Src/stmpe811.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f4xx.cyclo ./Core/Src/system_stm32f4xx.d ./Core/Src/system_stm32f4xx.o ./Core/Src/system_stm32f4xx.su ./Core/Src/touchLogic.cyclo ./Core/Src/touchLogic.d ./Core/Src/touchLogic.o ./Core/Src/touchLogic.su

.PHONY: clean-Core-2f-Src

