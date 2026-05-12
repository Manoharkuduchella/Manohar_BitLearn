#include "stm32l4xx_hal.h"

#define BTN_PORT GPIOC
#define BTN_PIN GPIO_PIN_13
#define LED_PORT GPIOA
#define LED_PIN GPIO_PIN_5

//USR_LED = PA5 --> AHB2 EN bit 0
//USR_BUTTON = PC13 --> AHB2 EN bit 2



void pc13_led_init(void)
{
	//configure PC13 as input pin
	//Enable clock for GPIOC
	__HAL_RCC_GPIOC_CLK_ENABLE();

	GPIO_InitTypeDef GPIO_InitStruct = {0};

	GPIO_InitStruct.Pin = BTN_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

	HAL_GPIO_Init(BTN_PORT,&GPIO_InitStruct);

}

void pa5_btn_init(void)
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

void SysTick_Handler(void)
{
	HAL_IncTick();
}



uint8_t buttonStatus;

int main()
{
	HAL_Init();

	pc13_led_init();
	pa5_btn_init();



	while(1)
	{
		buttonStatus = HAL_GPIO_ReadPin (BTN_PORT, BTN_PIN);
		HAL_GPIO_WritePin (LED_PORT, LED_PIN, buttonStatus);
	}
}

