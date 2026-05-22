################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/delay.c \
../Src/main_spi.c \
../Src/syscalls.c \
../Src/sysmem.c \
../Src/w25qxx.c 

OBJS += \
./Src/delay.o \
./Src/main_spi.o \
./Src/syscalls.o \
./Src/sysmem.o \
./Src/w25qxx.o 

C_DEPS += \
./Src/delay.d \
./Src/main_spi.d \
./Src/syscalls.d \
./Src/sysmem.d \
./Src/w25qxx.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32L4 -DSTM32 -DSTM32L476RGTx -c -I../Inc -I"C:/Users/manohar kuduchella/STM32CubeIDE/stm32l4_workspace_LL/SPI_test/Drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/delay.cyclo ./Src/delay.d ./Src/delay.o ./Src/delay.su ./Src/main_spi.cyclo ./Src/main_spi.d ./Src/main_spi.o ./Src/main_spi.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su ./Src/w25qxx.cyclo ./Src/w25qxx.d ./Src/w25qxx.o ./Src/w25qxx.su

.PHONY: clean-Src

