################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: led_clock.axf

# Tool invocations
led_clock.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"F:\Dropbox\lpc\workspace\CMSISv2p00_LPC11Uxx\Debug" -Xlinker -Map="led_clock.map" -Xlinker --gc-sections -mcpu=cortex-m0 -mthumb -T "HelloLPC_Debug.ld" -o "led_clock.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES) led_clock.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "led_clock.axf" ; arm-none-eabi-objdump -S led_clock.axf >led_clock.lss ; arm-none-eabi-objcopy -O ihex led_clock.axf led_clock.hex ; #arm-none-eabi-objcopy -v -O binary "led_clock.axf" "led_clock.bin" ; #checksum -p LPC11U12_201 -d "led_clock.bin" ;
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
