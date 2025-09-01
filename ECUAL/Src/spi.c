/*
 * spi.c
 *
 *  Created on: Aug 11, 2025
 *      Author: Sujith S Babu
 */
#include "spi.h"


/*Abstraction layer API to handle SPI initialization */
void spi_init()
{
	spi_stm32_init();
}

/*Abstraction layer API to send TX loop back frame */
void spi_send_frame(uint8_t* pSPI_Frame,SPI_RegDef_Struct* pSPI2)
{
	spi_stm32_send_frame(pSPI_Frame,pSPI2);
}
