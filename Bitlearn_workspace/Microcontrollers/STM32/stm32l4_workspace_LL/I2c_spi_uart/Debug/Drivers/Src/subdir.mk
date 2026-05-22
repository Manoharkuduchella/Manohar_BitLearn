################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Src/stm32l476xx_gpio_drivers.c \
../Drivers/Src/stm32l476xx_i2c_drivers.c \
../Drivers/Src/stm32l476xx_rcc_driver.c \
../Drivers/Src/stm32l476xx_spi.c \
../Drivers/Src/stm32l476xx_uart_driver.c 

OBJS += \
./Drivers/Src/stm32l476xx_gpio_drivers.o \
./Drivers/Src/stm32l476xx_i2c_drivers.o \
./Drivers/Src/stm32l476xx_rcc_driver.o \
./Drivers/Src/stm32l476xx_spi.o \
./Drivers/Src/stm32l476xx_uart_driver.o 

C_DEPS += \
./Drivers/Src/stm32l476xx_gpio_drivers.d \
./Drivers/Src/stm32l476xx_i2c_drivers.d \
./Drivers/Src/stm32l476xx_rcc_driver.d \
./Drivers/Src/stm32l476xx_spi.d \
./Drivers/Src/stm32l476xx_uart_driver.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Src/%.o Drivers/Src/%.su Drivers/Src/%.cyclo: ../Drivers/Src/%.c Drivers/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32L4 -DSTM32 -DSTM32L476RGTx -c -I../Inc -I"C:/Users/manohar kuduchella/STM32CubeIDE/stm32l4_workspace_LL/I2c_spi_uart/Drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-Src

clean-Drivers-2f-Src:
	-$(RM) ./Drivers/Src/stm32l476xx_gpio_drivers.cyclo ./Drivers/Src/stm32l476xx_gpio_drivers.d ./Drivers/Src/stm32l476xx_gpio_drivers.o ./Drivers/Src/stm32l476xx_gpio_drivers.su ./Drivers/Src/stm32l476xx_i2c_drivers.cyclo ./Drivers/Src/stm32l476xx_i2c_drivers.d ./Drivers/Src/stm32l476xx_i2c_drivers.o ./Drivers/Src/stm32l476xx_i2c_drivers.su ./Drivers/Src/stm32l476xx_rcc_driver.cyclo ./Drivers/Src/stm32l476xx_rcc_driver.d ./Drivers/Src/stm32l476xx_rcc_driver.o ./Drivers/Src/stm32l476xx_rcc_driver.su ./Drivers/Src/stm32l476xx_spi.cyclo ./Drivers/Src/stm32l476xx_spi.d ./Drivers/Src/stm32l476xx_spi.o ./Drivers/Src/stm32l476xx_spi.su ./Drivers/Src/stm32l476xx_uart_driver.cyclo ./Drivers/Src/stm32l476xx_uart_driver.d ./Drivers/Src/stm32l476xx_uart_driver.o ./Drivers/Src/stm32l476xx_uart_driver.su

.PHONY: clean-Drivers-2f-Src

