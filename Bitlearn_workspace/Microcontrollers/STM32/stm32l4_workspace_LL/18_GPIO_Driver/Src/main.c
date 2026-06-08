
#include "stm32l476xx.h"
#include "stm32l476xx_gpio_drivers.h"
#include <inttypes.h>

//USR_LED = PA5 --> AHB2 EN bit 0
//USR_BUTTON = PC13 --> AHB2 EN bit 2

#define LED_PORT GPIOA
#define LED_PIN 5

GPIO_Handle_t Gpioled;

void delay_us(uint32_t us);

void GPIO_Inits(void)
{
	Gpioled.pGPIOx = LED_PORT;
	Gpioled.GPIO_PinConfig.GPIO_PinNumber =LED_PIN;
	Gpioled.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUTPUT;
	Gpioled.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	Gpioled.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	Gpioled.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	GPIO_PeriClockControl(LED_PORT,ENABLE);
	GPIO_Init(&Gpioled);

}



int main()
{

    GPIO_Inits();

	while (1) {
		GPIO_WriteToOutputPin(LED_PORT, LED_PIN, GPIO_PIN_RESET);
		delay_us(10000);
		GPIO_WriteToOutputPin (LED_PORT, LED_PIN, GPIO_PIN_SET);

	}
}


