#include "stm32l4xx_hal.h"
#include "uart.h"
#include "adc.h"
#include <stdio.h>

void SysTick_Handler(void);

uint32_t sensor_value;


int main() {
	HAL_Init();
	uart2_init();

	adc_init_start();

	while (1) {
		sensor_value = pa0_adc_read();
		HAL_Delay(10);
	}
}

void SysTick_Handler(void) {
	HAL_IncTick();
}



