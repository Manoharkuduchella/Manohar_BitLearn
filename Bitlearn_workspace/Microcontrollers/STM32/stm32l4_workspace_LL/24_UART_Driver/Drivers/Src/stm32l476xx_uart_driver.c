/*
 * stm32l476xx_uart_driver.c
 *
 *  Created on: May 18, 2026
 *      Author: manohar kuduchella
 */

/*
 * Peripheral Clock setup
 * */
#include <stm32l476xx_usart_driver.h>
#include "stm32l476xx_rcc_driver.h"

void USART_PeriClockControl(USART_RegDef_t *pUSARTx,uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
			if(pUSARTx == USART1)
			{
				USART1_PCLK_EN();

			}else if(pUSARTx == USART2)
			{
				USART2_PCLK_EN();

			}else if(pUSARTx == USART3)
			{
				USART3_PCLK_EN();
			}
	}else
	{
		if(pUSARTx == USART1)
		{
			USART1_PCLK_DI();

		}else if(pUSARTx == USART2)
		{
			USART2_PCLK_DI();

		}else if(pUSARTx == USART3)
		{
			USART3_PCLK_DI();
		}
	}
}
/*
 * Init and De-init
 */
void USART_Init(USART_Handle_t *pUSARTHandle)
{
    uint32_t tempreg = 0;

    /*
     * Enable peripheral clock
     */
    USART_PeriClockControl(pUSARTHandle->pUSARTx, ENABLE);

    /*
     * Disable USART before configuration
     */
    USART_PeripheralControl(pUSARTHandle->pUSARTx, DISABLE);

    /*
     * Configure USART mode
     */
    if(pUSARTHandle->USART_Config.USART_Mode == USART_MODE_ONLY_TX)
    {
        tempreg |= (1 << USART_CR1_TE);
    }
    else if(pUSARTHandle->USART_Config.USART_Mode == USART_MODE_ONLY_RX)
    {
        tempreg |= (1 << USART_CR1_RE);
    }
    else if(pUSARTHandle->USART_Config.USART_Mode == USART_MODE_TXRX)
    {
        tempreg |= (1 << USART_CR1_TE);
        tempreg |= (1 << USART_CR1_RE);
    }

    /*
     * Configure word length
     *
     * STM32L4:
     * M1 M0
     * 0  0  = 8 bits
     * 0  1  = 9 bits
     * 1  0  = 7 bits
     */
    if(pUSARTHandle->USART_Config.USART_WordLength == USART_WORDLEN_8BITS)
    {
        tempreg &= ~(1 << USART_CR1_M0);
        tempreg &= ~(1 << USART_CR1_M1);
    }
    else if(pUSARTHandle->USART_Config.USART_WordLength == USART_WORDLEN_9BITS)
    {
        tempreg |=  (1 << USART_CR1_M0);
        tempreg &= ~(1 << USART_CR1_M1);
    }
    else if(pUSARTHandle->USART_Config.USART_WordLength == USART_WORDLEN_7BITS)
    {
        tempreg &= ~(1 << USART_CR1_M0);
        tempreg |=  (1 << USART_CR1_M1);
    }

    /*
     * Configure parity
     */
    if(pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_DISABLE)
    {
        tempreg &= ~(1 << USART_CR1_PCE);
    }
    else if(pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_EN_EVEN)
    {
        tempreg |=  (1 << USART_CR1_PCE);
        tempreg &= ~(1 << USART_CR1_PS);
    }
    else if(pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_EN_ODD)
    {
        tempreg |= (1 << USART_CR1_PCE);
        tempreg |= (1 << USART_CR1_PS);
    }

    /*
     * Configure oversampling by 16
     */
    tempreg &= ~(1 << USART_CR1_OVER8);

    /*
     * Write CR1
     */
    pUSARTHandle->pUSARTx->CR1 = tempreg;


    /*
     * Configure stop bits in CR2
     */
    tempreg = 0;

    tempreg |= pUSARTHandle->USART_Config.USART_NoOfStopBits << USART_CR2_STOP;

    pUSARTHandle->pUSARTx->CR2 = tempreg;


    /*
     * Configure hardware flow control in CR3
     */
    tempreg = 0;

    if(pUSARTHandle->USART_Config.USART_HWFlowControl == USART_HW_FLOW_CTRL_CTS)
    {
        tempreg |= (1 << USART_CR3_CTSE);
    }
    else if(pUSARTHandle->USART_Config.USART_HWFlowControl == USART_HW_FLOW_CTRL_RTS)
    {
        tempreg |= (1 << USART_CR3_RTSE);
    }
    else if(pUSARTHandle->USART_Config.USART_HWFlowControl == USART_HW_FLOW_CTRL_CTS_RTS)
    {
        tempreg |= (1 << USART_CR3_CTSE);
        tempreg |= (1 << USART_CR3_RTSE);
    }

    pUSARTHandle->pUSARTx->CR3 = tempreg;


    /*
     * Configure baud rate
     */
    USART_SetBaudRate(pUSARTHandle->pUSARTx, pUSARTHandle->USART_Config.USART_Baud);
}

void USART_DeInit(USART_RegDef_t *pUSARTx)
{
    if(pUSARTx == USART1)
    {
        USART1_REG_RESET();
    }
    else if(pUSARTx == USART2)
    {
        USART2_REG_RESET();
    }
    else if(pUSARTx == USART3)
    {
        USART3_REG_RESET();
    }
}


/*
 * Data Send and Receive
 */
void USART_SendData(USART_RegDef_t *pUSARTx, uint8_t *pTxBuffer, uint32_t Len)
{
    uint16_t *pdata;

    for(uint32_t i = 0; i < Len; i++)
    {
        /*
         * Wait until TXE is set
         */
        while(!USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE));

        /*
         * Check word length
         */
        if(pUSARTx->CR1 & (1 << USART_CR1_M0))
        {
            /*
             * 9-bit data
             */
            pdata = (uint16_t*)pTxBuffer;
            pUSARTx->TDR = (*pdata & (uint16_t)0x01FF);

            /*
             * If parity is disabled, 9 bits of user data are sent.
             * So increment buffer by 2.
             */
            if(!(pUSARTx->CR1 & (1 << USART_CR1_PCE)))
            {
                pTxBuffer++;
                pTxBuffer++;
            }
            else
            {
                /*
                 * If parity is enabled, 8 bits of user data + 1 parity bit.
                 * So increment buffer by 1.
                 */
                pTxBuffer++;
            }
        }
        else
        {
            /*
             * 8-bit or 7-bit data
             */
            pUSARTx->TDR = (*pTxBuffer & (uint8_t)0xFF);
            pTxBuffer++;
        }
    }

    /*
     * Wait until transmission complete
     */
    while(!USART_GetFlagStatus(pUSARTx, USART_FLAG_TC));
}


void USART_ReceiveData(USART_RegDef_t *pUSARTx, uint8_t *pRxBuffer, uint32_t Len)
{
    for(uint32_t i = 0; i < Len; i++)
    {
        /*
         * Wait until RXNE is set
         */
        while(!USART_GetFlagStatus(pUSARTx, USART_FLAG_RXNE));

        /*
         * Check word length
         */
        if(pUSARTx->CR1 & (1 << USART_CR1_M0))
        {
            /*
             * 9-bit word length
             */
            if(!(pUSARTx->CR1 & (1 << USART_CR1_PCE)))
            {
                /*
                 * No parity, all 9 bits are user data
                 */
                *((uint16_t*)pRxBuffer) = (pUSARTx->RDR & (uint16_t)0x01FF);
                pRxBuffer++;
                pRxBuffer++;
            }
            else
            {
                /*
                 * Parity enabled, only 8 bits are user data
                 */
                *pRxBuffer = (pUSARTx->RDR & (uint8_t)0xFF);
                pRxBuffer++;
            }
        }
        else
        {
            /*
             * 8-bit or 7-bit word length
             */
            if(!(pUSARTx->CR1 & (1 << USART_CR1_PCE)))
            {
                /*
                 * No parity
                 */
                *pRxBuffer = (uint8_t)(pUSARTx->RDR & (uint8_t)0xFF);
            }
            else
            {
                /*
                 * Parity enabled, 7 bits user data for 8-bit word length
                 */
                *pRxBuffer = (uint8_t)(pUSARTx->RDR & (uint8_t)0x7F);
            }

            pRxBuffer++;
        }
    }
}


void USART_SetBaudRate(USART_RegDef_t *pUSARTx, uint32_t BaudRate)
{
    uint32_t PCLKx;
    uint32_t usartdiv;

    /*
     * Get peripheral clock
     */
    if(pUSARTx == USART1)
    {
        PCLKx = RCC_GetPCLK2Value();
    }
    else
    {
        PCLKx = RCC_GetPCLK1Value();
    }

    /*
     * For oversampling by 16:
     *
     * USARTDIV = PCLK / BaudRate
     * BRR = USARTDIV
     *
     * In STM32L4, when OVER8 = 0, BRR = PCLK / BaudRate
     */
    usartdiv = PCLKx / BaudRate;

    pUSARTx->BRR = usartdiv;
}

void USART_PeripheralControl(USART_RegDef_t *pUSARTx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		pUSARTx->CR1 |= (1 << USART_CR1_UE);
	}else
	{
		pUSARTx->CR1 &= ~(1 << USART_CR1_UE);
	}
}


uint8_t USART_GetFlagStatus(USART_RegDef_t *pUSARTx, uint16_t FlagName)
{
	if(pUSARTx->ISR & FlagName)
	{
		return FLAG_SET;
	}
	return FLAG_RESET;
}


void USART_ClearFlag(USART_RegDef_t *pUSARTx, uint16_t FlagName)
{
    /*
     * Only some flags are cleared through ICR.
     * TXE and RXNE are not cleared manually.
     * RXNE clears by reading RDR.
     * TXE clears by writing TDR.
     */

    if(FlagName == USART_FLAG_TC)
    {
        pUSARTx->ICR |= (1 << USART_ICR_TCCF);
    }
    else if(FlagName == USART_FLAG_IDLE)
    {
        pUSARTx->ICR |= (1 << USART_ICR_IDLECF);
    }
    else if(FlagName == USART_FLAG_ORE)
    {
        pUSARTx->ICR |= (1 << USART_ICR_ORECF);
    }
    else if(FlagName == USART_FLAG_FE)
    {
        pUSARTx->ICR |= (1 << USART_ICR_FECF);
    }
    else if(FlagName == USART_FLAG_NE)
    {
        pUSARTx->ICR |= (1 << USART_ICR_NCF);
    }
    else if(FlagName == USART_FLAG_PE)
    {
        pUSARTx->ICR |= (1 << USART_ICR_PECF);
    }
}



/*
 * IRQ Configuration and ISR handling
 * */

//void USART_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi)
//{
//	if (EnorDi == ENABLE)
//	{
//		if(IRQNumber <= 31)
//		{
//			//program ISER0 reg
//			*NVIC_ISER0 |= ( 1 << IRQNumber);
//
//		}else if (IRQNumber > 31 && IRQNumber < 64)
//		{
//			//program ISER1 reg
//			*NVIC_ISER1 |= ( 1 << IRQNumber % 32);
//
//		}else if (IRQNumber >= 64 && IRQNumber < 96)
//		{
//			*NVIC_ISER2 |= ( 1 << IRQNumber % 64);
//		}
//	}else
//	{
//		if(IRQNumber <= 31)
//		{
//			*NVIC_ICER0 |= ( 1 << IRQNumber);
//
//		}else if (IRQNumber > 31 && IRQNumber < 64)
//		{
//			*NVIC_ICER1 |= ( 1 << IRQNumber % 32);
//
//		}else if (IRQNumber >= 64 && IRQNumber < 96)
//		{
//			*NVIC_ICER2 |= ( 1 << IRQNumber % 64);
//		}
//	}
//}


//void USART_IRQPriorityConfig( uint8_t IRQNumber,uint8_t IRQPriority)
//{
//	uint8_t iprx = IRQNumber /4;
//	uint8_t iprx_section = IRQNumber % 4;
//
//	uint8_t shift_amount = ( 8 * iprx_section) + ( 8 - NO_PR_BITS_IMPLEMENTED);
//
//	*(NVIC_PR_BASE_ADDR + iprx) |= (IRQPriority << shift_amount);
//}
//
//void USART_IRQHandling(uint8_t PinNumber)
//{
//	//clear the exti pr register corresponding to the pin number
//	if (EXTI->PR1 & (1 << PinNumber))
//	{
//		EXTI->PR1 |= ( 1 << PinNumber );
//	}
//}
