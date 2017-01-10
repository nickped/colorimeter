################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Utilities/STM32F0xx-Nucleo/stm32f0xx_nucleo.c 

OBJS += \
./Utilities/STM32F0xx-Nucleo/stm32f0xx_nucleo.o 

C_DEPS += \
./Utilities/STM32F0xx-Nucleo/stm32f0xx_nucleo.d 


# Each subdirectory must supply rules for building sources it contributes
Utilities/STM32F0xx-Nucleo/%.o: ../Utilities/STM32F0xx-Nucleo/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -mfloat-abi=soft -DSTM32F072RBTx -DSTM32F0 -DNUCLEO_F072RB -DSTM32 -DUSE_STDPERIPH_DRIVER -DSTM32F072 -I"C:/Users/Nick/Desktop/stm32M0/eclipseWorkSpace/nucleo-f072rb_stdperiph_lib/CMSIS/core" -I"C:/Users/Nick/Desktop/stm32M0/eclipseWorkSpace/nucleo-f072rb_stdperiph_lib/CMSIS/device" -I"C:/Users/Nick/Desktop/stm32M0/eclipseWorkSpace/nucleo-f072rb_stdperiph_lib/StdPeriph_Driver/inc" -I"C:/Users/Nick/Desktop/stm32M0/eclipseWorkSpace/nucleo-f072rb_stdperiph_lib/Utilities/STM32F0xx-Nucleo" -O3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


