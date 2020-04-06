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
all: bootloader_app_pc

# Tool invocations
bootloader_app_pc: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C Linker'
	gcc -L"/home/oem/git_clone/cpp_practice/bootloader_app_pc/BOOT_PROC" -L"/home/oem/git_clone/cpp_practice/bootloader_app_pc/COMMON_INCLUDE" -L"/home/oem/git_clone/cpp_practice/bootloader_app_pc/FILE_HANDLE" -L"/home/oem/git_clone/cpp_practice/bootloader_app_pc/SERIAL_PORT" -o "bootloader_app_pc" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) bootloader_app_pc
	-@echo ' '

.PHONY: all clean dependents

-include ../makefile.targets
