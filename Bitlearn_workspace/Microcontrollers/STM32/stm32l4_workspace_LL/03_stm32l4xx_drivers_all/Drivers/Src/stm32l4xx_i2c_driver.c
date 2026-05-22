/*
 * stm32l4xx_i2c_driver.c
 *
 *  Created on: May 14, 2026
 *      Author: manohar kuduchella
 */

#include "stm32l476xx_i2c_driver.h"
/*
 *
 * Peripheral Clock setup
 * */

#define I2C_TIMEOUT_VALUE   500000U


void I2C_PeriClockControl(I2C_RegDef_t *pI2Cx,uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
			if(pI2Cx == I2C1)
			{
				I2C1_PCLK_EN();

			}else if(pI2Cx == I2C2)
			{
				I2C2_PCLK_EN();

			}else if(pI2Cx == I2C3)
			{
				I2C3_PCLK_EN();
			}
	}else
	{
		if(pI2Cx == I2C1)
		{
			I2C1_PCLK_DI();

		}else if(pI2Cx == I2C2)
		{
			I2C2_PCLK_DI();

		}else if(pI2Cx == I2C3)
		{
			I2C3_PCLK_DI();
		}
	}

}

void I2C_PeripheralControl(I2C_RegDef_t *pI2Cx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		pI2Cx->CR1 |= (1 << I2C_CR1_PE);
	}else
	{
		pI2Cx->CR1 &= ~(1 << I2C_CR1_PE);
	}

}

void I2C_Init(I2C_Handle_t *pI2CHandle)
{
	uint32_t tempreg = 0;

	I2C_PeriClockControl(pI2CHandle->pI2Cx, ENABLE);

	tempreg = 0;

	if (pI2CHandle->I2C_Config.I2C_OwnAddress1 != 0)
	{
	    if (pI2CHandle->I2C_Config.I2C_AddressingMode == I2C_ADDRESSINGMODE_7BIT)
	    {
	        tempreg |= (pI2CHandle->I2C_Config.I2C_OwnAddress1 << 1);
	    }
	    else
	    {
	        tempreg |= (pI2CHandle->I2C_Config.I2C_OwnAddress1 & 0x3FF);
	        tempreg |= (1 << I2C_OAR1_OA1MODE);
	    }

	    tempreg |= (1 << I2C_OAR1_OA1EN);
	}

	pI2CHandle->pI2Cx->OAR1 = tempreg;



     /*
      * 5. Configure analog filter
      *
      * ANFOFF = 0: analog filter enabled
      * ANFOFF = 1: analog filter disabled
      */
     if (pI2CHandle->I2C_Config.I2C_AnalogFilter == I2C_ANALOGFILTER_DISABLE)
     {
         pI2CHandle->pI2Cx->CR1 |= (1 << I2C_CR1_ANFOFF);
     }
     else
     {
         pI2CHandle->pI2Cx->CR1 &= ~(1 << I2C_CR1_ANFOFF);
     }


     /*
      * 6. Configure digital noise filter
      *
      * DNF bits are CR1[11:8]
      * valid value: 0 to 15
      */
     pI2CHandle->pI2Cx->CR1 &= ~(0xF << I2C_CR1_DNF);

     pI2CHandle->pI2Cx->CR1 |=
         ((pI2CHandle->I2C_Config.I2C_DigitalFilter & 0xF) << I2C_CR1_DNF);


     /*
      * 7. Configure clock stretching
      *
      * NOSTRETCH = 0: clock stretching enabled
      * NOSTRETCH = 1: clock stretching disabled
      */
     if (pI2CHandle->I2C_Config.I2C_StretchMode == I2C_STRETCH_DISABLE)
     {
         pI2CHandle->pI2Cx->CR1 |= (1 << I2C_CR1_NOSTRETCH);
     }
     else
     {
         pI2CHandle->pI2Cx->CR1 &= ~(1 << I2C_CR1_NOSTRETCH);
     }


     pI2CHandle->pI2Cx->TIMINGR = pI2CHandle->I2C_Config.I2C_Timing;//Put calculated value

     I2C_PeripheralControl(pI2CHandle->pI2Cx, ENABLE);

}



void I2C_DeInit(I2C_RegDef_t *pI2Cx)
{
	if(pI2Cx == I2C1)
	{
		I2C1_REG_RESET();

	}else if(pI2Cx == I2C2)
	{
		I2C2_REG_RESET();

	}else if(pI2Cx == I2C3)
	{
		I2C3_REG_RESET();

	}
}



uint8_t I2C_GetFlagStatus(I2C_RegDef_t *pI2Cx, uint32_t FlagName)
{
	if(pI2Cx->ISR & FlagName)
	{
		return FLAG_SET;
	}
	return FLAG_RESET;
}

static void I2C_ClearSTOPFlag(I2C_RegDef_t *pI2Cx)
{
    pI2Cx->ICR |= (1 << I2C_ICR_STOPCF);
}

static void I2C_ClearNACKFlag(I2C_RegDef_t *pI2Cx)
{
    pI2Cx->ICR |= (1 << I2C_ICR_NACKCF);
}


static void I2C_MasterTransferConfig(I2C_RegDef_t *pI2Cx,
                                     uint8_t SlaveAddr,
                                     uint8_t TransferDirection,
                                     uint8_t NBytes,
                                     uint8_t AutoEnd)
{
    uint32_t tempreg = 0;

    /*
     * Clear these CR2 fields before new transfer:
     * SADD[9:0], RD_WRN, ADD10, HEAD10R, NBYTES[7:0],
     * RELOAD, AUTOEND, START, STOP, NACK
     */
    pI2Cx->CR2 &= ~((0x3FF << I2C_CR2_SADD)   |
                    (1 << I2C_CR2_RD_WRN)     |
                    (1 << I2C_CR2_ADD10)      |
                    (1 << I2C_CR2_HEAD10R)    |
                    (0xFF << I2C_CR2_NBYTES)  |
                    (1 << I2C_CR2_RELOAD)     |
                    (1 << I2C_CR2_AUTOEND)    |
                    (1 << I2C_CR2_START)      |
                    (1 << I2C_CR2_STOP)       |
                    (1 << I2C_CR2_NACK));

    /*
     * 7-bit slave address:
     * In STM32L4 CR2, SADD[7:1] contains slave address.
     * So shift left by 1.
     */
    tempreg |= ((uint32_t)(SlaveAddr << 1) & 0x3FF);

    /*
     * Direction
     * 0 = write
     * 1 = read
     */
    if (TransferDirection == I2C_READ)
    {
        tempreg |= (1 << I2C_CR2_RD_WRN);
    }

    /*
     * Number of bytes
     */
    tempreg |= ((NBytes & 0xFF) << I2C_CR2_NBYTES);

    /*
     * AUTOEND
     * If AUTOEND = 1, STOP is automatically generated after NBYTES transfer.
     */
    if (AutoEnd == I2C_AUTOEND_ENABLE)
    {
        tempreg |= (1 << I2C_CR2_AUTOEND);
    }

    /*
     * Generate START
     */
    tempreg |= (1 << I2C_CR2_START);

    /*
     * Write final CR2 value
     */
    pI2Cx->CR2 |= tempreg;
}


void I2C_MasterSendData(I2C_Handle_t *pI2CHandle,
                        uint8_t *pTxbuffer,
                        uint32_t len,
                        uint8_t SlaveAddr)
{
    uint32_t i;

    if ((len == 0) || (len > 255))
    {
        return;
    }

    while (I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_BUSY) == FLAG_SET);

    I2C_MasterTransferConfig(pI2CHandle->pI2Cx,
                          SlaveAddr,
						  I2C_WRITE,
                          (uint8_t)len,
                          I2C_AUTOEND_ENABLE);


    for (i = 0; i < len; i++)
    {
        while (I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_TXIS) == FLAG_RESET)
        {
        	if (I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_NACKF) == FLAG_SET)
        	{
        	    I2C_ClearNACKFlag(pI2CHandle->pI2Cx);

        	    if (I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_STOPF) == FLAG_SET)
        	    {
        	        I2C_ClearSTOPFlag(pI2CHandle->pI2Cx);
        	    }

        	    return;
        	}
        }

        pI2CHandle->pI2Cx->TXDR = pTxbuffer[i];
    }

    while (I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_STOPF) == FLAG_RESET);

    I2C_ClearSTOPFlag(pI2CHandle->pI2Cx);
}

void I2C_MasterReceiveData(I2C_Handle_t *pI2CHandle,
                           uint8_t *pRxbuffer,
                           uint32_t len,
                           uint8_t SlaveAddr)
{
    uint32_t i;

    if ((len == 0) || (len > 255))
    {
        return;
    }

    while (I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_BUSY) == FLAG_SET);

    I2C_MasterTransferConfig(pI2CHandle->pI2Cx,
                             SlaveAddr,
                             I2C_READ,
                             (uint8_t)len,
                             I2C_AUTOEND_ENABLE);

    for (i = 0; i < len; i++)
    {
        while (I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_RXNE) == FLAG_RESET)
        {
        	if (I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_NACKF) == FLAG_SET)
        	{
        	    I2C_ClearNACKFlag(pI2CHandle->pI2Cx);

        	    if (I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_STOPF) == FLAG_SET)
        	    {
        	        I2C_ClearSTOPFlag(pI2CHandle->pI2Cx);
        	    }

        	    return;
        	}

        }

        pRxbuffer[i] = pI2CHandle->pI2Cx->RXDR;
    }

    while (I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_STOPF) == FLAG_RESET);

    I2C_ClearSTOPFlag(pI2CHandle->pI2Cx);
}


//uint8_t I2C_MasterReadRegister(I2C_Handle_t *pI2CHandle,
//                               uint8_t SlaveAddr,
//                               uint8_t RegAddr,
//                               uint8_t *pRxBuffer,
//                               uint32_t len)
//{
//    uint32_t i;
//
//    if ((len == 0) || (len > 255))
//    {
//        return 0;
//    }
//
//    /*
//     * Wait until bus free
//     */
//    while (I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_BUSY) == FLAG_SET);
//
//    /*
//     * Step 1: Write register address
//     * AUTOEND disabled, so no STOP.
//     * After one byte, TC flag will set.
//     */
//    I2C_MasterTransferConfig(pI2CHandle->pI2Cx,
//                             SlaveAddr,
//                             I2C_WRITE,
//                             1,
//                             I2C_AUTOEND_DISABLE);
//
//    /*
//     * Wait TXIS
//     */
//    while (I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_TXIS) == FLAG_RESET)
//    {
//        if (I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_NACKF) == FLAG_SET)
//        {
//            I2C_ClearNACKFlag(pI2CHandle->pI2Cx);
//            return 0;
//        }
//    }
//
//    /*
//     * Send register address
//     */
//    pI2CHandle->pI2Cx->TXDR = RegAddr;
//
//    /*
//     * Wait TC = transfer complete, no STOP generated
//     */
//    while (I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_TC) == FLAG_RESET)
//    {
//        if (I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_NACKF) == FLAG_SET)
//        {
//            I2C_ClearNACKFlag(pI2CHandle->pI2Cx);
//            return 0;
//        }
//    }
//
//    /*
//     * Step 2: Repeated START + read
//     */
//    I2C_MasterTransferConfig(pI2CHandle->pI2Cx,
//                             SlaveAddr,
//                             I2C_READ,
//                             (uint8_t)len,
//                             I2C_AUTOEND_ENABLE);
//
//    /*
//     * Read bytes
//     */
//    for (i = 0; i < len; i++)
//    {
//        while (I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_RXNE) == FLAG_RESET)
//        {
//            if (I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_NACKF) == FLAG_SET)
//            {
//                I2C_ClearNACKFlag(pI2CHandle->pI2Cx);
//                return 0;
//            }
//        }
//
//        pRxBuffer[i] = pI2CHandle->pI2Cx->RXDR;
//    }
//
//    /*
//     * Wait STOPF
//     */
//    while (I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_STOPF) == FLAG_RESET);
//
//    /*
//     * Clear STOPF
//     */
//    I2C_ClearSTOPFlag(pI2CHandle->pI2Cx);
//
//    return 1;
//}



uint8_t I2C_MasterWriteRegister(I2C_Handle_t *pI2CHandle,uint8_t SlaveAddr,uint8_t RegAddr,uint8_t *pTxBuffer, uint32_t len)
{
    uint32_t i;

    if (len > 254)
    {
        return 0;
    }

    while (I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_BUSY) == FLAG_SET);

    /*
     * Total bytes = register address + data bytes
     */
    I2C_MasterTransferConfig(pI2CHandle->pI2Cx,
                             SlaveAddr,
                             I2C_WRITE,
                             (uint8_t)(len + 1),
                             I2C_AUTOEND_ENABLE);

    /*
     * Send register address first
     */
    while (I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_TXIS) == FLAG_RESET)
    {
        if (I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_NACKF) == FLAG_SET)
        {
            I2C_ClearNACKFlag(pI2CHandle->pI2Cx);
            return 0;
        }
    }

    pI2CHandle->pI2Cx->TXDR = RegAddr;

    /*
     * Send data bytes
     */
    for (i = 0; i < len; i++)
    {
        while (I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_TXIS) == FLAG_RESET)
        {
            if (I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_NACKF) == FLAG_SET)
            {
                I2C_ClearNACKFlag(pI2CHandle->pI2Cx);
                return 0;
            }
        }

        pI2CHandle->pI2Cx->TXDR = pTxBuffer[i];
    }

    while (I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_STOPF) == FLAG_RESET);

    I2C_ClearSTOPFlag(pI2CHandle->pI2Cx);

    return 1;
}







uint8_t I2C_MasterReadRegister(I2C_Handle_t *pI2CHandle,
                               uint8_t SlaveAddr,
                               uint8_t RegAddr,
                               uint8_t *pRxBuffer,
                               uint32_t len)
{
    uint32_t i;
    uint32_t timeout;

    if ((len == 0) || (len > 255))
    {
        return 0;
    }

    timeout = I2C_TIMEOUT_VALUE;
    while (I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_BUSY) == FLAG_SET)
    {
        if (timeout-- == 0)
        {
            return 0;
        }
    }

    if (I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_STOPF) == FLAG_SET)
    {
        I2C_ClearSTOPFlag(pI2CHandle->pI2Cx);
    }

    if (I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_NACKF) == FLAG_SET)
    {
        I2C_ClearNACKFlag(pI2CHandle->pI2Cx);
    }

    /*
     * Phase 1: write register address, no STOP
     */
    I2C_MasterTransferConfig(pI2CHandle->pI2Cx,
                             SlaveAddr,
                             I2C_WRITE,
                             1,
                             I2C_AUTOEND_DISABLE);

    timeout = I2C_TIMEOUT_VALUE;
    while (I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_TXIS) == FLAG_RESET)
    {
        if (I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_NACKF) == FLAG_SET)
        {
            I2C_ClearNACKFlag(pI2CHandle->pI2Cx);

            if (I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_STOPF) == FLAG_SET)
            {
                I2C_ClearSTOPFlag(pI2CHandle->pI2Cx);
            }

            return 0;
        }

        if (timeout-- == 0)
        {
            return 0;
        }
    }

    pI2CHandle->pI2Cx->TXDR = RegAddr;

    /*
     * Wait TC
     */
    timeout = I2C_TIMEOUT_VALUE;
    while (I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_TC) == FLAG_RESET)
    {
        if (I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_NACKF) == FLAG_SET)
        {
            I2C_ClearNACKFlag(pI2CHandle->pI2Cx);

            if (I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_STOPF) == FLAG_SET)
            {
                I2C_ClearSTOPFlag(pI2CHandle->pI2Cx);
            }

            return 0;
        }

        if (I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_STOPF) == FLAG_SET)
        {
            I2C_ClearSTOPFlag(pI2CHandle->pI2Cx);
            return 0;
        }

        if (timeout-- == 0)
        {
            return 0;
        }
    }

    /*
     * Phase 2: repeated START + read
     */
    I2C_MasterTransferConfig(pI2CHandle->pI2Cx,
                             SlaveAddr,
                             I2C_READ,
                             (uint8_t)len,
                             I2C_AUTOEND_ENABLE);

    for (i = 0; i < len; i++)
    {
        timeout = I2C_TIMEOUT_VALUE;

        while (I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_RXNE) == FLAG_RESET)
        {
            if (I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_NACKF) == FLAG_SET)
            {
                I2C_ClearNACKFlag(pI2CHandle->pI2Cx);

                if (I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_STOPF) == FLAG_SET)
                {
                    I2C_ClearSTOPFlag(pI2CHandle->pI2Cx);
                }

                return 0;
            }

            /*
             * For safety: if STOP happens and RXNE never came,
             * don't hang forever.
             */
            if (I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_STOPF) == FLAG_SET)
            {
                return 0;
            }

            if (timeout-- == 0)
            {
                return 0;
            }
        }

        pRxBuffer[i] = (uint8_t)pI2CHandle->pI2Cx->RXDR;
    }

    /*
     * Wait STOPF after AUTOEND
     */
    timeout = I2C_TIMEOUT_VALUE;
    while (I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_STOPF) == FLAG_RESET)
    {
        if (timeout-- == 0)
        {
            return 0;
        }
    }

    I2C_ClearSTOPFlag(pI2CHandle->pI2Cx);

    return 1;
}
