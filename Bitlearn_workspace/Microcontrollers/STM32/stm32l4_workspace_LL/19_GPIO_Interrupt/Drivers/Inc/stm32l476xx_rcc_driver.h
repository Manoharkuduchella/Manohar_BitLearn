/*
 * stm32l476xx_rcc_driver.h
 *
 *  Created on: May 18, 2026
 *      Author: manohar kuduchella
 */

#ifndef INC_STM32L476XX_RCC_DRIVER_H_
#define INC_STM32L476XX_RCC_DRIVER_H_

#include "stm32l476xx.h"
extern uint16_t AHB_PreScaler[8];
extern uint8_t APB1_PreScaler[4];


uint32_t RCC_GetPCLK1Value(void);
uint32_t RCC_GetPCLK2Value(void);

#endif /* INC_STM32L476XX_RCC_DRIVER_H_ */
