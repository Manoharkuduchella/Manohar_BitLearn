/*
 * stm32l476_rcc_driver.c
 *
 *  Created on: May 18, 2026
 *      Author: manohar kuduchella
 */


#include "stm32l476xx_rcc_driver.h"

uint16_t AHB_PreScaler[8] = {2,4,8,16,64,128,256,512};
uint8_t APB1_PreScaler[4] = {2,4,8,16};


uint32_t RCC_GetPCLK1Value(void)
{
	uint32_t pclk1,SystemClk;

	uint8_t clksrc,temp,ahbp,apb1p;

	clksrc = ((RCC->CFGR >> 2) & 0x03);

	if(clksrc == 0)
	{
		SystemClk = 4000000;
	}
	else if(clksrc == 1)
	{
		SystemClk = 16000000;
	}

	//for ahb
	temp = ((RCC->CFGR >> 4) & 0x0F);

	if(temp < 8)
	{
		ahbp =1;
	}else
	{
		ahbp = AHB_PreScaler[temp-8];
	}

	//for apb1
	temp = ((RCC->CFGR >> 8) & 0x07);

	if(temp < 4)
	{
		apb1p = 1;
	}
	else
	{
		apb1p = APB1_PreScaler[temp-4];
	}

	pclk1 = (SystemClk / ahbp)/apb1p;


	return pclk1;

}

uint32_t RCC_GetPCLK2Value(void)
{
    /*
     * If you did not configure clock tree,
     * default MSI clock is usually 4 MHz.
     */
    return 4000000;
}
