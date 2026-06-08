
#include "stm32l476xx.h"
#include "stm32l476xx_gpio_drivers.h"

//USR_LED = PA5 --> AHB2 EN bit 0
//USR_BUTTON = PC13 --> AHB2 EN bit 2

GPIO_Handle_t GpioBtn;

volatile uint8_t button_pressed = 0;

void EXTI15_10_IRQHandler(void)
{
    GPIO_IRQHandling(13);
    button_pressed = 1;
}

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



int main()
{

    GPIO_Inits();

	while (1) {

	}
}


