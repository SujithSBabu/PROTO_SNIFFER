/*
 * spi_frame_simulate.c
 *
 *  Created on: Aug 13, 2025
 *      Author: Sujith S Babu
 */

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>


/* API For Simulating SPI loopback Tx Data */
uint8_t* spi_fame_simulate()
{
	static uint8_t spi_frame[8];

	for(uint8_t i =0; i < sizeof(spi_frame)/sizeof(spi_frame[0]); i++)
	{
		spi_frame[i] = rand() % 2; //generates 0 or 1;
	}

	return spi_frame;
}
