/*
 * peripheral_clock.c
 *
 *  Created on: Aug 2, 2025
 *      Author: Sujith S Babu
 */

#include "peripheral_clock.h"
uint16_t ahbp_array[8]  = {2,4,8,16,64,128,256,512};
uint8_t apb1p_array[4] = {2,4,8,16};

/*API to fetch and calculate peripheral clock speed*/
uint32_t get_pclk_value(void)
{
	uint32_t pclk,system_clock;
	uint8_t clksrc,temp_ahb,ahbp,temp_apb1,apb1p;
	clksrc = ((RCC->CFGR >> 2) & 0x3);

	if(clksrc == 0)
	{
		system_clock = 16000000;
	}
	else if(clksrc == 1)
	{
		system_clock = 8000000; //why?
	}
	else if(clksrc == 2)
	{
		RCC_GetPLL_Output_Clk();
	}

    /*AHB pre-scalar*/
	temp_ahb = ((RCC->CFGR >> 4) & 0xF);
	if(temp_ahb < 8)
	{
		ahbp = 1;
	}
	else
	{
		ahbp = ahbp_array[temp_ahb-8];
	}

	/*APB1 Pre-Scalar */
	temp_apb1 = ((RCC->CFGR >> 10) & 0x7);
	if(temp_apb1 < 4)
	{
		apb1p = 1;
	}
	else
	{
		apb1p = apb1p_array[temp_apb1-4];
	}

	pclk = ((system_clock/ahbp))/apb1p;
	return pclk;

}

void RCC_GetPLL_Output_Clk(void)
{
	//ToDo
	return;
}
