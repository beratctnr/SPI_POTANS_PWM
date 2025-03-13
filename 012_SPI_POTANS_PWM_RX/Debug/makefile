################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32F0xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
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

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := 012_SPI_POTANS_PWM_RX
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
012_SPI_POTANS_PWM_RX.elf \

MAP_FILES += \
012_SPI_POTANS_PWM_RX.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
012_SPI_POTANS_PWM_RX.list \

OBJCOPY_HEX += \
012_SPI_POTANS_PWM_RX.hex \

OBJCOPY_BIN += \
012_SPI_POTANS_PWM_RX.bin \


# All Target
all: main-build

# Main-build Target
main-build: 012_SPI_POTANS_PWM_RX.elf secondary-outputs

# Tool invocations
012_SPI_POTANS_PWM_RX.elf 012_SPI_POTANS_PWM_RX.map: $(OBJS) $(USER_OBJS) C:\Users\MONSTER\STM32CubeIDE\workspace_1.17.0\012_SPI_POTANS_PWM_RX\STM32F030R8TX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "012_SPI_POTANS_PWM_RX.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m0 -T"C:\Users\MONSTER\STM32CubeIDE\workspace_1.17.0\012_SPI_POTANS_PWM_RX\STM32F030R8TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="012_SPI_POTANS_PWM_RX.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

012_SPI_POTANS_PWM_RX.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "012_SPI_POTANS_PWM_RX.list"
	@echo 'Finished building: $@'
	@echo ' '

012_SPI_POTANS_PWM_RX.hex: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "012_SPI_POTANS_PWM_RX.hex"
	@echo 'Finished building: $@'
	@echo ' '

012_SPI_POTANS_PWM_RX.bin: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "012_SPI_POTANS_PWM_RX.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) 012_SPI_POTANS_PWM_RX.bin 012_SPI_POTANS_PWM_RX.elf 012_SPI_POTANS_PWM_RX.hex 012_SPI_POTANS_PWM_RX.list 012_SPI_POTANS_PWM_RX.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX) $(OBJCOPY_BIN)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
