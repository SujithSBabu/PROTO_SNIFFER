/*
 * log_data.h
 *
 *  Created on: Aug 14, 2025
 *      Author: Sujith S Babu
 */

#ifndef INC_LOG_DATA_H_
#define INC_LOG_DATA_H_

#include "stm32f407_xx_MemMap.h"
#include "circular_buffer.h"

/*Function Prototypes*/
void log_data(uint32_t);
void i2c_gyro_log_data();

#endif /* INC_LOG_DATA_H_ */
