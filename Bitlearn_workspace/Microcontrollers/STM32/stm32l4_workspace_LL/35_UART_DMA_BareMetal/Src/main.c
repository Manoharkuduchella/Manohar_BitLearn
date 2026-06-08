
#include "stm32l476xx.h"
#include "stm32l476xx_gpio_drivers.h"
#include "stm32l476xx_usart_driver.h"
#include <inttypes.h>

USART_Handle_t USARTHandle;


void UART_GPIO_Init()
{
    GPIO_Handle_t UARTPins;

    UARTPins.pGPIOx = GPIOA;

    UARTPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
    UARTPins.GPIO_PinConfig.GPIO_PinAltFunMode = 7;
    UARTPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    UARTPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
    UARTPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

    /************ USART2_TX -> PA2 ************/
    UARTPins.GPIO_PinConfig.GPIO_PinNumber = 2;
    GPIO_Init(&UARTPins);

    /************ USART2_RX -> PA3 ************/
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



uint8_t txBuf[] = "UART DMA Test\r\n";

int main(void)
{
    UART_GPIO_Init();

    UART_Init();

    USART_PeripheralControl(USART2, ENABLE);

    USART_SendDataDMA(USART2,
                      txBuf,
                      sizeof(txBuf)-1);

    while(1)
    {

    }
}


