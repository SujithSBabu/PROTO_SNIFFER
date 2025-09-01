/*
 * circular_buffer.c
 *
 *  Created on: Aug 13, 2025
 *      Author: Sujith S Babu
 */
#include <stdint.h>
#include <stdbool.h>
#include "circular_buffer.h"
#include "stm32f407_xx_MemMap.h"

circular_buffer circ_buffer;

circular_buffer_i2c_gyro gyro_buffer[BUFFER_SIZE];
circular_buffer_i2c_gyro circ_buffer_i2c_gyro;


/* Circular Buffer To Handle SPI loop back Data */
void cb_init(circular_buffer* pCB)
{
	pCB->head = 0;
	pCB->tail = 0;
}

bool cb_push(circular_buffer* pCB,uint8_t data_write)
{
	if(!((pCB->head +1) % BUFFER_SIZE == pCB->tail))
	{
		pCB->buffer[pCB->head] = data_write;
		pCB->head = (pCB->head + 1) % BUFFER_SIZE;
		return true;
	}
	return false;
}

void cb_pop(circular_buffer* pCB,uint8_t* data_read)
{
	if(pCB->head != pCB->tail)
	{
		*data_read = pCB->buffer[pCB->tail];
		pCB->tail = (pCB->tail + 1) % BUFFER_SIZE;
	}
}


/* Circular Buffer To Handle I2C-accel Sensor Data */
void cb_gyro_init(circular_buffer_i2c_gyro* pCBgyro)
{
	pCBgyro->head = 0;
	pCBgyro->tail = 0;
}

void cb_push_gyro(uint16_t accel_x, uint16_t accel_y, uint16_t accel_z)
{
	if(!(((circ_buffer_i2c_gyro.head + 1)% BUFFER_SIZE) == circ_buffer_i2c_gyro.tail))
	{
	  gyro_buffer[circ_buffer_i2c_gyro.head].accel_x = accel_x;
	  gyro_buffer[circ_buffer_i2c_gyro.head].accel_y = accel_y;
	  gyro_buffer[circ_buffer_i2c_gyro.head].accel_z = accel_z;

	  circ_buffer_i2c_gyro.head = (circ_buffer_i2c_gyro.head + 1) % BUFFER_SIZE;
	}
}
void cb_pop_gyro(circular_buffer_i2c_gyro *data)
{

	if(circ_buffer_i2c_gyro.head != circ_buffer_i2c_gyro.tail)
	{
	    *data = gyro_buffer[circ_buffer_i2c_gyro.tail];
	     circ_buffer_i2c_gyro.tail = (circ_buffer_i2c_gyro.tail + 1) % BUFFER_SIZE;
	}
}
