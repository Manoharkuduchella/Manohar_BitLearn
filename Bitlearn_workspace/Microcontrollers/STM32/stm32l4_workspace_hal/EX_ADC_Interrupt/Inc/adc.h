/*
 * adc.h
 *
 *  Created on: Apr 27, 2026
 *      Author: manohar kuduchella
 */

#ifndef ADC_H_
#define ADC_H_

uint32_t pa0_adc_read(void);
void adc_init_start(void);
void adc_pa0_single_conv_init(void);
void adc_pa0_interrupt_init(void);
#endif /* ADC_H_ */
