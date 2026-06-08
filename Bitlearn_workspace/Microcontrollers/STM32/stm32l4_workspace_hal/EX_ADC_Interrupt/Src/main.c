#include "stm32l4xx_hal.h"
#include "uart.h"
#include "adc.h"
#include <stdio.h>

void SysTick_Handler(void);

ADC_HandleTypeDef hadc1;

uint32_t sensor_value;

int main() {

	HAL_Init();
	uart2_init();

	adc_pa0_interrupt_init();

	//start ADC
	HAL_ADC_Start_IT(&hadc1);

	while (1) {
		printf("The sensor value: %d \n\r",(int)sensor_value);
	}
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
	//user defined code
	//Get conversion
	sensor_value = pa0_adc_read();
	HAL_ADC_Start_IT(&hadc1);
}


void SysTick_Handler(void) {
	HAL_IncTick();
}
