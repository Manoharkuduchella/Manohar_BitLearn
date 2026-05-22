/*
 * spi_loop.c
 *
 *  Created on: May 13, 2026
 *      Author: manohar kuduchella
 */
#include "stm32l476xx.h"
#include "stm32l476xx_gpio_driver.h"
#include "stm32l476xx_spi_driver.h"

SPI_Handle_t SPI1Handle;

uint8_t tx_byte = 0xA;
uint8_t rx_byte = 0x00;

void SPI_Inits(void)
{
	SPI1Handle.pSPIx = SPI1;

	SPI1Handle.SPIConfig.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
	SPI1Handle.SPIConfig.SPI_BusConfig  = SPI_BUS_CONFIG_FD;
	SPI1Handle.SPIConfig.SPI_SclkSpeed  = SPI_SCLK_SPEED_DIV32;
	SPI1Handle.SPIConfig.SPI_DFF        = SPI_DFF_8BITS;
	SPI1Handle.SPIConfig.SPI_CPOL       = SPI_CPOL_LOW;
	SPI1Handle.SPIConfig.SPI_CPHA       = SPI_CPHA_LOW;
	SPI1Handle.SPIConfig.SPI_SSM        = SPI_SSM_EN;

	SPI_Init(&SPI1Handle);
}

void SPI1_GPIOInits_Loopback(void)
{
	GPIO_Handle_t SPIPins;

	SPIPins.pGPIOx = GPIOA;

	SPIPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	SPIPins.GPIO_PinConfig.GPIO_PinAltFunMode = 5;
	SPIPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	SPIPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	SPIPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

	// PA5 SCK
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = 5;
	GPIO_Init(&SPIPins);

	// PA6 MISO
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = 6;
	GPIO_Init(&SPIPins);

	// PA7 MOSI
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = 7;
	GPIO_Init(&SPIPins);
}

int main(void)
{
	SPI1_GPIOInits_Loopback();

	SPI_Inits();

	rx_byte = SPI_Transfer(SPI1, tx_byte);

	while(1)
	{

	}
}
