################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../camera.c \
../dipswitch.c \
../grayscale.c \
../i2c.c \
../lcd_simple.c \
../main.c \
../sobel.c \
../vga.c 

OBJS += \
./camera.o \
./dipswitch.o \
./grayscale.o \
./i2c.o \
./lcd_simple.o \
./main.o \
./sobel.o \
./vga.o 

C_DEPS += \
./camera.d \
./dipswitch.d \
./grayscale.d \
./i2c.d \
./lcd_simple.d \
./main.d \
./sobel.d \
./vga.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Nios II GCC C Compiler'
	nios2-elf-gcc -O3 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


