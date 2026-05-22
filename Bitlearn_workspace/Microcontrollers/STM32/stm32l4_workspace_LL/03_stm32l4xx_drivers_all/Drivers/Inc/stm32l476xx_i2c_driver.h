/*
 * stm32l476xx_i2c_driver.h
 *
 *  Created on: May 14, 2026
 *      Author: manohar kuduchella
 */

#ifndef INC_STM32L476XX_I2C_DRIVER_H_
#define INC_STM32L476XX_I2C_DRIVER_H_

#include "stm32l476xx.h"

/*
 * Bit position defs I2C_CR1
 * */
#define I2C_CR1_PE             0
#define I2C_CR1_TXIE           1
#define I2C_CR1_RXIE           2
#define I2C_CR1_ADDRIE         3
#define I2C_CR1_NACKIE         4
#define I2C_CR1_STOPIE         5
#define I2C_CR1_TCIE           6
#define I2C_CR1_ERRIE          7
#define I2C_CR1_DNF            8    /* 4 bits: 11:8 */
#define I2C_CR1_ANFOFF         12
#define I2C_CR1_TXDMAEN        14
#define I2C_CR1_RXDMAEN        15
#define I2C_CR1_SBC            16
#define I2C_CR1_NOSTRETCH      17
#define I2C_CR1_WUPEN          18
#define I2C_CR1_GCEN           19
#define I2C_CR1_SMBHEN         20
#define I2C_CR1_SMBDEN         21
#define I2C_CR1_ALERTEN        22
#define I2C_CR1_PECEN          23


/*
 * Bit position defs I2C_CR2
 * */
#define I2C_CR2_SADD           0    /* 10 bits: 9:0 */
#define I2C_CR2_RD_WRN         10
#define I2C_CR2_ADD10          11
#define I2C_CR2_HEAD10R        12
#define I2C_CR2_START          13
#define I2C_CR2_STOP           14
#define I2C_CR2_NACK           15
#define I2C_CR2_NBYTES         16   /* 8 bits: 23:16 */
#define I2C_CR2_RELOAD         24
#define I2C_CR2_AUTOEND        25
#define I2C_CR2_PECBYTE        26

/*
 * Bit position defs I2C_SR1
 * */


/*
 * Bit position defs I2C_SR2
 * */


/*
 * Bit position defs I2C_TIMINGR
 * */
#define I2C_TIMINGR_SCLL       0    /* 8 bits: 7:0 */
#define I2C_TIMINGR_SCLH       8    /* 8 bits: 15:8 */
#define I2C_TIMINGR_SDADEL     16   /* 4 bits: 19:16 */
#define I2C_TIMINGR_SCLDEL     20   /* 4 bits: 23:20 */
#define I2C_TIMINGR_PRESC      28   /* 4 bits: 31:28 */

/*
 * Bit position defs I2C_ISR
 * */
#define I2C_ISR_TXE            0
#define I2C_ISR_TXIS           1
#define I2C_ISR_RXNE           2
#define I2C_ISR_ADDR           3
#define I2C_ISR_NACKF          4
#define I2C_ISR_STOPF          5
#define I2C_ISR_TC             6
#define I2C_ISR_TCR            7
#define I2C_ISR_BERR           8
#define I2C_ISR_ARLO           9
#define I2C_ISR_OVR            10
#define I2C_ISR_PECERR         11
#define I2C_ISR_TIMEOUT        12
#define I2C_ISR_ALERT          13
#define I2C_ISR_BUSY           15
#define I2C_ISR_DIR            16
#define I2C_ISR_ADDCODE        17   /* 7 bits: 23:17 */


/*
 * Bit position defs I2C_ICR
 */
#define I2C_ICR_ADDRCF         3
#define I2C_ICR_NACKCF         4
#define I2C_ICR_STOPCF         5
#define I2C_ICR_BERRCF         8
#define I2C_ICR_ARLOCF         9
#define I2C_ICR_OVRCF          10
#define I2C_ICR_PECCF          11
#define I2C_ICR_TIMOUTCF       12
#define I2C_ICR_ALERTCF        13


#define I2C_OAR1_OA1EN 			15
#define I2C_OAR1_OA1MODE		0

#define I2C_WRITE                  0
#define I2C_READ                   1

#define I2C_AUTOEND_ENABLE         1
#define I2C_AUTOEND_DISABLE        0

#define I2C_FLAG_TXIS              (1 << I2C_ISR_TXIS)
#define I2C_FLAG_TC                (1 << I2C_ISR_TC)
#define I2C_FLAG_STOPF             (1 << I2C_ISR_STOPF)
#define I2C_FLAG_NACKF             (1 << I2C_ISR_NACKF)
#define I2C_FLAG_BUSY              (1 << I2C_ISR_BUSY)
#define I2C_FLAG_RXNE              (1 << I2C_ISR_RXNE)

/*
 * Configuration structure for I2Cx peripheral - STM32L4
 */
typedef struct
{
    uint32_t I2C_Timing;

    uint32_t I2C_OwnAddress1;

    uint8_t  I2C_DeviceAddress;

    uint8_t  I2C_AckControl;

    uint8_t  I2C_AddressingMode;

    uint8_t  I2C_AnalogFilter;

    uint8_t  I2C_DigitalFilter;

    uint8_t  I2C_StretchMode;

} I2C_Config_t;


/*
 * Handle structure for I2Cx peripheral - STM32L4
 */
typedef struct
{
	I2C_RegDef_t *pI2Cx;

    I2C_Config_t I2C_Config;

    uint8_t *pTxBuffer;

    uint8_t *pRxBuffer;

    uint32_t TxLen;

    uint32_t RxLen;

    uint8_t TxRxState;

    uint8_t DevAddr;

    uint32_t RxSize;

    uint8_t Sr;

} I2C_Handle_t;


/*
 * I2C ACK control
 */
#define I2C_ACK_ENABLE              1
#define I2C_ACK_DISABLE             0

/*
 * I2C addressing mode
 */
#define I2C_ADDRESSINGMODE_7BIT     0
#define I2C_ADDRESSINGMODE_10BIT    1

/*
 * I2C analog filter
 */
#define I2C_ANALOGFILTER_ENABLE     0
#define I2C_ANALOGFILTER_DISABLE    1

/*
 * I2C clock stretching
 */
#define I2C_STRETCH_ENABLE          0
#define I2C_STRETCH_DISABLE         1

/*
 * I2C application states
 */
#define I2C_READY                   0
#define I2C_BUSY_IN_RX              1
#define I2C_BUSY_IN_TX              2

/*
 * I2C repeated start
 */
#define I2C_DISABLE_SR              0
#define I2C_ENABLE_SR               1

/*
 * I2C Timing
 */
#define I2C_SCL_SPEED_SM 	1000000
#define I2C_SCL_SPEED_FM4K 	4000000
#define I2C_SCL_SPEED_FM2K 	2000000


/*******************I2C API's*******************/


/*
 * Peripheral Clock setup
 * */

void I2C_PeriClockControl(I2C_RegDef_t *pI2Cx,uint8_t EnorDi);

/*
 * Init and De-init
 */


void I2C_Init(I2C_Handle_t *pI2CHandle);
void I2C_DeInit(I2C_RegDef_t *pI2Cx);


/*
 * Data Send and Receive
 * */
void I2C_MasterSendData(I2C_Handle_t *pI2CHandle,uint8_t *pTxbuffer,uint32_t len,uint8_t SlaveAddr);
void I2C_MasterReceiveData(I2C_Handle_t *pI2CHandle,
                           uint8_t *pRxbuffer,
                           uint32_t len,
                           uint8_t SlaveAddr);

uint8_t I2C_MasterReadRegister(I2C_Handle_t *pI2CHandle,uint8_t SlaveAddr,uint8_t RegAddr,uint8_t *pRxBuffer,uint32_t len);

uint8_t I2C_MasterWriteRegister(I2C_Handle_t *pI2CHandle,uint8_t SlaveAddr,uint8_t RegAddr,uint8_t *pTxBuffer, uint32_t len);

/*
 * IRQ Configuration and ISR handling
 * */

void I2C_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);
void I2C_IRQPriorityConfig(  uint8_t IRQNumber,uint8_t IRQPriority);


/*other api*/
void I2C_PeripheralControl(I2C_RegDef_t *pI2Cx, uint8_t EnorDi);
uint8_t I2C_GetFlagStatus(I2C_RegDef_t *pI2Cx, uint32_t FlagName);

//callback
uint8_t I2C_Transfer(I2C_RegDef_t *pI2Cx, uint8_t data);


#endif /* INC_STM32L476XX_I2C_DRIVER_H_ */
