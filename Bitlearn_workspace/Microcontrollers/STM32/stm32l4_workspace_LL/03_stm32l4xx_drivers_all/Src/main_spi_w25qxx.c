
#include "stm32l476xx.h"
#include <string.h>
#include "w25q32f.h"
/*
 * PA5 -> SPI1_SCK
 * PA6 -> SPI1_MISO
 * PA7 -> SPI1_MOSI
 * PA4 -> SPI1_CS
 *
 * Alternate functionality: AF5
 * */

void delay_ms(uint32_t ms);

SPI_Handle_t SPI1handle;

uint8_t tx[4] = {0x11, 0x22, 0x33, 0x44};
uint8_t rx[4];
uint32_t ft = 34.56;
uint32_t r_ft;
uint32_t flash_id;


void SPI1_Inits(void)
{
	SPI1handle.pSPIx = SPI1;
	SPI1handle.SPIConfig.SPI_BusConfig = SPI_BUS_CONFIG_FD;
	SPI1handle.SPIConfig.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
	SPI1handle.SPIConfig.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV32;
	SPI1handle.SPIConfig.SPI_DFF = SPI_DFF_8BITS;
	SPI1handle.SPIConfig.SPI_CPOL = SPI_CPOL_LOW;
	SPI1handle.SPIConfig.SPI_CPHA = SPI_CPHA_LOW;
	SPI1handle.SPIConfig.SPI_SSM = SPI_SSM_EN;

	SPI_Init(&SPI1handle);
}



void SPI_GPIOInits(void)
{
	GPIO_Handle_t SPIPins;
	SPIPins.pGPIOx = GPIOA;
	SPIPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	SPIPins.GPIO_PinConfig.GPIO_PinAltFunMode = 5;
	SPIPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	SPIPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	SPIPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

	//sclk
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_5;
	GPIO_Init(&SPIPins);

	//mosi
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_7;
	GPIO_Init(&SPIPins);

	//miso
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_6;
	GPIO_Init(&SPIPins);

	//NSS
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_4;
	GPIO_Init(&SPIPins);

}


int main()
{

	//char user_data[] = "Hello world";

	SPI_GPIOInits();

	SPI1_Inits();

	w25q_reset();

	flash_id = w25q_readID();

	w25q_erase_sector(0);

	w25q_write(0x000000, (uint8_t*)&ft, 4);


	//SPI_SendData(SPI1, (uint8_t*)user_data, strlen(user_data));
	delay_ms(100);
	w25q_read(0x000000, (uint8_t*)&r_ft, 4);

	//enable the spi1 peripheral
	SPI_PeripheralControl(SPI1, DISABLE);

	while(1);

	return 0;
}


