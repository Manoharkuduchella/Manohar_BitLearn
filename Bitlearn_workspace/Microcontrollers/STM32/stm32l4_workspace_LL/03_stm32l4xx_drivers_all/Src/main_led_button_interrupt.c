/*
 * main.c
 *
 *  Created on: May 11, 2026
 *      Author: manohar kuduchella
 */
#include "stm32l476xx.h"
#include "stm32l476xx_gpio_driver.h"
#include<string.h>

void delay(void){
	for(uint32_t i = 0; i < 500000/2; i++){
		;
	}
}


void EXTI15_10_IRQHandler(void)
{
	delay();
	GPIO_IRQHandling(GPIO_PIN_NO_13);
    GPIO_ToggleOutputPin(GPIOA, GPIO_PIN_NO_5);

}


int main()
{

		GPIO_Handle_t GpioLed,GpioBtn;
		memset(&GpioLed,0,sizeof(GpioLed));
	    memset(&GpioBtn,0,sizeof(GpioBtn));
		GpioLed.pGPIOx = GPIOA;
		GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_5;
		GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
		GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
		GpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
		GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

		GPIO_PeriClockControl(GPIOA, ENABLE);
		GPIO_Init(&GpioLed);

		GpioBtn.pGPIOx = GPIOC;
		GpioBtn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
		GpioBtn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_FT;
		GpioBtn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
		GpioBtn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;

		//GPIOA_PCLK_EN();
		//GPIOC_PCLK_EN();

		GPIO_PeriClockControl(GPIOC, ENABLE);

		GPIO_Init(&GpioBtn);

		GPIO_IRQPriorityConfig(IRQ_NO_EXTI15_10, NVIC_IRQ_PRI15);
		GPIO_IRQInterruptConfig(IRQ_NO_EXTI15_10, ENABLE);


		while(1);

	return 0;
}



