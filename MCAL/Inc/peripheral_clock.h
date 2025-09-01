/*
 * peripheral_clock.h
 *
 *  Created on: Aug 2, 2025
 *      Author: Sujith S Babu
 */

#ifndef INC_PERIPHERAL_CLOCK_H_
#define INC_PERIPHERAL_CLOCK_H_

#include "stm32f407_xx_MemMap.h"

/*Function Prototypes - MCAL*/
uint32_t get_pclk_value(void);
void RCC_GetPLL_Output_Clk(void);//ToDo

#endif /* INC_PERIPHERAL_CLOCK_H_ */
