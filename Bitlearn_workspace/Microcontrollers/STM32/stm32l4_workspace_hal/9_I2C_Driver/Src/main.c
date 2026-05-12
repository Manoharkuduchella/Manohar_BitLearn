#include "stm32l4xx_hal.h"
#include "uart.h"
#include "adc.h"
#include <stdio.h>
#include "BME280_STM32.h"
#include "main.h"

#define DEVICE_ID_R 	0xD0
#define DEVICE_ID 		0x60

void SysTick_Handler(void);
void i2c2_init(void);


I2C_HandleTypeDef hi2c2;

float Temperature, Pressure, Humidity;

int flag =0;

uint8_t chip_id = 0;


HAL_StatusTypeDef ret;

int main() {


	HAL_Init();

	i2c2_init();


	if (BME280_Config(OSRS_2, OSRS_16, OSRS_1, MODE_NORMAL, T_SB_0p5, IIR_16) != 0)
	{
		Error_Handler();

	}

	while (1) {

		BME280_Measure(&Temperature, &Pressure, &Humidity);
		HAL_Delay (500);
	}
}


/*
 * I2C_SCL -> PB11
 * I2C_SDA -> PB10
 *
 * */


void i2c2_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_11;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;

	HAL_GPIO_Init(GPIOB,&GPIO_InitStruct);


	//COnfigure I2C

	__HAL_RCC_I2C1_CLK_ENABLE();

	hi2c2.Instance = I2C2;
	hi2c2.Init.Timing = 0x00100D14;//for PCLK 4Mhz - i2c speed 100khz
	hi2c2.Init.OwnAddress1 = 0;
	hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	hi2c2.Init.OwnAddress2 =0;
	hi2c2.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
	hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;

	if (HAL_I2C_Init(&hi2c2) != HAL_OK)
	{
	    Error_Handler();
	}

	  /** Configure Analogue filter
	  */
	  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c2, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
	  {
	    Error_Handler();
	  }

	  /** Configure Digital filter
	  */
	  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c2, 0) != HAL_OK)
	  {
	    Error_Handler();
	  }

}


void SysTick_Handler(void) {
	HAL_IncTick();
}


/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}


