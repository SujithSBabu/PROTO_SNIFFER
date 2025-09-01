/*
 * spi_loopback_feature.c
 *
 *  Created on: Aug 13, 2025
 *      Author: Sujith S Babu
 */

#include "spi_loopback_feature.h"
#include <stdint.h>

/* API to generate SPI loop back Tx frame */
void spi_loopback_test()
{
    SPI_RegDef_Struct* pSPI2 = SPI2;
	uint8_t * Pspi_sim_frame = spi_fame_simulate();
    spi_send_frame(Pspi_sim_frame,pSPI2);
}
