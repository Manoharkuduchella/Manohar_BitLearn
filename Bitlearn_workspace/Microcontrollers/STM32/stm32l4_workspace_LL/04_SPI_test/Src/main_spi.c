#include "stm32l476xx.h"
#include "stm32l476xx_gpio_drivers.h"
#include "stm32l476xx_spi.h"
#include "w25qxx.h"
#include <string.h>
#include "delay.h"


GPIO_Handle_t GpioBtn;

SPI_Handle_t SPI1Handle;



void SPI1_inits(void);

void SPI_GPIO_Init(void) {
		GPIO_Handle_t spiPins;
	    GPIO_Handle_t csPin;

	    memset(&spiPins, 0, sizeof(spiPins));
	    memset(&csPin, 0, sizeof(csPin));

	    GPIO_PeriClockControl(GPIOA, ENABLE);

	    /*
	     * SPI1 pins:
	     * PA5 = SCK
	     * PA6 = MISO
	     * PA7 = MOSI
	     */
	    spiPins.pGPIOx = GPIOA;
	    spiPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	    spiPins.GPIO_PinConfig.GPIO_PinAltFunMode = 5;
	    spiPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	    spiPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	    spiPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	    spiPins.GPIO_PinConfig.GPIO_PinNumber = 5;
	    GPIO_Init(&spiPins);

	    spiPins.GPIO_PinConfig.GPIO_PinNumber = 6;
	    GPIO_Init(&spiPins);

	    spiPins.GPIO_PinConfig.GPIO_PinNumber = 7;
	    GPIO_Init(&spiPins);

	    /*
	     * Manual CS:
	     * PA4 = GPIO output
	     */
	    csPin.pGPIOx = GPIOA;
	    csPin.GPIO_PinConfig.GPIO_PinNumber = 4;
	    csPin.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUTPUT;
	    csPin.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	    csPin.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	    csPin.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	    GPIO_Init(&csPin);

	    GPIO_WriteToOutputPin(GPIOA, 4, 1);

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

uint8_t buf[7]="A";
uint32_t addr = 0, read_data = 0,id;
uint8_t read_buf[7];

uint8_t h = 'A';

int main(void)
{

	GPIO_PeriClockControl(GPIOA, ENABLE);

    SPI_GPIO_Init();

    //W25Q_Reset();

    W25Q_EraseSector(0);
    id = W25Q_ReadID();

	W25Q_Write(addr, &h, 1);

	delay_ms(100);

	W25Q_Read(addr, &read_buf[0], 1);


	while (1) {


	}
}

