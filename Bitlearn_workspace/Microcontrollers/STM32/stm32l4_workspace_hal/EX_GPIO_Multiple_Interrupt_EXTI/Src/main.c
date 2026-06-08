#include <stdio.h>
#include "stm32l4xx_hal.h"
#include "uart.h"
//USR_BUTTON = PC13 --> AHB2 EN bit 2
#define BTN_PORT GPIOC
#define BTN_PIN GPIO_PIN_13

#define LED_PORT GPIOA
#define LED_PIN GPIO_PIN_5

void gpio_pc13_interrupt_init(void);
void pa5_led_init(void);

int main() {

	HAL_Init();
	uart2_init();

	pa5_led_init();
	gpio_pc13_interrupt_init();

	while (1) {

	}
}

void SysTick_Handler(void) {
	HAL_IncTick();
}



void gpio_pc13_interrupt_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	__HAL_RCC_GPIOC_CLK_ENABLE();

	//Configure PC13
	GPIO_InitStruct.Pin = BTN_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

	HAL_GPIO_Init(BTN_PORT,&GPIO_InitStruct);

	//Configure PA0
	GPIO_InitStruct.Pin = GPIO_PIN_0;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

	HAL_GPIO_Init(LED_PORT,&GPIO_InitStruct);

	//Configure PA5
	GPIO_InitStruct.Pin = LED_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

	HAL_GPIO_Init(LED_PORT,&GPIO_InitStruct);


	//Configure EXTI

	HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(EXTI0_IRQn);

	HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);


}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	//executing user define code
	if(GPIO_Pin == GPIO_PIN_13)
	{
		HAL_GPIO_TogglePin(LED_PORT, LED_PIN);
		printf("Button 13 pressed \n\r");
	}

	if(GPIO_Pin == GPIO_PIN_0)
	{
		printf("Button 0 pressed \n\r");
	}

}



void EXTI15_10_IRQHandler(void)
{
	HAL_GPIO_EXTI_IRQHandler(BTN_PIN);
}

void EXTI0_IRQHandler(void)
{
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
}

void pa5_led_init(void)
{
	//configure PA5 as output pin
	//Enable clock for GPIOA
	__HAL_RCC_GPIOA_CLK_ENABLE();

	GPIO_InitTypeDef GPIO_InitStruct = {0};

	GPIO_InitStruct.Pin = LED_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

	HAL_GPIO_Init (LED_PORT, &GPIO_InitStruct);

}


