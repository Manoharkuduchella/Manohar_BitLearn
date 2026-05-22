
#include "stm32l476xx.h"
#include "stm32l476xx_spi2.h"
#include "stm32l476xx_gpio_driver.h"

/*
 * PA5  -> SPI1_SCK
 * PA6  -> SPI1_MISO
 * PA7  -> SPI1_MOSI
 * PA4  -> CS
 */

#define W25Q_CMD_ENABLE_RESET      0x66
#define W25Q_CMD_RESET_DEVICE      0x99
#define W25Q_CMD_WRITE_ENABLE      0x06
#define W25Q_CMD_WRITE_DISABLE     0x04
#define W25Q_CMD_READ_STATUS1      0x05
#define W25Q_CMD_JEDEC_ID          0x9F
#define W25Q_CMD_READ_DATA         0x03
#define W25Q_CMD_PAGE_PROGRAM      0x02
#define W25Q_CMD_SECTOR_ERASE_4K   0x20

void delay_ms(uint32_t ms);



void delay_ms(uint32_t ms)
{
	for (uint32_t i = 0; i < ms; i++)
	{
		for (volatile uint32_t j = 0; j < 4000; j++)
		{
			__asm volatile ("nop");
		}
	}
}

/* ================= CS CONTROL ================= */
void cs_low(void)
{
	GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_NO_4, GPIO_PIN_RESET);
}

void cs_high(void)
{
	GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_NO_4, GPIO_PIN_SET);
}

/* ================= SPI WRAPPERS ================= */

void spi_write(uint8_t *data, uint32_t len)
{
	SPI_SendData(SPI1, data, len);
}

void spi_read(uint8_t *data, uint32_t len)
{
	SPI_ReceiveData(SPI1, data, len);
}

/* ================= W25Q BASIC COMMANDS ================= */

void w25q_reset(void)
{
	uint8_t cmd;

	cmd = 0x66;
	cs_low();
	spi_write(&cmd, 1);
	cs_high();

	cmd = 0x99;
	cs_low();
	spi_write(&cmd, 1);
	cs_high();

}

uint8_t Flash_ReadStatus(void)
{
	uint8_t cmd = W25Q_CMD_READ_STATUS1;
		uint8_t status;

		Flash_CS_LOW();

		SPI_SendData(SPI1, &cmd, 1);

		SPI_ReceiveData(SPI1, &status, 1);

		Flash_CS_HIGH();

		return status;
}

void Flash_WriteEnable(void)
{
	uint8_t cmd = W25Q_CMD_WRITE_ENABLE;

		Flash_CS_LOW();

		SPI_SendData(SPI1, &cmd, 1);

        Flash_CS_HIGH();
}

void write_disable(void)
{
	uint8_t cmd = W25Q_CMD_WRITE_DISABLE;

	cs_low();
	spi_write(&cmd, 1);
	cs_high();

}

void Flash_WaitBusy(void)
{
    while(Flash_ReadStatus() & 0x01);
}

void  w25q_readID(uint8_t *id) {
	uint8_t cmd = W25Q_CMD_JEDEC_ID;

	Flash_CS_LOW();

	SPI_SendData(SPI1, &cmd, 1);

	SPI_ReceiveData(SPI1, id, 3);

	Flash_CS_HIGH();
}

void Flash_Read(uint32_t addr,
                uint8_t *buffer,
                uint16_t len)
{
	uint8_t cmd[4];

		cmd[0] = W25Q_CMD_READ_DATA;
		cmd[1] = (addr >> 16) & 0xFF;
		cmd[2] = (addr >> 8) & 0xFF;
		cmd[3] = addr & 0xFF;

		Flash_CS_LOW();

		SPI_SendData(SPI1, cmd, 4);

		SPI_ReceiveData(SPI1, buffer, len);

		Flash_CS_HIGH();
}


void Flash_Write(uint32_t addr,
                 uint8_t *data,
                 uint16_t len)
{

	    while(len > 0)
	    {
	        uint16_t chunk;

	        chunk = 256 - (addr % 256);

	        if(chunk > len)
	            chunk = len;

	        Flash_PageWrite(addr, data, chunk);

	        addr += chunk;
	        data  += chunk;
	        len  -= chunk;
	    }
}


void Flash_EraseSector(uint32_t addr) {
	Flash_WriteEnable();

	uint8_t cmd[4];

	cmd[0] = W25Q_CMD_SECTOR_ERASE_4K;
	cmd[1] = (addr >> 16) & 0xFF;
	cmd[2] = (addr >> 8) & 0xFF;
	cmd[3] = addr & 0xFF;

	Flash_CS_LOW();

	SPI_SendData(SPI1, cmd, 4);

	Flash_CS_HIGH();

	Flash_WaitBusy();
}

void Flash_PageWrite(uint32_t addr, uint8_t *buf, uint16_t len) {
	Flash_WriteEnable();

	uint8_t cmd[4];

	cmd[0] = W25Q_CMD_PAGE_PROGRAM;
	cmd[1] = (addr >> 16) & 0xFF;
	cmd[2] = (addr >> 8) & 0xFF;
	cmd[3] = addr & 0xFF;

	Flash_CS_LOW();

	SPI_SendData(SPI1, cmd, 4);

	SPI_SendData(SPI1, buf, len);

	Flash_CS_HIGH();

	Flash_WaitBusy();
}


