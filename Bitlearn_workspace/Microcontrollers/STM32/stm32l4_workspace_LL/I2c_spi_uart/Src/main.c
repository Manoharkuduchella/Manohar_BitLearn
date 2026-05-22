#include "stm32l476xx.h"
#include "stm32l476xx_gpio_drivers.h"
#include "stm32l476xx_usart_driver.h"
#include "stm32l476xx_i2c_drivers.h"
#include "stm32l476xx_spi.h"
#include "opt3001.h"
#include "w25qxx.h"
#include <string.h>
#include <inttypes.h>


#define FLASH_START_ADDR   0x000000
#define FLASH_SECTOR_SIZE  4096

USART_Handle_t USARTHandle;
GPIO_Handle_t GpioBtn;

I2C_Handle_t I2C2Handle;
SPI_Handle_t SPI1Handle;


void  I2C2_inits(void);
void SPI1_inits(void);

int _write(int file, char *ptr, int len) {
	USART_SendData(USART2, (uint8_t*) ptr, len);

	return len;
}




typedef struct
{
    uint32_t lux;
} opt3001_log_t;

volatile opt3001_log_t sensor_log;

uint32_t write_addr = FLASH_START_ADDR;

volatile uint8_t read_request = 0;

uint32_t flash_id;

uint32_t log_count = 0;





void GPIO_Inits(void)
{
	GpioBtn.pGPIOx = GPIOC;
	 GpioBtn.GPIO_PinConfig.GPIO_PinNumber =13;
	 GpioBtn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_FT;
	 GpioBtn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	 GpioBtn.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	 GpioBtn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
		GPIO_PeriClockControl(GPIOC,ENABLE);
		GPIO_Init(&GpioBtn);

		GPIO_IRQPriorityConfig(40,15);
		GPIO_IRQConfig(40,15,ENABLE);
}

void UART_GPIO_Init()
{
    GPIO_Handle_t UARTPins;

    UARTPins.pGPIOx = GPIOA;

    UARTPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
    UARTPins.GPIO_PinConfig.GPIO_PinAltFunMode = 7;
    UARTPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    UARTPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
    UARTPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

    /************ USART1_TX -> PA9 ************/
    UARTPins.GPIO_PinConfig.GPIO_PinNumber = 2;
    GPIO_Init(&UARTPins);

    /************ USART1_RX -> PA10 ************/
    UARTPins.GPIO_PinConfig.GPIO_PinNumber = 3;
    GPIO_Init(&UARTPins);
}

void UART_Init()
{
    USARTHandle.pUSARTx = USART2;

    USARTHandle.USART_Config.USART_Mode = USART_MODE_TXRX;

    USARTHandle.USART_Config.USART_Baud = USART_STD_BAUD_9600;

    USARTHandle.USART_Config.USART_NoOfStopBits = 1;

    USARTHandle.USART_Config.USART_WordLength = USART_WORDLEN_8BITS;

    USARTHandle.USART_Config.USART_ParityControl = USART_PARITY_DISABLE;

    USARTHandle.USART_Config.USART_HWFlowControl = 0;

    USART_Init(&USARTHandle);
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

		/* PB10 -> SCL */
		I2CPins.GPIO_PinConfig.GPIO_PinNumber = 10;
		GPIO_Init(&I2CPins);

		/* PB11 -> SDA */
		I2CPins.GPIO_PinConfig.GPIO_PinNumber = 11;
		GPIO_Init(&I2CPins);
		I2C2_inits();

}

void  I2C2_inits(void)
{
	I2C2Handle.pI2Cx = I2C2;

		I2C2Handle.I2C_Config.SCLSpeed = 100000;
		I2C2Handle.I2C_Config.DeviceAddress = 0x61;
		I2C2Handle.I2C_Config.ACKControl = ENABLE;

		I2C_Init(&I2C2Handle);
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


void print_last_5_logs(void)
{
    opt3001_log_t read_data;

    uint32_t available_logs = (log_count < 5) ? log_count : 5;

    printf("\r\nLast %lu Entries:\r\n", available_logs);

    for (int i = 0; i < 5; i++)
    {
        uint32_t offset = (i + 1) * sizeof(opt3001_log_t);
        uint32_t read_addr;

        if ((write_addr - FLASH_START_ADDR) >= offset)
        {
            read_addr = write_addr - offset;
        }
        else
        {
            read_addr =
                FLASH_START_ADDR +
                FLASH_SECTOR_SIZE -
                (offset - (write_addr - FLASH_START_ADDR));
        }

        W25Q_Read(read_addr,
                  (uint8_t*)&read_data,
                  sizeof(opt3001_log_t));

        printf("[%d] Light value(xl) : %lu\r\n", i, read_data.lux);
    }
}


void EXTI15_10_IRQHandler(void)
{
	GPIO_IRQHandling(13);
	read_request = 1;
}


int main()
{
	GPIO_PeriClockControl(GPIOA, ENABLE);
	GPIO_PeriClockControl(GPIOB, ENABLE);
    UART_GPIO_Init();
    SPI_GPIO_Init();
    GPIO_Inits();
    I2C2_GPIOInits();

    UART_Init();
    USART_PeriClockControl(USART2, ENABLE);
    USART_PeripheralControl(USART2, ENABLE);
    OPT3001_Init(&I2C2Handle);
    W25Q_Init();

    W25Q_EraseSector(0);
    I2C2_GPIOInits();

	while (1) {

				sensor_log.lux = OPT3001_ReadLux(&I2C2Handle);

		        /*
		         * Sector wrap check
		         */
		        if ((write_addr + sizeof(opt3001_log_t)) >
		            (FLASH_START_ADDR + FLASH_SECTOR_SIZE))
		        {
		            W25Q_EraseSector(0);
		            write_addr = FLASH_START_ADDR;
		        }

		        W25Q_Write(write_addr,
		                   (uint8_t*)&sensor_log,
		                   sizeof(opt3001_log_t));

		        write_addr += sizeof(opt3001_log_t);

		        if (log_count < (FLASH_SECTOR_SIZE / sizeof(opt3001_log_t)))
		        {
		            log_count++;
		        }

		        if (read_request)
		        {
		            read_request = 0;

		            print_last_5_logs();
		        }

		        delay_ms(100);
		    }
}

