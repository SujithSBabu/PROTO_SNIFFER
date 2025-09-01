/*
 * spi.h
 *
 *  Created on: Aug 11, 2025
 *      Author: Sujith S Babu
 */

#ifndef INC_SPI_H_
#define INC_SPI_H_

#include "stm32f407_xx_MemMap.h"
#include "spi_stm32.h"

/*Function Prototypes*/
void spi_init();
void spi_send_frame(uint8_t*,SPI_RegDef_Struct*);

#endif /* INC_SPI_H_ */
