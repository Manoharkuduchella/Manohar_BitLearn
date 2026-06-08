/*
 * stm32l476xx_uart_driver.h
 *
 *  Created on: May 18, 2026
 *      Author: manohar kuduchella
 */

#ifndef INC_STM32L476XX_USART_DRIVER_H_
#define INC_STM32L476XX_USART_DRIVER_H_

#include "stm32l476xx.h"

/*
 * Configuration structure for USARTx peripheral - STM32L4
 */
typedef struct
{
    uint8_t USART_Mode;             /* TX only, RX only, or TXRX */
    uint32_t USART_Baud;            /* Baud rate: 9600, 115200 etc */
    uint8_t USART_NoOfStopBits;     /* Stop bits: 1, 0.5, 2, 1.5 */
    uint8_t USART_WordLength;       /* 8-bit, 9-bit, 7-bit */
    uint8_t USART_ParityControl;    /* No parity, even parity, odd parity */
    uint8_t USART_HWFlowControl;    /* CTS/RTS flow control */

} USART_Config_t;


/*
 * Handle structure for USARTx peripheral - STM32L4
 */
typedef struct
{
    USART_RegDef_t *pUSARTx;
    USART_Config_t USART_Config;

} USART_Handle_t;



/*
 * USART possible modes
 */
//#define USART_MODE_ONLY_TX          0
//#define USART_MODE_ONLY_RX          1
//#define USART_MODE_TXRX             2

/*
 * USART baud rates
 */
#define USART_STD_BAUD_1200         1200
#define USART_STD_BAUD_2400         2400
#define USART_STD_BAUD_9600         9600
#define USART_STD_BAUD_19200        19200
#define USART_STD_BAUD_38400        38400
#define USART_STD_BAUD_57600        57600
#define USART_STD_BAUD_115200       115200
#define USART_STD_BAUD_230400       230400
#define USART_STD_BAUD_460800       460800
#define USART_STD_BAUD_921600       921600


/*
 * USART stop bits
 */
#define USART_STOPBITS_1            0
#define USART_STOPBITS_0_5          1
#define USART_STOPBITS_2            2
#define USART_STOPBITS_1_5          3

/*
 * USART word length
 */
#define USART_WORDLEN_8BITS         0
//#define USART_WORDLEN_9BITS         1
#define USART_WORDLEN_7BITS         2

/*
 * USART parity control
 */
#define USART_PARITY_DISABLE        0
//#define USART_PARITY_EN_EVEN        1
//#define USART_PARITY_EN_ODD         2


/*
 * USART hardware flow control
 */
#define USART_HW_FLOW_CTRL_NONE     0
#define USART_HW_FLOW_CTRL_CTS      1
#define USART_HW_FLOW_CTRL_RTS      2
#define USART_HW_FLOW_CTRL_CTS_RTS  3


/*
 * Bit position definitions USART_CR1
 */
#define USART_CR1_UE            0
#define USART_CR1_UESM          1
#define USART_CR1_RE            2
#define USART_CR1_TE            3
#define USART_CR1_IDLEIE        4
#define USART_CR1_RXNEIE        5
#define USART_CR1_TCIE          6
#define USART_CR1_TXEIE         7
#define USART_CR1_PEIE          8
#define USART_CR1_PS            9
#define USART_CR1_PCE           10
#define USART_CR1_WAKE          11
#define USART_CR1_M0            12
#define USART_CR1_MME           13
#define USART_CR1_CMIE          14
#define USART_CR1_OVER8         15
#define USART_CR1_DEDT          16
#define USART_CR1_DEAT          21
#define USART_CR1_RTOIE         26
#define USART_CR1_EOBIE         27
#define USART_CR1_M1            28

/*
 * Bit position definitions USART_CR2
 */
#define USART_CR2_STOP          12

/*
 * Bit position definitions USART_CR3
 */
#define USART_CR3_RTSE          8
#define USART_CR3_CTSE          9

/*
 * Bit position definitions USART_ISR
 */
#define USART_ISR_PE            0
#define USART_ISR_FE            1
#define USART_ISR_NE            2
#define USART_ISR_ORE           3
#define USART_ISR_IDLE          4
#define USART_ISR_RXNE          5
#define USART_ISR_TC            6
#define USART_ISR_TXE           7
#define USART_ISR_BUSY          16
#define USART_ISR_TEACK         21
#define USART_ISR_REACK         22


#define USART_FLAG_PE           (1 << USART_ISR_PE)
#define USART_FLAG_FE           (1 << USART_ISR_FE)
#define USART_FLAG_NE           (1 << USART_ISR_NE)
#define USART_FLAG_ORE          (1 << USART_ISR_ORE)
#define USART_FLAG_IDLE         (1 << USART_ISR_IDLE)
//#define USART_FLAG_RXNE         (1 << USART_ISR_RXNE)
//#define USART_FLAG_TC           (1 << USART_ISR_TC)
//#define USART_FLAG_TXE          (1 << USART_ISR_TXE)
#define USART_FLAG_BUSY         (1 << USART_ISR_BUSY)
#define USART_FLAG_TEACK        (1 << USART_ISR_TEACK)
#define USART_FLAG_REACK        (1 << USART_ISR_REACK)


#define USART_ICR_PECF          0
#define USART_ICR_FECF          1
#define USART_ICR_NCF           2
#define USART_ICR_ORECF         3
#define USART_ICR_IDLECF        4
#define USART_ICR_TCCF          6


/*******************USART API's*******************/


void USART_PeriClockControl(USART_RegDef_t *pUSARTx, uint8_t EnorDi);

void USART_Init(USART_Handle_t *pUSARTHandle);
void USART_DeInit(USART_RegDef_t *pUSARTx);

void USART_SendData(USART_RegDef_t *pUSARTx, uint8_t *pTxBuffer, uint32_t Len);
void USART_ReceiveData(USART_RegDef_t *pUSARTx, uint8_t *pRxBuffer, uint32_t Len);

void USART_SendDataIT(USART_Handle_t *pUSARTHandle, uint8_t *pTxBuffer, uint32_t Len);
void USART_ReceiveDataIT(USART_Handle_t *pUSARTHandle, uint8_t *pRxBuffer, uint32_t Len);

void USART_PeripheralControl(USART_RegDef_t *pUSARTx, uint8_t EnorDi);

uint8_t USART_GetFlagStatus(USART_RegDef_t *pUSARTx, uint16_t FlagName);
void USART_ClearFlag(USART_RegDef_t *pUSARTx, uint16_t FlagName);

void USART_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);
void USART_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority);

void USART_SetBaudRate(USART_RegDef_t *pUSARTx, uint32_t BaudRate);


#endif /* INC_STM32L476XX_USART_DRIVER_H_ */
