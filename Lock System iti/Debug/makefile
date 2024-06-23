################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Stm32f103c6_Drivers/subdir.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include HAL/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
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
EXECUTABLES += \
Lock\ System\ iti.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
Lock\ System\ iti.list \

OBJCOPY_BIN += \
Lock\ System\ iti.bin \


# All Target
all: Lock\ System\ iti.elf secondary-outputs

# Tool invocations
Lock\ System\ iti.elf: $(OBJS) $(USER_OBJS) A:\Projects\Stm32CubeIDE\HAL_And_MCAL\STM32F103C6TX_FLASH.ld
	arm-none-eabi-gcc -gdwarf-2 -o "Lock System iti.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"A:\Projects\Stm32CubeIDE\HAL_And_MCAL\STM32F103C6TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="Lock System iti.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

Lock\ System\ iti.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "Lock System iti.list"
	@echo 'Finished building: $@'
	@echo ' '

Lock\ System\ iti.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "Lock System iti.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
