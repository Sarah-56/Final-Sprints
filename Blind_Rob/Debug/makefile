################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include MCAL/UART/subdir.mk
-include MCAL/Timer/Timer2/subdir.mk
-include MCAL/Timer/Timer0/subdir.mk
-include MCAL/DIO/subdir.mk
-include MCAL/ADC/subdir.mk
-include HAL/voice_sensor/subdir.mk
-include HAL/Servo/subdir.mk
-include HAL/Motor/subdir.mk
-include HAL/LED/subdir.mk
-include HAL/Bluetooth/subdir.mk
-include Application/MainApp/subdir.mk
-include Application/App2/subdir.mk
-include Application/App1/subdir.mk
-include Application/APP3/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
Blind_Rob.lss \

SIZEDUMMY += \
sizedummy \


# All Target
all: Blind_Rob.elf secondary-outputs

# Tool invocations
Blind_Rob.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Blind_Rob.map -mmcu=atmega2560 -o "Blind_Rob.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Blind_Rob.lss: Blind_Rob.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Blind_Rob.elf  >"Blind_Rob.lss"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Blind_Rob.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega2560 Blind_Rob.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Blind_Rob.elf
	-@echo ' '

secondary-outputs: $(LSS) $(SIZEDUMMY)

.PHONY: all clean dependents

-include ../makefile.targets
