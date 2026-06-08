/*
 * exti.h
 *
 *  Created on: Apr 28, 2026
 *      Author: manohar kuduchella
 */

#ifndef EXTI_H_
#define EXTI_H_

void gpio_pc13_interrupt_init(void);
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
void EXTI15_10_IRQHandler(void);

#endif /* EXTI_H_ */
