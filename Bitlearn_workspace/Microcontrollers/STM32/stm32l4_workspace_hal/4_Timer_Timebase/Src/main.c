#include <stdio.h>
#include "stm32l4xx_hal.h"
#include "uart.h"
#include "adc.h"
#include "tim.h"


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	//do
	printf("A second just elapsed \n\r");
}





int main() {

	HAL_Init();
	tim_timebase_init();
	uart2_init();

	while (1) {

	}
}

void SysTick_Handler(void)
{
	HAL_IncTick();
}







