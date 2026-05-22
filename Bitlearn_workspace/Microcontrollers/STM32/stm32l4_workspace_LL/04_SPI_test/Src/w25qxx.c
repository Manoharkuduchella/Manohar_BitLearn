/*
 * w25qxx.c
 **/

#include "w25qxx.h"
#include "stm32l476xx_gpio_drivers.h"
#include "stm32l476xx_spi.h"
#include "delay.h"

/* -------- CS CONTROL -------- */
#define CS_LOW()   GPIO_WriteToOutputPin(GPIOA, 4, 0)
#define CS_HIGH()  GPIO_WriteToOutputPin(GPIOA, 4, 1)

/* -------- INIT -------- */
void W25Q_Init(void) {
	CS_HIGH();
}

void W25Q_Reset(void)
{
	uint8_t rst_cmd[2];
	rst_cmd[0] = 0x66;//enabling reset
	rst_cmd[1] = 0x99;//reset

	CS_LOW();
	SPI_Transfer(SPI1, rst_cmd[0]);
	CS_HIGH();

	delay_us(10);

	CS_LOW();
	SPI_Transfer(SPI1, rst_cmd[1]);
	CS_HIGH();

}


/* -------- WRITE ENABLE -------- */
void W25Q_WriteEnable(void) {
	uint8_t cmd = W25Q_CMD_WRITE_ENABLE;

	CS_LOW();
	SPI_SendData(SPI1, &cmd, 1);

	while(SPI_GetFlagStatus(SPI1, SPI_BUSY_FLAG));
	CS_HIGH();
	//delay_ms(5);
}

/********* WRITE DISABLE************/
void W25Q_WriteDisable(void)
{
	uint8_t cmd = 0x04;

	CS_LOW();
	SPI_SendData(SPI1, &cmd, 1);
	while(SPI_GetFlagStatus(SPI1, SPI_BUSY_FLAG));
	CS_HIGH();
	//delay_ms(5);
}

/* -------- READ STATUS -------- */
uint8_t W25Q_ReadStatus(void) {
	uint8_t cmd = W25Q_CMD_READ_STATUS;
	uint8_t status;

	CS_LOW();
	SPI_SendData(SPI1, &cmd, 1);
	SPI_ReceiveData(SPI1, &status, 1);

	while(SPI_GetFlagStatus(SPI1, SPI_BUSY_FLAG));

	CS_HIGH();

	return status;
}

/* -------- WAIT BUSY -------- */
void W25Q_WaitBusy(void) {
	while (W25Q_ReadStatus() & 0x01)
		;
}

/* -------- READ ID -------- */
uint32_t W25Q_ReadID(void) {
	uint8_t cmd = W25Q_CMD_READ_ID;
	uint8_t id[3]={0};

	CS_LOW();
	SPI_SendData(SPI1, &cmd, 1);
	SPI_ReceiveData(SPI1, id, 3);
	while(SPI_GetFlagStatus(SPI1, SPI_BUSY_FLAG));
	CS_HIGH();

	return ((id[0]<<16)|(id[1]<<8)|id[2]);
}

/* -------- READ DATA -------- */
void W25Q_Read(uint32_t Addr, uint8_t *rData, uint8_t size)
{
	uint8_t r_cmd[4]={0};

	r_cmd[0] = 0x03;
	r_cmd[1] =(Addr>>16)&0xFF;
	r_cmd[2] = (Addr>>8)&0xFF;
	r_cmd[3] = (Addr)&0xFF;

	CS_LOW();
	SPI_SendData(SPI1, r_cmd, 4);
	SPI_ReceiveData(SPI1, rData, size);
	while(SPI_GetFlagStatus(SPI1, SPI_BUSY_FLAG));
	CS_HIGH();
}

volatile uint8_t status_after_wren;
volatile uint8_t status_after_write;

/* -------- PAGE WRITE -------- */
void W25Q_Write(uint32_t Addr, uint8_t *data, uint8_t size)
{
    uint8_t wr_cmd[4];

    wr_cmd[0] = 0x02; // Page Program
    wr_cmd[1] = (Addr >> 16) & 0xFF;
    wr_cmd[2] = (Addr >> 8) & 0xFF;
    wr_cmd[3] = Addr & 0xFF;

    W25Q_WriteEnable();

    CS_LOW();

    SPI_SendData(SPI1, wr_cmd, 4);

    SPI_SendData(SPI1, data, size);

    while(SPI_GetFlagStatus(SPI1, SPI_BUSY_FLAG));

    CS_HIGH();

    W25Q_WaitBusy();
}



/* -------- SECTOR ERASE -------- */
void W25Q_EraseSector(uint32_t sector)
{
    uint8_t cmd[4];
    uint32_t addr = sector*16*256;

    W25Q_WriteEnable();

    cmd[0] = 0x20;
    cmd[1] = (addr >> 16) & 0xFF;
    cmd[2] = (addr >> 8) & 0xFF;
    cmd[3] = addr & 0xFF;


	CS_LOW();
	SPI_SendData(SPI1, cmd, 4);
	while(SPI_GetFlagStatus(SPI1, SPI_BUSY_FLAG));
	CS_HIGH();

	W25Q_WaitBusy();

}


//void W25Q_Init(void)
//{
//    CS_HIGH();
//    delay_ms(1);
//}
//
//void W25Q_Reset(void)
//{
//    CS_LOW();
//    SPI_Transfer(SPI1, 0x66);
//    CS_HIGH();
//
//    delay_us(10);
//
//    CS_LOW();
//    SPI_Transfer(SPI1, 0x99);
//    CS_HIGH();
//
//    delay_ms(1);
//}
//
//uint32_t W25Q_ReadID(void)
//{
//    uint8_t id0, id1, id2;
//
//    CS_LOW();
//
//    SPI_Transfer(SPI1, 0x9F);
//    id0 = SPI_Transfer(SPI1, 0xFF);
//    id1 = SPI_Transfer(SPI1, 0xFF);
//    id2 = SPI_Transfer(SPI1, 0xFF);
//
//    CS_HIGH();
//
//    return (((uint32_t)id0 << 16) | ((uint32_t)id1 << 8) | id2);
//}
//
//uint8_t W25Q_ReadStatus(void)
//{
//    uint8_t status;
//
//    CS_LOW();
//
//    SPI_Transfer(SPI1, 0x05);
//    status = SPI_Transfer(SPI1, 0xFF);
//
//    CS_HIGH();
//
//    return status;
//}
//
//void W25Q_WriteEnable(void)
//{
//    CS_LOW();
//    SPI_Transfer(SPI1, 0x06);
//    CS_HIGH();
//
//    delay_us(10);
//}
//
//void W25Q_WriteDisable(void)
//{
//    CS_LOW();
//    SPI_Transfer(SPI1, 0x04);
//    CS_HIGH();
//
//    delay_us(10);
//}
//
//void W25Q_WaitBusy(void)
//{
//    while (W25Q_ReadStatus() & 0x01);
//}





