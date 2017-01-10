################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include startup/subdir.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: test.elf

dependents:
	-cd C:/Users/Nick/Desktop/stm32M0/eclipseWorkSpace/nucleo-f072rb_stdperiph_lib/Release && $(MAKE) all

# Tool invocations
test.elf: $(OBJS) $(USER_OBJS) C:/Users/Nick/Desktop/stm32M0/eclipseWorkSpace/nucleo-f072rb_stdperiph_lib/Release/libnucleo-f072rb_stdperiph_lib.a
	@echo 'Building target: $@'
	@echo 'Invoking: MCU GCC Linker'
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -mfloat-abi=soft -L"C:\Users\Nick\Desktop\stm32M0\eclipseWorkSpace\nucleo-f072rb_stdperiph_lib\Release" -T"C:\Users\Nick\Desktop\stm32M0\eclipseWorkSpace\test\LinkerScript.ld" -Wl,-Map=output.map -Wl,--gc-sections -lm -o "test.elf" @"objects.list" $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

post-build:
	-@echo 'Generating binary and Printing size information:'
	arm-none-eabi-objcopy -O binary "test.elf" "test.bin"
	arm-none-eabi-size -B "test.elf"
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build
C:/Users/Nick/Desktop/stm32M0/eclipseWorkSpace/nucleo-f072rb_stdperiph_lib/Release/libnucleo-f072rb_stdperiph_lib.a:

-include ../makefile.targets
