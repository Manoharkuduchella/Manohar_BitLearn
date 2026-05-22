#include "stm32l476xx.h"
#include "stm32l476xx_gpio_driver.h"
#include "stm32l476xx_spi.h"
#include <string.h>

/*
 * SPI1 Pins
 * PA4  -> NSS
 * PA5  -> SCLK
 * PA6  -> MISO
 * PA7  -> MOSI
 */

#define Flash_CMD_WRITE_ENABLE      0x06
#define Flash_CMD_WRITE_DISABLE     0x04
#define Flash_CMD_READ_STATUS1      0x05
#define Flash_CMD_PAGE_PROGRAM      0x02
#define Flash_CMD_READ_DATA         0x03
#define Flash_CMD_FAST_READ         0x0B
#define Flash_CMD_SECTOR_ERASE      0x20
#define Flash_CMD_CHIP_ERASE        0xC7
#define Flash_CMD_JEDEC_ID          0x9F



#define Flash_CS_PORT               GPIOA
#define Flash_CS_PIN                4


SPI_Handle_t SPI1Handle;
#define FLASH_CS_ENABLE() \
        GPIO_WriteToOutputPin(Flash_CS_PORT, Flash_CS_PIN, GPIO_PIN_RESET)

#define FLASH_CS_DISABLE() \
        GPIO_WriteToOutputPin(Flash_CS_PORT, Flash_CS_PIN, GPIO_PIN_SET)
 unsigned char buffer[50];
 void Flash_PageWrite(uint32_t addr, uint8_t *buf, uint16_t len);

 void delay_loop(volatile uint32_t count)
 {
     while (count--)
     {
         __asm volatile ("nop");
     }
 }

 void delay_us(uint32_t us)
 {
     while (us--)
     {
         /*
          * Approximate delay for default 4 MHz clock.
          * Increase this value if delay is too short.
          */
         delay_loop(4);
     }
 }

 void delay_ms(uint32_t ms)
 {
     while (ms--)
     {
         delay_us(1000);
     }
 }



 void SPI_Inits(void)
 {
 	SPI1Handle.pSPIx = SPI1;

 	SPI1Handle.SPI_Config.DeviceMode = SPI_DEVICE_MODE_MASTER;
 	SPI1Handle.SPI_Config.BusConfig  = SPI_BUS_CONFIG_FD;
 	SPI1Handle.SPI_Config.SclkSpeed  = SPI_SCLK_SPEED_DIV32;
 	SPI1Handle.SPI_Config.DFF        = SPI_DFF_8BITS;
 	SPI1Handle.SPI_Config.CPOL       = SPI_CPOL_LOW;
 	SPI1Handle.SPI_Config.CPHA       = SPI_CPHA_LOW;
 	SPI1Handle.SPI_Config.SSM        = SPI_SSM_EN;

 	SPI_Init(&SPI1Handle);
 }
/**
void SPI1_GPIOInits(void)
{
	GPIOA_CLK_EN();
	GPIOB_CLK_EN();
    GPIO_Handle_t SPIPins;

    SPIPins.pGPIOx = GPIOA;

    SPIPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
    SPIPins.GPIO_PinConfig.GPIO_PinAltFunMode = 5;
    SPIPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    SPIPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
    SPIPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

    //SCLK
    SPIPins.GPIO_PinConfig.GPIO_PinNumber = 5;
    GPIO_Init(&SPIPins);

    //MISO
    SPIPins.GPIO_PinConfig.GPIO_PinNumber = 6;
    GPIO_Init(&SPIPins);

    //MOSI
    SPIPins.GPIO_PinConfig.GPIO_PinNumber = 7;
    GPIO_Init(&SPIPins);

    //CS -> GPIO Output
    SPIPins.pGPIOx = GPIOB;

    SPIPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUTPUT;
    SPIPins.GPIO_PinConfig.GPIO_PinNumber = 6;

    GPIO_Init(&SPIPins);

    GPIO_WriteToOutputPin(GPIOB,6,GPIO_PIN_SET);


    GPIO_Handle_t GPIO_LED;

    GPIO_LED.pGPIOx = GPIOB;

    GPIO_LED.GPIO_PinConfig.GPIO_PinNumber = 5;
    GPIO_LED.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUTPUT;
    GPIO_LED.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
    GPIO_LED.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    GPIO_LED.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

    GPIO_Init(&GPIO_LED);
    GPIO_WriteToOutputPin(GPIOB,6,GPIO_PIN_SET);
}***/

void SPI_FLASH_Init(void) {
	GPIO_Handle_t spiclk;
	GPIO_Handle_t spics;
	GPIO_Handle_t spiMosi;
	GPIO_Handle_t spiMiso;

	memset(&spiclk, 0, sizeof(spiclk));

	// SCK
	spiclk.pGPIOx = GPIOA;
	spiclk.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	spiclk.GPIO_PinConfig.GPIO_PinAltFunMode = 5; // AF5 (SPI1)
	spiclk.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	spiclk.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	spiclk.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	spiclk.GPIO_PinConfig.GPIO_PinNumber = 5;

	GPIO_Init(&spiclk);

	// MISO
	spiMiso.pGPIOx = GPIOA;
	spiMiso.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	spiMiso.GPIO_PinConfig.GPIO_PinNumber = 6;
	spiMiso.GPIO_PinConfig.GPIO_PinAltFunMode = 5;
	spiMiso.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	spiMiso.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	spiMiso.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_Init(&spiMiso);

	// MOSI
	spiMosi.pGPIOx = GPIOA;
	spiMosi.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	spiMosi.GPIO_PinConfig.GPIO_PinNumber = 7;
	spiMosi.GPIO_PinConfig.GPIO_PinAltFunMode = 5;
	spiMosi.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	spiMosi.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	spiMosi.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_Init(&spiMosi);

	// CS (manual)
	spics.pGPIOx = GPIOA;
	spics.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	spics.GPIO_PinConfig.GPIO_PinNumber = 4;
	spics.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	spics.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	spics.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	GPIO_Init(&spics);

	GPIO_WriteToOutputPin(GPIOA, 4, 1); // CS HIGH
}
void Flash_CS_LOW(void) {
	GPIO_WriteToOutputPin(Flash_CS_PORT, Flash_CS_PIN, 0);
}

void Flash_CS_HIGH(void) {
	GPIO_WriteToOutputPin(Flash_CS_PORT, Flash_CS_PIN, 1);
}

void Flash_Init(void) {
	Flash_CS_HIGH();
}


void SPI_ClearRX(SPI_RegDef_t *pSPIx)
{
    volatile uint8_t dummy;

    while (pSPIx->SR & SPI_RXNE_FLAG)
    {
        dummy = *((volatile uint8_t *)&pSPIx->DR);
        (void)dummy;
    }

    if (pSPIx->SR & (1 << 6)) // OVR
    {
        dummy = *((volatile uint8_t *)&pSPIx->DR);
        dummy = pSPIx->SR;
        (void)dummy;
    }
}


//void Flash_ReadID(uint8_t *id) {
//
//	uint8_t cmd = Flash_CMD_JEDEC_ID;
//
//	Flash_CS_LOW();
//
//	SPI_SendData(SPI1, &cmd, 1);
//
//	SPI_ReceiveData(SPI1, id, 3);
//
//	Flash_CS_HIGH();
//}

void Flash_ReadID(uint8_t *id)
{
    volatile uint8_t dummy;

    Flash_CS_LOW();

    // Send JEDEC ID command
    SPI_Transfer(SPI1, Flash_CMD_JEDEC_ID);

    // Flush any stale RX byte if present
    while (SPI1->SR & SPI_RXNE_FLAG)
    {
        dummy = *((volatile uint8_t *)&SPI1->DR);
        (void)dummy;
    }

    // Now read actual 3 ID bytes
    id[0] = SPI_Transfer(SPI1, 0xFF);
    id[1] = SPI_Transfer(SPI1, 0xFF);
    id[2] = SPI_Transfer(SPI1, 0xFF);

    Flash_CS_HIGH();
}



//void Flash_WriteEnable(void)
//{
//	uint8_t cmd = Flash_CMD_WRITE_ENABLE;
//
//	Flash_CS_LOW();
//
//		SPI_SendData(SPI1, &cmd, 1);
//
//        Flash_CS_HIGH();
//}
void Flash_WriteEnable(void)
{
    SPI_ClearRX(SPI1);

    Flash_CS_LOW();

    SPI_Transfer(SPI1, 0x06);   // Write Enable

    Flash_CS_HIGH();

    delay_ms(1);
}


//uint8_t Flash_ReadStatus(void)
//{
//	uint8_t cmd = Flash_CMD_READ_STATUS1;
//		uint8_t status;
//
//		Flash_CS_LOW();
//
//		SPI_SendData(SPI1, &cmd, 1);
//
//		SPI_ReceiveData(SPI1, &status, 1);
//
//		Flash_CS_HIGH();
//
//		return status;
//}
uint8_t Flash_ReadStatus(void)
{
    uint8_t status;

    SPI_ClearRX(SPI1);

    Flash_CS_LOW();

    SPI_Transfer(SPI1, 0x05);
    status = SPI_Transfer(SPI1, 0xFF);

    Flash_CS_HIGH();

    return status;
}
void Flash_WaitBusy(void)
{
    while(Flash_ReadStatus() & 0x01);
}

//void Flash_Write(uint32_t addr,
//                 uint8_t *data,
//                 uint16_t len)
//{
//
//	    while(len > 0)
//	    {
//	        uint16_t chunk;
//
//	        chunk = 256 - (addr % 256);
//
//	        if(chunk > len)
//	            chunk = len;
//
//	        Flash_PageWrite(addr, data, chunk);
//
//	        addr += chunk;
//	        data  += chunk;
//	        len  -= chunk;
//	    }
//}

void Flash_Write(uint32_t addr, uint8_t *data, uint16_t len)
{
    Flash_WriteEnable();

    Flash_CS_LOW();

    SPI_Transfer(SPI1, 0x02);                  // Page Program
    SPI_Transfer(SPI1, (addr >> 16) & 0xFF);
    SPI_Transfer(SPI1, (addr >> 8) & 0xFF);
    SPI_Transfer(SPI1, addr & 0xFF);

    for(uint16_t i = 0; i < len; i++)
    {
        SPI_Transfer(SPI1, data[i]);
    }

    Flash_CS_HIGH();

    Flash_WaitBusy();
}

//void Flash_Read(uint32_t addr,
//                uint8_t *buffer,
//                uint16_t len)
//{
//	uint8_t cmd[4];
//
//		cmd[0] = Flash_CMD_READ_DATA;
//		cmd[1] = (addr >> 16) & 0xFF;
//		cmd[2] = (addr >> 8) & 0xFF;
//		cmd[3] = addr & 0xFF;
//
//		Flash_CS_LOW();
//
//		SPI_SendData(SPI1, cmd, 4);
//
//		SPI_ReceiveData(SPI1, buffer, len);
//
//		Flash_CS_HIGH();
//}

void Flash_Read(uint32_t addr, uint8_t *buffer, uint16_t len)
{
    Flash_CS_LOW();

    SPI_Transfer(SPI1, 0x03);                  // Read Data
    SPI_Transfer(SPI1, (addr >> 16) & 0xFF);
    SPI_Transfer(SPI1, (addr >> 8) & 0xFF);
    SPI_Transfer(SPI1, addr & 0xFF);

    for(uint16_t i = 0; i < len; i++)
    {
        buffer[i] = SPI_Transfer(SPI1, 0xFF);
    }

    Flash_CS_HIGH();
}

//void Flash_EraseSector(uint32_t addr) {
//	Flash_WriteEnable();
//
//	uint8_t cmd[4];
//
//	cmd[0] = Flash_CMD_SECTOR_ERASE;
//	cmd[1] = (addr >> 16) & 0xFF;
//	cmd[2] = (addr >> 8) & 0xFF;
//	cmd[3] = addr & 0xFF;
//
//	Flash_CS_LOW();
//
//	SPI_SendData(SPI1, cmd, 4);
//
//	Flash_CS_HIGH();
//
//	Flash_WaitBusy();
//}
void Flash_EraseSector(uint32_t addr)
{
    Flash_WriteEnable();

    Flash_CS_LOW();

    SPI_Transfer(SPI1, 0x20);                  // Sector Erase 4KB
    SPI_Transfer(SPI1, (addr >> 16) & 0xFF);
    SPI_Transfer(SPI1, (addr >> 8) & 0xFF);
    SPI_Transfer(SPI1, addr & 0xFF);

    Flash_CS_HIGH();

    Flash_WaitBusy();
}

void Flash_Reset(void)
{
    SPI_ClearRX(SPI1);

    Flash_CS_LOW();
    SPI_Transfer(SPI1, 0x66);   // Enable Reset
    Flash_CS_HIGH();

    delay_ms(1);

    Flash_CS_LOW();
    SPI_Transfer(SPI1, 0x99);   // Reset
    Flash_CS_HIGH();

    delay_ms(10);
}


void Flash_PageWrite(uint32_t addr, uint8_t *buf, uint16_t len) {
	Flash_WriteEnable();

	uint8_t cmd[4];

	cmd[0] = Flash_CMD_PAGE_PROGRAM;
	cmd[1] = (addr >> 16) & 0xFF;
	cmd[2] = (addr >> 8) & 0xFF;
	cmd[3] = addr & 0xFF;

	Flash_CS_LOW();

	SPI_SendData(SPI1, cmd, 4);

	SPI_SendData(SPI1, buf, len);

	Flash_CS_HIGH();

	Flash_WaitBusy();
}

uint8_t Flash[3];
uint32_t flash_id;
uint8_t txData[] = "HELLO";
uint8_t rxData[10] = {0};
uint8_t st1, st2, st3;
int main(void)
{

    GPIOA_PCLK_EN();

    SPI_PeriClockControl(SPI1, ENABLE);

    SPI_Inits();
    SPI_FLASH_Init();

    Flash_Reset();

    Flash_ReadID(Flash);

    flash_id = ((uint32_t)Flash[0] << 16) |
               ((uint32_t)Flash[1] << 8)  |
               ((uint32_t)Flash[2]);




    st1 = Flash_ReadStatus();

    Flash_WriteEnable();
    st2 = Flash_ReadStatus();

    Flash_EraseSector(0x000000);
    st3 = Flash_ReadStatus();

//    Flash_EraseSector(0x001000);
//    Flash_Write(0x001000, txData, 5);
//
//    Flash_Read(0x001000, rxData, 5);

    while(1)
    {

    }
}
