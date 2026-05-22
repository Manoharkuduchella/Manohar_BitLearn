
#include "stm32l476xx_spi_driver.h"


/*
 * Peripheral Clock setup
 * */

void SPI_PeriClockControl(SPI_RegDef_t *pSPIx,uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
			if(pSPIx == SPI1)
			{
				SPI1_PCLK_EN();

			}else if(pSPIx == SPI2)
			{
				SPI2_PCLK_EN();

			}else if(pSPIx == SPI3)
			{
				SPI3_PCLK_EN();
			}
	}else
	{
		if(pSPIx == SPI1)
		{
			SPI1_PCLK_DI();

		}else if(pSPIx == SPI2)
		{
			SPI2_PCLK_DI();

		}else if(pSPIx == SPI3)
		{
			SPI3_PCLK_DI();
		}
		}

}



/*
 * Init and De-init
 */

void SPI_Init(SPI_Handle_t *pSPIHandle)
{

	//peripheral clock enable
	SPI_PeriClockControl(pSPIHandle->pSPIx, ENABLE);


	//config SPI_CR1 reg
	uint32_t tempreg = 0;

	//config the deive mode
	tempreg |= pSPIHandle->SPIConfig.SPI_DeviceMode << 2;//MSTR

	//config BUS
	if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_FD)
	{
		//bidi should be cleared
		tempreg &= ~( 1 << 15);
	}else if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_HD)
	{
		//bidi mode should be set
		tempreg |= (1 << 15);
	}else if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_SIMPLEX_RXONLY)
	{
		//bidi mode should be cleared
		tempreg &= ~(1 << 15);
		//rxonly bit must be set
		tempreg |= (1 << 10);
	}


	//config spi scl speed
	tempreg |= (pSPIHandle->SPIConfig.SPI_SclkSpeed << SPI_CR1_BR);

	/* -------- DFF -------- */
	/* -------- Data size (CR2 DS bits) -------- */
	pSPIHandle->pSPIx->CR2 &= ~(0xF << SPI_CR2_DS);

	if (pSPIHandle->SPIConfig.SPI_DFF == SPI_DFF_8BITS)
		pSPIHandle->pSPIx->CR2 |= (7 << SPI_CR2_DS);   // 8-bit
	else
		pSPIHandle->pSPIx->CR2 |= (15 << SPI_CR2_DS);


	//config CPOL
	tempreg |= pSPIHandle->SPIConfig.SPI_CPOL << SPI_CR1_CPOL;

	//config CPHA
	tempreg |= pSPIHandle->SPIConfig.SPI_CPHA << SPI_CR1_CPHA;

	//config Software slave management
	tempreg |= pSPIHandle->SPIConfig.SPI_SSM << SPI_CR1_SSM;

	pSPIHandle->pSPIx->CR1 = tempreg;

	/* -------- SSI (must for master + SSM) -------- */
	if (pSPIHandle->SPIConfig.SPI_SSM == SPI_SSM_EN) {
		pSPIHandle->pSPIx->CR1 |= (1 << SPI_CR1_SSI);
		//pSPIHandle->pSPIx->CR2 |= (1 << SPI_CR2_NSSP);
	}

	//enable the spi1 peripheral
	//SPI_PeripheralControl(SPI1, ENABLE);
	pSPIHandle->pSPIx->CR1 |= (1 << SPI_CR1_SPE);

}

void SPI_DeInit(SPI_RegDef_t *pSPIx)
{
	if(pSPIx == SPI1)
	{
		SPI1_REG_RESET();

	}else if(pSPIx == SPI2)
	{
		SPI2_REG_RESET();

	}else if(pSPIx == SPI3)
	{
		SPI3_REG_RESET();

	}
}

uint8_t SPI_GetFlagStatus(SPI_RegDef_t *pSPIx, uint32_t FlagName)
{
	if(pSPIx->SR & FlagName)
	{
		return FLAG_SET;
	}
	return FLAG_RESET;
}

void SPI_PeripheralControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		pSPIx->CR1 |= (1 << SPI_CR1_SPE);
	}else
	{
		pSPIx->CR1 &= ~(1 << SPI_CR1_SPE);
	}
}


/*
 * Data Send and Receive
 * */

void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t len)
{
	while(len > 0)
	{
		//wait unitl TXE is set
		while(SPI_GetFlagStatus(pSPIx,SPI_TXE_FLAG) == FLAG_RESET);
		//while(!( pSPIx->SR & (1<<1)));

		//check the Data Size
		if(((pSPIx->CR2 >> SPI_CR2_DS) & 0xF) > 8 )
		{
			//if data size is > 8bits
			pSPIx->DR = (*(uint16_t*)pTxBuffer);
			len--;
			len--;
			(uint16_t*)pTxBuffer++;
		}else
		{
			//if data size is <= 8bits
			pSPIx->DR = (*pTxBuffer);
			len--;
			pTxBuffer++;
		}
	}
	// wait until SPI is not busy
	while(SPI_GetFlagStatus(pSPIx, SPI_BSY_FLAG) == FLAG_SET);

}
void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer, uint32_t len)
{
	while(len > 0)
	{

		// wait until TXE is set
		while(SPI_GetFlagStatus(pSPIx, SPI_TXE_FLAG) == FLAG_RESET);


		//check the Data Size
		if(((pSPIx->CR2 >> SPI_CR2_DS) & 0xF) > 8 )
		{
			// send dummy byte to generate SPI clock
			pSPIx->DR = 0xFFFF;

			//wait unitl RXNE is set
			while(SPI_GetFlagStatus(pSPIx,SPI_RXNE_FLAG) == FLAG_RESET);
			//while(!( pSPIx->SR & (1<<1)));

			//if data size is > 8bits
			(*(uint16_t*)pRxBuffer) = pSPIx->DR;
			len--;
			len--;
			(uint16_t*)pRxBuffer++;
		}else
		{

			*((volatile uint8_t*) &pSPIx->DR) = 0xFF;

			//wait unitl RXNE is set
			while(SPI_GetFlagStatus(pSPIx,SPI_RXNE_FLAG) == FLAG_RESET);

			//if data size is <= 8bits
			(*pRxBuffer) = pSPIx->DR;
			len--;
			pRxBuffer++;
		}
	}

	// wait until SPI is not busy
	while(SPI_GetFlagStatus(pSPIx, SPI_BSY_FLAG) == FLAG_SET);

}



uint8_t SPI_Transfer(SPI_RegDef_t *pSPIx, uint8_t data) {
	while (!(pSPIx->SR & SPI_TXE_FLAG));

	pSPIx->DR = data;

	while (!(pSPIx->SR & SPI_RXNE_FLAG));

	return pSPIx->DR;
}


/*
 * IRQ Configuration and ISR handling
 * */

uint8_t SPI_SendData_IT(SPI_Handle_t *pSPIHandle, uint8_t *pTxBuffer, uint32_t len)
{
	uint8_t state = pSPIHandle->TxState;

	if(state != SPI_BUSY_IN_TX)
	{
		pSPIHandle->pTxBuffer = pTxBuffer;
		pSPIHandle->Txlen = len;

		pSPIHandle->TxState = SPI_BUSY_IN_TX;

		pSPIHandle->pSPIx->CR2 |= ( 1 << SPI_CR2_TXEIE);
	}


	return state;

}
uint8_t SPI_ReceiveData_IT(SPI_Handle_t *pSPIHandle, uint8_t *pRxBuffer, uint32_t len)
{
	uint8_t state = pSPIHandle->TxState;

	if(state != SPI_BUSY_IN_RX)
	{
		pSPIHandle->pRxBuffer = pRxBuffer;
		pSPIHandle->Rxlen = len;

		pSPIHandle->RxState = SPI_BUSY_IN_RX;

		pSPIHandle->pSPIx->CR2 |= ( 1 << SPI_CR2_RXNEIE);
	}


	return state;
}

void SPI_CloseTransmission(SPI_Handle_t *pSPIHandle)
{
	pSPIHandle->pSPIx->CR2 &= ~(1 << SPI_CR2_TXEIE);
	pSPIHandle->pTxBuffer=NULL;
	pSPIHandle->Txlen = 0;
	pSPIHandle->TxState = SPI_READY;

}

void SPI_CloseReception(SPI_Handle_t *pSPIHandle)
{
	pSPIHandle->pSPIx->CR2 &= ~(1 << SPI_CR2_RXNEIE);
	pSPIHandle->pRxBuffer=NULL;
	pSPIHandle->Rxlen = 0;
	pSPIHandle->RxState = SPI_READY;
}

void SPI_ClearOVRFlag(SPI_RegDef_t *pSPIx)
{
	uint8_t temp;
	temp = pSPIx->DR;
	temp = pSPIx->SR;
	(void)temp;
}


__weak void SPI_ApplicationEventCallback(SPI_Handle_t *pSPIHandle, uint8_t AppEv)
{
	//this is a weak implementation
}


static void spi_txe_interrupt_handle(SPI_Handle_t *pSPIHandle)
{
	//check the Data Size
	if(((pSPIHandle->pSPIx->CR2 >> SPI_CR2_DS) & 0xF) > 8 )
	{
		//if data size is > 8bits
		pSPIHandle->pSPIx->DR = (*(uint16_t*)pSPIHandle->pTxBuffer);
		pSPIHandle->Txlen--;
		pSPIHandle->Txlen--;
		(uint16_t*)pSPIHandle->pTxBuffer++;
	}else
	{
		//if data size is <= 8bits
		pSPIHandle->pSPIx->DR = *(pSPIHandle->pTxBuffer);
		pSPIHandle->Txlen--;
		pSPIHandle->pTxBuffer++;
	}

	if(!pSPIHandle->Txlen)
	{
		SPI_CloseTransmission(pSPIHandle);
		SPI_ApplicationEventCallback(pSPIHandle, SPI_EVENT_TX_CMPLT);
	}
}
static void spi_rxne_interrupt_handle(SPI_Handle_t *pSPIHandle)
{
	//check the Data Size
	if(((pSPIHandle->pSPIx->CR2 >> SPI_CR2_DS) & 0xF) > 8 )
	{
		//if data size is > 8bits
		(*(uint16_t*)pSPIHandle->pRxBuffer) = pSPIHandle->pSPIx->DR;
		pSPIHandle->Rxlen--;
		pSPIHandle->Rxlen--;
		(uint16_t*)pSPIHandle->pRxBuffer--;
	}else
	{
		//if data size is <= 8bits
		*(pSPIHandle->pRxBuffer) = (uint8_t)pSPIHandle->pSPIx->DR;
		pSPIHandle->Rxlen--;
		pSPIHandle->pRxBuffer--;
	}

	if(!pSPIHandle->Rxlen)
	{
		SPI_CloseReception(pSPIHandle);
		SPI_ApplicationEventCallback(pSPIHandle, SPI_EVENT_RX_CMPLT);
	}

}
static void spi_ovr_err_interrupt_handle(SPI_Handle_t *pSPIHandle)
{
	uint8_t temp;

	if(pSPIHandle->TxState != SPI_BUSY_IN_TX)
	{
		temp = pSPIHandle->pSPIx->DR;
		temp = pSPIHandle->pSPIx->SR;
	}
	(void)temp;
	SPI_ApplicationEventCallback(pSPIHandle, SPI_EVENT_OVR_ERR);

}




void SPI_IRQHandling(SPI_Handle_t *pHandle)
{
	uint8_t temp1, temp2;

	temp1 = pHandle->pSPIx->SR & (1 << SPI_SR_TXE);
	temp2 = pHandle->pSPIx->CR2 & (1 << SPI_CR2_TXEIE);

	if(temp1 && temp2)
	{
		spi_txe_interrupt_handle(pHandle);
	}

	temp1 = pHandle->pSPIx->SR & (1 << SPI_SR_RXNE);
	temp2 = pHandle->pSPIx->CR2 & (1 << SPI_CR2_RXNEIE);

	if(temp1 && temp2)
	{
		spi_rxne_interrupt_handle(pHandle);
	}

	temp1 = pHandle->pSPIx->SR & (1 << SPI_SR_OVR);
	temp2 = pHandle->pSPIx->CR2 & (1 << SPI_CR2_ERRIE);

	if(temp1 && temp2)
	{
		spi_ovr_err_interrupt_handle(pHandle);
	}

}



void SPI_IRQInterruptConfig(uint8_t IRQNumber,uint8_t EnorDi)
{
	if (EnorDi == ENABLE)
	{
		if(IRQNumber <= 31)
		{
			//program ISER0 reg
			*NVIC_ISER0 |= ( 1 << IRQNumber);

		}else if (IRQNumber > 31 && IRQNumber < 64)
		{
			//program ISER1 reg
			*NVIC_ISER1 |= ( 1 << IRQNumber % 32);

		}else if (IRQNumber >= 64 && IRQNumber < 96)
		{
			*NVIC_ISER3 |= ( 1 << IRQNumber % 64);
		}
	}else
	{
		if(IRQNumber <= 31)
		{
			*NVIC_ICER0 |= ( 1 << IRQNumber);

		}else if (IRQNumber > 31 && IRQNumber < 64)
		{
			*NVIC_ICER1 |= ( 1 << IRQNumber % 32);

		}else if (IRQNumber >= 64 && IRQNumber < 96)
		{
			*NVIC_ICER3 |= ( 1 << IRQNumber % 64);
		}
	}
}


void SPI_IRQPriorityConfig( uint8_t IRQNumber,uint8_t IRQPriority)
{
	uint8_t iprx = IRQNumber /4;
	uint8_t iprx_section = IRQNumber % 4;

	uint8_t shift_amount = ( 8 * iprx_section) + ( 8 - NO_PR_BITS_IMPLEMENTED);

	*(NVIC_PR_BASE_ADDR + (iprx * 4)) |= (IRQPriority << (8*shift_amount));
}




