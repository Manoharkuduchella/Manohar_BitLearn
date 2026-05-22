/*
 * main_w25q32_spi.c
 *
 *  Created on: May 15, 2026
 *      Author: manohar kuduchella
 */

#include "stm32l476xx.h"
#include "w25q32f.h"

SPI_Handle_t SPI1Handle;

void SPI1_Init(void)
{
	SPI1Handle.pSPIx = SPI1;

	SPI1Handle.SPI_Config.DeviceMode = SPI_DEVICE_MODE_MASTER;
	SPI1Handle.SPI_Config.BusConfig  = SPI_BUS_CONFIG_FD;
	SPI1Handle.SPI_Config.SclkSpeed  = SPI_SCLK_SPEED_DIV16;
	SPI1Handle.SPI_Config.DFF        = SPI_DFF_8BITS;
	SPI1Handle.SPI_Config.CPOL       = SPI_CPOL_LOW;
	SPI1Handle.SPI_Config.CPHA       = SPI_CPHA_LOW;
	SPI1Handle.SPI_Config.SSM        = SPI_SSM_EN;

	SPI_Init(&SPI1Handle);
}

void SPI1_GPIOInits(void)
{
	GPIO_Handle_t SPIPins;

	SPIPins.pGPIOx = GPIOA;
	SPIPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	SPIPins.GPIO_PinConfig.GPIO_PinAltFunMode = 5;
	SPIPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	SPIPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	SPIPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

	/* SCK PA5 */
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_5;
	GPIO_Init(&SPIPins);

	/* MISO PA6 */
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_6;
	GPIO_Init(&SPIPins);

	/* MOSI PA7 */
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_7;
	GPIO_Init(&SPIPins);
}

void W25Q_CS_GPIOInit(void)
{
	GPIO_Handle_t csPin;

	csPin.pGPIOx = GPIOA;
	csPin.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_4;
	csPin.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	csPin.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	csPin.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	csPin.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_Init(&csPin);

	cs_high();
}

void W25Q_Test(void)
{
	uint32_t id;
	uint8_t txData[5] = {11, 22, 33, 44, 55};
	uint8_t rxData[5] = {0};

	w25q_reset();

	id = w25q_readID();
	(void)id;

	/*
	 * Put breakpoint here.
	 * Expected:
	 * id = 0xEF4016
	 */

	w25q_erase_sector(0);

	w25q_write(0x000000, txData, 5);

	w25q_read(0x000000, rxData, 5);

	/*
	 * Expected:
	 * rxData[0] = 11
	 * rxData[1] = 22
	 * rxData[2] = 33
	 * rxData[3] = 44
	 * rxData[4] = 55
	 */
}


uint32_t id;
uint8_t txData[5] = {11, 22, 33, 44, 55};
uint8_t rxData[5] = {0};

int main(void)
{
	GPIO_PeriClockControl(GPIOA, ENABLE);

	SPI1_GPIOInits();
	W25Q_CS_GPIOInit();

	SPI1_Init();

	//w25q_reset();

	id = w25q_readID();
	//W25Q_Test();

	while (1)
	{

	}
}
