/*
 * stm32l476xx_gpio_driver.c
 */
#include "stm32l476xx_gpio_drivers.h"


/* -------- CLOCK CONTROL -------- */

void GPIO_PeriClockControl(GPIO_TypeDef *pGPIOx, uint8_t En_or_Dis) {
	if (En_or_Dis == ENABLE) {
		if (pGPIOx == GPIOA)
			GPIOA_CLK_EN();
		else if (pGPIOx == GPIOB)
			GPIOB_CLK_EN();
		else if (pGPIOx == GPIOC)
			GPIOC_CLK_EN();
		else if (pGPIOx == GPIOD)
			GPIOD_CLK_EN();
		else if (pGPIOx == GPIOE)
			GPIOE_CLK_EN();
		else if (pGPIOx == GPIOF)
			GPIOF_CLK_EN();
		else if (pGPIOx == GPIOG)
			GPIOG_CLK_EN();
		else if (pGPIOx == GPIOH)
			GPIOH_CLK_EN();
	} else {
		if (pGPIOx == GPIOA)
			GPIOA_CLK_DI();
		else if (pGPIOx == GPIOB)
			GPIOB_CLK_DI();
		else if (pGPIOx == GPIOC)
			GPIOC_CLK_DI();
		else if (pGPIOx == GPIOD)
			GPIOD_CLK_DI();
		else if (pGPIOx == GPIOE)
			GPIOE_CLK_DI();
		else if (pGPIOx == GPIOF)
			GPIOF_CLK_DI();
		else if (pGPIOx == GPIOG)
			GPIOG_CLK_DI();
		else if (pGPIOx == GPIOH)
			GPIOH_CLK_DI();
	}
}

/* -------- INIT -------- */

void GPIO_Init(GPIO_Handle_t *pGPIOHandle) {
	GPIO_PeriClockControl(pGPIOHandle->pGPIOx, ENABLE);

	uint32_t temp = 0;
	uint32_t pin = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber;

	/* -------- 1. MODE -------- */
	if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG) {
		temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << (2 * pin));
		pGPIOHandle->pGPIOx->MODER &= ~(0x3 << (2 * pin));
		pGPIOHandle->pGPIOx->MODER |= temp;
	} else {
		/* interrupt mode â†’ set as input */
		pGPIOHandle->pGPIOx->MODER &= ~(0x3 << (2 * pin));

		/* -------- Trigger config -------- */
		if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_FT) {
			EXTI->FTSR1 |= (1 << pin);
			EXTI->RTSR1 &= ~(1 << pin);
		} else if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RT) {
			EXTI->RTSR1 |= (1 << pin);
			EXTI->FTSR1 &= ~(1 << pin);
		} else if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RFT) {
			EXTI->RTSR1 |= (1 << pin);
			EXTI->FTSR1 |= (1 << pin);
		}

		/* -------- SYSCFG -------- */
		SYSCFG_CLK_ENABLE();

		uint8_t portcode = 0;

		if (pGPIOHandle->pGPIOx == GPIOA)
			portcode = 0;
		else if (pGPIOHandle->pGPIOx == GPIOB)
			portcode = 1;
		else if (pGPIOHandle->pGPIOx == GPIOC)
			portcode = 2;
		else if (pGPIOHandle->pGPIOx == GPIOD)
			portcode = 3;
		else if (pGPIOHandle->pGPIOx == GPIOE)
			portcode = 4;
		else if (pGPIOHandle->pGPIOx == GPIOF)
			portcode = 5;
		else if (pGPIOHandle->pGPIOx == GPIOG)
			portcode = 6;
		else if (pGPIOHandle->pGPIOx == GPIOH)
			portcode = 7;

		uint8_t index = pin / 4;
		uint8_t pos = pin % 4;

		SYSCFG->EXTICR[index] &= ~(0xF << (4 * pos));
		SYSCFG->EXTICR[index] |= (portcode << (4 * pos));

		/* -------- Unmask -------- */
		EXTI->IMR1 |= (1 << pin);
	}

	/* -------- SPEED -------- */
	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed << (2 * pin));
	pGPIOHandle->pGPIOx->OSPEEDR &= ~(0x3 << (2 * pin));
	pGPIOHandle->pGPIOx->OSPEEDR |= temp;

	/* -------- PUPD -------- */
	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl << (2 * pin));
	pGPIOHandle->pGPIOx->PUPDR &= ~(0x3 << (2 * pin));
	pGPIOHandle->pGPIOx->PUPDR |= temp;

	/* -------- OUTPUT TYPE -------- */
	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType << pin);
	pGPIOHandle->pGPIOx->OTYPER &= ~(1 << pin);
	pGPIOHandle->pGPIOx->OTYPER |= temp;

	/* -------- ALTERNATE FUNCTION -------- */
	if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALTFN) {
		uint32_t index = pin / 8;
		uint32_t pos = pin % 8;
		uint32_t af = pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode;

		pGPIOHandle->pGPIOx->AFR[index] &= ~(0xF << (4 * pos));
		pGPIOHandle->pGPIOx->AFR[index] |= (af << (4 * pos));
	}
}

/* -------- DEINIT -------- */

void GPIO_DeInit(GPIO_TypeDef *pGPIOx) {
	if (pGPIOx == GPIOA)
		GPIOA_REG_RESET();
	else if (pGPIOx == GPIOB)
		GPIOB_REG_RESET();
	else if (pGPIOx == GPIOC)
		GPIOC_REG_RESET();
	else if (pGPIOx == GPIOD)
		GPIOD_REG_RESET();
	else if (pGPIOx == GPIOE)
		GPIOE_REG_RESET();
	else if (pGPIOx == GPIOF)
		GPIOF_REG_RESET();
	else if (pGPIOx == GPIOG)
		GPIOG_REG_RESET();
	else if (pGPIOx == GPIOH)
		GPIOH_REG_RESET();

}

/* -------- READ -------- */

uint8_t GPIO_ReadFromInputPin(GPIO_TypeDef *pGPIOx, uint8_t PinNumber) {
	return (uint8_t) ((pGPIOx->IDR >> PinNumber) & 0x1);
}


uint16_t GPIO_ReadFromInputPort(GPIO_TypeDef *pGPIOx) {
	return (uint16_t) (pGPIOx->IDR);
}

/* -------- WRITE -------- */

void GPIO_WriteToOutputPin(GPIO_TypeDef *pGPIOx, uint8_t PinNumber,
		uint8_t Value) {
	if (Value == GPIO_PIN_SET)
		pGPIOx->BSRR = (1 << PinNumber);
	else
		pGPIOx->BSRR = (1 << (PinNumber + 16));
}


void GPIO_WriteToOutputPort(GPIO_TypeDef *pGPIOx, uint16_t Value) {
	pGPIOx->ODR = Value;
}


void GPIO_ToggleOutputPin(GPIO_TypeDef *pGPIOx, uint8_t PinNumber) {
	pGPIOx->ODR ^= (1 << PinNumber);
}


void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t En_or_Dis) {
	if (En_or_Dis) {
		if (IRQNumber <= 31)
			NVIC_ISER0 |= (1 << IRQNumber);
		else if (IRQNumber < 64)
			NVIC_ISER1 |= (1 << (IRQNumber % 32));
		else if (IRQNumber < 96)
			NVIC_ISER2 |= (1 << (IRQNumber % 32));

	} else {
		if (IRQNumber <= 31)
			NVIC_ICER0 |= (1 << IRQNumber);
		else if (IRQNumber < 64)
			NVIC_ICER1 |= (1 << (IRQNumber % 32));
		else if (IRQNumber < 96)
			NVIC_ICER2 |= (1 << (IRQNumber % 32));
	}

	/* Set priority */
	uint8_t iprx = IRQNumber / 4;
	uint8_t section = IRQNumber % 4;

	NVIC_IPR[iprx] &= ~(0xFF << (8 * section));     // clear
	NVIC_IPR[iprx] |= (IRQPriority << (8 * section));
}


void GPIO_IRQHandling(uint8_t PinNumber) {
	if (EXTI->PR1 & (1 << PinNumber)) {
		EXTI->PR1 |= (1 << PinNumber); // clear pending
	}
}


void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority)
{
    uint8_t iprx = IRQNumber / 4;      // which IPR register
    uint8_t section = IRQNumber % 4;   // which section inside register

    uint8_t shift = (8 * section) + 4; // STM32 uses upper 4 bits

    /* Clear old priority */
    NVIC_IPR[iprx] &= ~(0xF << shift);

    /* Set new priority */
    NVIC_IPR[iprx] |= (IRQPriority << shift);
}
