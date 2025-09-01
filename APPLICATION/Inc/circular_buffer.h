/*
 * circular_buffer.h
 *
 *  Created on: Aug 13, 2025
 *      Author: Sujith S Babu
 */

#ifndef INC_CIRCULAR_BUFFER_H_
#define INC_CIRCULAR_BUFFER_H_
#include <stdint.h>
#include <stdbool.h>

#define BUFFER_SIZE 64
/*Circular Buffer Structure for handling SPI loop back data*/
typedef struct
{
	uint8_t buffer[BUFFER_SIZE];
	volatile uint8_t head;
	volatile uint8_t tail;
}circular_buffer;

/*Circular Buffer Structure for handling I2C-Gyro data */
typedef struct
{
	//uint8_t gyro_buffer[BUFFER_SIZE];
	volatile uint8_t head;
	volatile uint8_t tail;
	uint16_t accel_x;
	uint16_t accel_y;
	uint16_t accel_z;
}circular_buffer_i2c_gyro;

extern circular_buffer_i2c_gyro gyro_buffer[BUFFER_SIZE];

/*Function Prototype*/
void cb_init(circular_buffer*);
bool cb_push(circular_buffer*,uint8_t);
void cb_pop(circular_buffer*,uint8_t*);

void cb_gyro_init(circular_buffer_i2c_gyro*);
void cb_push_gyro(uint16_t accel_x, uint16_t accel_y, uint16_t accel_z);
void cb_pop_gyro(circular_buffer_i2c_gyro*);

#endif /* INC_CIRCULAR_BUFFER_H_ */
