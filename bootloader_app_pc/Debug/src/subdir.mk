################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/main.c 

OBJS += \
./src/main.o 

C_DEPS += \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"/home/anhpt26/git_clone/cpp_practice/bootloader_app_pc/FILE_HANDLE" -I"/home/anhpt26/git_clone/cpp_practice/bootloader_app_pc/SERIAL_PORT" -I"/home/anhpt26/git_clone/cpp_practice/bootloader_app_pc/BOOT_PROC" -I"/home/anhpt26/git_clone/cpp_practice/bootloader_app_pc/src" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


