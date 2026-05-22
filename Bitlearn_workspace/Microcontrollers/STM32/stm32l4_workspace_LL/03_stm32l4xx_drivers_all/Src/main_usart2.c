/*
 * main_usart2.c
 *
 *  Created on: May 18, 2026
 *      Author: manohar kuduchella
 */


#include "stm32l476xx.h"
#include <string.h>

USART_Handle_t usart2_handle;

void delay(void)
{
    for(uint32_t i = 0; i < 500000; i++);
}

void USART2_GPIOInit(void)
{
    GPIO_Handle_t usart_gpios;

    usart_gpios.pGPIOx = GPIOA;
    usart_gpios.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
    usart_gpios.GPIO_PinConfig.GPIO_PinAltFunMode = 7;
    usart_gpios.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    usart_gpios.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
    usart_gpios.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

    /*
     * USART2_TX -> PA2
     */
    usart_gpios.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_2;
    GPIO_Init(&usart_gpios);

    /*
     * USART2_RX -> PA3
     */
    usart_gpios.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_3;
    GPIO_Init(&usart_gpios);
}

void USART2_Init(void)
{
    usart2_handle.pUSARTx = USART2;
    usart2_handle.USART_Config.USART_Mode = USART_MODE_ONLY_TX;
    usart2_handle.USART_Config.USART_Baud = USART_STD_BAUD_9600;
    usart2_handle.USART_Config.USART_NoOfStopBits = USART_STOPBITS_1;
    usart2_handle.USART_Config.USART_WordLength = USART_WORDLEN_8BITS;
    usart2_handle.USART_Config.USART_ParityControl = USART_PARITY_DISABLE;
    usart2_handle.USART_Config.USART_HWFlowControl = USART_HW_FLOW_CTRL_NONE;

    USART_Init(&usart2_handle);
}

char tx_data[] = "UART2 OK\r\n";
char rx_data[sizeof(tx_data)];

int main(void)
{


    /*
     * GPIO init for PA2 and PA3
     */
    USART2_GPIOInit();

    /*
     * USART2 peripheral init
     */
    USART2_Init();

    /*
     * Enable USART2
     */
    USART_PeripheralControl(USART2, ENABLE);

    while(1)
    {
        memset(rx_data, 0, sizeof(rx_data));

        USART_SendData(USART2, (uint8_t*)tx_data, strlen(tx_data));

        USART_ReceiveData(USART2, (uint8_t*)rx_data, strlen(tx_data));

        /*
         * Put breakpoint here and check rx_data.
         * Expected:
         * rx_data = "UART2 LOOPBACK OK\r\n"
         */
        delay();



    }
}
