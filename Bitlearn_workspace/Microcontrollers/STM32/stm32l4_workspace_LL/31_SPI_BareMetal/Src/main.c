
#include "stm32l476xx.h"
#include "stm32l476xx_gpio_drivers.h"
#include "stm32l476xx_spi.h"
#include <string.h>


void SPI1_inits(void);
void SPI_GPIO_Init(void);

SPI_Handle_t SPI1Handle;

int main()
{
	SPI_GPIO_Init();



	while (1) {

	}
}


void SPI_GPIO_Init(void) {
	GPIO_Handle_t spiPins;

	memset(&spiPins, 0, sizeof(spiPins));

	spiPins.pGPIOx = GPIOA;

	spiPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	spiPins.GPIO_PinConfig.GPIO_PinAltFunMode = 5; // AF5 (SPI1)
	spiPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	spiPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	spiPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	// SCK
	spiPins.GPIO_PinConfig.GPIO_PinNumber = 5;
	GPIO_Init(&spiPins);

	// MISO
	spiPins.GPIO_PinConfig.GPIO_PinNumber = 6;
	GPIO_Init(&spiPins);

	// MOSI
	spiPins.GPIO_PinConfig.GPIO_PinNumber = 7;
	GPIO_Init(&spiPins);

	// CS (manual)
	spiPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUTPUT;
	spiPins.GPIO_PinConfig.GPIO_PinNumber = 4;
	GPIO_Init(&spiPins);

	GPIO_WriteToOutputPin(GPIOA, 4, 1); // CS HIGH
	SPI1_inits();
}


void SPI1_inits(void)
{
SPI1Handle.pSPIx = SPI1;

	SPI1Handle.SPI_Config.DeviceMode = SPI_DEVICE_MODE_MASTER;
	SPI1Handle.SPI_Config.BusConfig = SPI_BUS_CONFIG_FD;
	SPI1Handle.SPI_Config.SclkSpeed = SPI_SCLK_SPEED_DIV16;
	SPI1Handle.SPI_Config.DFF = SPI_DFF_8BITS;
	SPI1Handle.SPI_Config.CPOL = SPI_CPOL_LOW;
	SPI1Handle.SPI_Config.CPHA = SPI_CPHA_LOW;
	SPI1Handle.SPI_Config.SSM = SPI_SSM_EN;

	SPI_Init(&SPI1Handle);
}
