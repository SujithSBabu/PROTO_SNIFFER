/*
 * spi_stm32.h
 *
 *  Created on: Aug 11, 2025
 *      Author: Sujith S Babu
 */

#ifndef INC_SPI_STM32_H_
#define INC_SPI_STM32_H_
#include "stm32f407_xx_MemMap.h"
#include "uart_stm32.h"

/*Function Prototypes - MCAL*/
void spi_stm32_init();
void spi2_irq_enable();
void spi_stm32_send_frame(uint8_t*,SPI_RegDef_Struct*);

#endif /* INC_SPI_STM32_H_ */
