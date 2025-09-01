/*
 * i2c.h
 *
 *  Created on: Aug 15, 2025
 *      Author: Sujith S Babu
 */

#ifndef INC_I2C_H_
#define INC_I2C_H_

#include "stm32f407_xx_MemMap.h"
#include "i2c_stm32.h"

/*Function Prototypes*/
void i2c_init();
void i2c_master_send_data();
uint8_t i2c_master_read_data(uint8_t, uint8_t);

#endif /* INC_I2C_H_ */
