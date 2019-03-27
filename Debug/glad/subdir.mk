################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../glad/glad.c 

OBJS += \
./glad/glad.o 

C_DEPS += \
./glad/glad.d 


# Each subdirectory must supply rules for building sources it contributes
glad/%.o: ../glad/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I../inc -O0 -g3 -Wall -Wextra -c -fmessage-length=0 -fsanitize=address -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


