/*
 * main_i2c.c
 *
 *  Created on: May 15, 2026
 *      Author: manohar kuduchella
 */

//**************************************************************************************

#include <stdint.h>
#include "stm32l476xx.h"
#include "stm32l476xx_gpio_driver.h"
#include "stm32l476xx_i2c_driver.h"
#include "bme280.h"

I2C_Handle_t I2C2Handle;

float temperature;
float pressure;
float humidity;

uint8_t bme_id;
uint8_t bme_status;

void delay(void)
{
    for (volatile uint32_t i = 0; i < 500000; i++);
}

void I2C2_GPIOInits(void)
{
    GPIO_Handle_t I2CPins;

    I2CPins.pGPIOx = GPIOB;

    I2CPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
    I2CPins.GPIO_PinConfig.GPIO_PinAltFunMode = 4;
    I2CPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_OD;
    I2CPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
    I2CPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

    /*
     * PB10 = I2C2_SCL
     */
    I2CPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_10;
    GPIO_Init(&I2CPins);

    /*
     * PB11 = I2C2_SDA
     */
    I2CPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_11;
    GPIO_Init(&I2CPins);
}

void I2C2_Inits(void)
{
    I2C2Handle.pI2Cx = I2C2;

    I2C2Handle.I2C_Config.I2C_Timing = 0x00100D14;
    I2C2Handle.I2C_Config.I2C_OwnAddress1 = 0x00;
    I2C2Handle.I2C_Config.I2C_AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    I2C2Handle.I2C_Config.I2C_AnalogFilter = I2C_ANALOGFILTER_ENABLE;
    I2C2Handle.I2C_Config.I2C_DigitalFilter = 0;
    I2C2Handle.I2C_Config.I2C_StretchMode = I2C_STRETCH_ENABLE;

    I2C_Init(&I2C2Handle);
}

volatile uint8_t measure_status;

int main(void)
{
    I2C2_GPIOInits();
    I2C2_Inits();

    /*
     * First check chip ID.
     * Expected: 0x60
     */
    bme_id = BME280_ReadID(&I2C2Handle);

    if (bme_id != 0x60)
    {
        while (1);
    }

    bme_status = BME280_Config(&I2C2Handle,OSRS_2,OSRS_16,OSRS_1,MODE_NORMAL,T_SB_0p5,IIR_16);


    if (bme_status != 0)
    {
        while (1);
    }

    while (1)
    {
    	measure_status = BME280_Measure(&I2C2Handle,
                       &temperature,
                       &pressure,
                       &humidity);

        __asm volatile("nop");

        delay();
    }
}

