/*
 * i2c_stm32.h
 *
 *  Created on: Aug 15, 2025
 *      Author: Sujith S Babu
 */

#ifndef INC_I2C_STM32_H_
#define INC_I2C_STM32_H_
#include "stm32f407_xx_MemMap.h"
#include "peripheral_clock.h"

/*Function Prototypes - MCAL */
void i2c_stm32_init();
void i2c_stm32_master_write_data();
uint8_t i2c_stm32_master_read_data(uint8_t, uint8_t);
void I2C1_irq_enable(void);

#endif /* INC_I2C_STM32_H_ */
