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

#define FLASH_CMD_WRITE_ENABLE      0x06
#define Flash_CMD_WRITE_DISABLE     0x04
#define FLASH_CMD_READ_STATUS1      0x05
#define Flash_CMD_PAGE_PROGRAM      0x02
#define Flash_CMD_READ_DATA         0x03
#define Flash_CMD_FAST_READ         0x0B
#define Flash_CMD_SECTOR_ERASE      0x20
#define Flash_CMD_CHIP_ERASE        0xC7
#define FLASH_CMD_JEDEC_ID          0x9F



#define Flash_CS_PORT               GPIOA
#define Flash_CS_PIN                4


SPI_Handle_t SPI1Handle;

uint8_t st_before_erase;
uint8_t st_after_we;
uint8_t st_after_erase_cmd;
uint8_t spi_debug_ret;
uint32_t sr_debug;
uint8_t status_cmd_ret;
uint8_t status_data_ret;

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

 void SPI_FLASH_Init(void)
 {
     GPIO_Handle_t spiclk;
     GPIO_Handle_t spics;
     GPIO_Handle_t spiMosi;
     GPIO_Handle_t spiMiso;

     memset(&spiclk, 0, sizeof(spiclk));
     memset(&spics, 0, sizeof(spics));
     memset(&spiMosi, 0, sizeof(spiMosi));
     memset(&spiMiso, 0, sizeof(spiMiso));

     // SCK PA5
     spiclk.pGPIOx = GPIOA;
     spiclk.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
     spiclk.GPIO_PinConfig.GPIO_PinAltFunMode = 5;
     spiclk.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
     spiclk.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
     spiclk.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
     spiclk.GPIO_PinConfig.GPIO_PinNumber = 5;
     GPIO_Init(&spiclk);

     // MISO PA6
     spiMiso.pGPIOx = GPIOA;
     spiMiso.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
     spiMiso.GPIO_PinConfig.GPIO_PinAltFunMode = 5;
     spiMiso.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
     spiMiso.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
     spiMiso.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
     spiMiso.GPIO_PinConfig.GPIO_PinNumber = 6;
     GPIO_Init(&spiMiso);

     // MOSI PA7
     spiMosi.pGPIOx = GPIOA;
     spiMosi.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
     spiMosi.GPIO_PinConfig.GPIO_PinAltFunMode = 5;
     spiMosi.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
     spiMosi.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
     spiMosi.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
     spiMosi.GPIO_PinConfig.GPIO_PinNumber = 7;
     GPIO_Init(&spiMosi);

     // CS PA4
     spics.pGPIOx = GPIOA;
     spics.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
     spics.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
     spics.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
     spics.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
     spics.GPIO_PinConfig.GPIO_PinNumber = 4;
     GPIO_Init(&spics);

     FLASH_CS_DISABLE();
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

static void Flash_Select(void)
{
    SPI_ClearOVR(SPI1);
    FLASH_CS_ENABLE();
}

static void Flash_Unselect(void)
{
    while (SPI1->SR & SPI_BUSY_FLAG);
    FLASH_CS_DISABLE();
}


void Flash_ReadID(uint8_t *id)
{
    Flash_Select();

    SPI_Transfer(SPI1, FLASH_CMD_JEDEC_ID);

    id[0] = SPI_Transfer(SPI1, 0xFF);
    id[1] = SPI_Transfer(SPI1, 0xFF);
    id[2] = SPI_Transfer(SPI1, 0xFF);

    Flash_Unselect();
}


uint8_t Flash_ReadStatus1(void)
{
    Flash_Select();

    status_cmd_ret  = SPI_Transfer(SPI1, FLASH_CMD_READ_STATUS1);
    status_data_ret = SPI_Transfer(SPI1, 0xFF);

    Flash_Unselect();

    return status_data_ret;
}

uint8_t Flash_WriteEnable_Check(void)
{
    uint32_t timeout = 100000;
    uint8_t status;

    Flash_Select();

    SPI_Transfer(SPI1, FLASH_CMD_WRITE_ENABLE);

    Flash_Unselect();

    do
    {
        status = Flash_ReadStatus1();

        if (status & 0x02)
            return 0;       // WEL bit set, success

    } while (--timeout);

    return 1;               // timeout, WEL not set
}


void Flash_WriteEnable(void)
{
    FLASH_CS_ENABLE();

    SPI_Transfer(SPI1, FLASH_CMD_JEDEC_ID);

    FLASH_CS_DISABLE();

    /* Optional check: wait until WEL bit becomes 1 */
    while (!(Flash_ReadStatus1() & 0x02));
}


void Flash_WaitBusy(void)
{
    while (Flash_ReadStatus1() & 0x01);
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

void Flash_Read(uint32_t addr, uint8_t *buf, uint16_t len)
{
    FLASH_CS_ENABLE();

    SPI_Transfer(SPI1, FLASH_CMD_JEDEC_ID);

    SPI_Transfer(SPI1, (addr >> 16) & 0xFF);
    SPI_Transfer(SPI1, (addr >> 8)  & 0xFF);
    SPI_Transfer(SPI1, addr & 0xFF);

    for (uint16_t i = 0; i < len; i++)
    {
        buf[i] = SPI_Transfer(SPI1, 0xFF);
    }

    FLASH_CS_DISABLE();
}



void Flash_EraseSector(uint32_t addr)
{
    st_before_erase = Flash_ReadStatus1();

    Flash_WriteEnable();

    st_after_we = Flash_ReadStatus1();

    /*
     * If WEL bit is not set, erase will not start.
     */
    if (!(st_after_we & 0x02))
    {
        return;
    }

    FLASH_CS_ENABLE();

    spi_debug_ret = SPI_Transfer(SPI1, Flash_CMD_SECTOR_ERASE);
    sr_debug = SPI1->SR;

    SPI_Transfer(SPI1, (addr >> 16) & 0xFF);
    SPI_Transfer(SPI1, (addr >> 8)  & 0xFF);
    SPI_Transfer(SPI1, addr & 0xFF);

    FLASH_CS_DISABLE();

    st_after_erase_cmd = Flash_ReadStatus1();

    Flash_WaitBusy();
}




void Flash_PageWrite(uint32_t addr, uint8_t *buf, uint16_t len)
{
    if (len == 0)
        return;

    if (len > 256)
        len = 256;

    Flash_WriteEnable();

    FLASH_CS_ENABLE();

    SPI_Transfer(SPI1, FLASH_CMD_JEDEC_ID);

    SPI_Transfer(SPI1, (addr >> 16) & 0xFF);
    SPI_Transfer(SPI1, (addr >> 8)  & 0xFF);
    SPI_Transfer(SPI1, addr & 0xFF);

    for (uint16_t i = 0; i < len; i++)
    {
        SPI_Transfer(SPI1, buf[i]);
    }

    FLASH_CS_DISABLE();

    Flash_WaitBusy();
}

uint8_t Flash[3];
uint32_t flash_id;

uint8_t txData[5] = {'H', 'E', 'L', 'L', 'O'};
uint8_t rxData[10] = {0};

uint8_t st0;
uint8_t st1;
uint8_t we_ret;

uint8_t erase_result;
uint8_t write_result;


int main(void)
{
    GPIOA_PCLK_EN();

    SPI_Inits();
    SPI_FLASH_Init();

    FLASH_CS_DISABLE();
    delay_ms(10);

    Flash_ReadID(Flash);

    flash_id = ((uint32_t)Flash[0] << 16) |
               ((uint32_t)Flash[1] << 8)  |
               ((uint32_t)Flash[2]);

    /*
     * TEST WRITE ENABLE HERE
     */
    st0 = Flash_ReadStatus1();

    we_ret = Flash_WriteEnable_Check();

    st1 = Flash_ReadStatus1();

    /*
     * Put breakpoint here and check:
     *
     * st0    should be 0xC0
     * we_ret should be 0
     * st1    should be 0xC2
     */

    erase_result = Flash_EraseSector(0x001000);

    if (erase_result == 0)
    {
        write_result = Flash_PageWrite(0x001000, txData, 5);

        if (write_result == 0)
        {
            Flash_Read(0x001000, rxData, 5);
        }
    }

    while (1)
    {
    }
}
