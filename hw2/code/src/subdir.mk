################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
./src/stepan_stm32f4_gpio.c \
./src/stepan_stm32f4_bus.c \
./src/stepan_stm32f4_flash.c \
./src/stepan_stm32f4_hal.c \
./src/stepan_stm32f4_tm1637.c \
./src/parallel_transmission.c \
./src/serial_transmission.c \
./src/main.c \
./src/blue_board.c \
./src/button.c \
./src/color.c \
./src/grean_board.c \
./src/init_process.c \
./src/parallel_transmission.c \
./src/serial_transmission.c \
./src/timer.c \
./src/work_mode.c

C_DEPS += \
./src/main.d \
./src/blue_board.d \
./src/button.d \
./src/color.d \
./src/grean_board.d \
./src/init_process.d \
./src/parallel_transmission.d \
./src/serial_transmission.d \
./src/timer.d \
./src/work_mode.d \
./src/stepan_stm32f4_gpio.d \
./src/stepan_stm32f4_bus.d \
./src/stepan_stm32f4_flash.d \
./src/stepan_stm32f4_hal.d \
./src/stepan_stm32f4_tm1637.d

OBJS += \
./src/main.o \
./src/blue_board.o \
./src/button.o \
./src/color.o \
./src/grean_board.o \
./src/init_process.o \
./src/parallel_transmission.o \
./src/serial_transmission.o \
./src/timer.o \
./src/work_mode.o \
./src/stepan_stm32f4_gpio.o \
./src/stepan_stm32f4_bus.o \
./src/stepan_stm32f4_flash.o \
./src/stepan_stm32f4_hal.o \
./src/stepan_stm32f4_tm1637.o




# Each subdirectory must supply rules for building sources it contributes
src/%.o: ./src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -g3 -DDEBUG -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_SEMIHOSTING_STDOUT -DSTM32F407xx -DUSE_HAL_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4-hal" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

#src/stm32f4xx_hal_msp.o: ./src/stm32f4xx_hal_msp.c src/subdir.mk
#	@echo 'Building file: $<'
#	@echo 'Invoking: GNU Arm Cross C Compiler'
#	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -g3 -DDEBUG -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_SEMIHOSTING_STDOUT -DSTM32F407xx -DUSE_HAL_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4-hal" -std=gnu11 -Wno-padded -Wno-missing-prototypes -Wno-missing-declarations -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
#	@echo 'Finished building: $<'
#	@echo ' '


