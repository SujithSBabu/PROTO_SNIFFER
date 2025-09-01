/*
 * i2c.c
 *
 *  Created on: Aug 15, 2025
 *      Author: Sujith S Babu
 */

#include "i2c.h"

/*Abstraction layer API to handle I2C initializations*/
void i2c_init()
{
   i2c_stm32_init();
}

/*Abstraction layer API to handle master sending data to slave */
void i2c_master_send_data()
{
	i2c_stm32_master_write_data();
}

/*Abstraction layer API to handle master reading data from slave */
uint8_t i2c_master_read_data(uint8_t sensor_addr_user_input, uint8_t read_reg_addr_user_input)
{
    uint8_t sensor_data = i2c_stm32_master_read_data(sensor_addr_user_input, read_reg_addr_user_input);
    return sensor_data;
}
