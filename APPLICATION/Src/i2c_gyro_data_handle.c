/*
 * i2c_gyro_data_handle.c
 *
 *  Created on: Aug 31, 2025
 *      Author: sujit
 */

#include "i2c_gyro_data_handle.h"
#include "circular_buffer.h"
#include "log_data.h"


circular_buffer_i2c_gyro gyro_struct_data;

/*API to call i2c_master_read_data with different register addresses for reading liner acceleration */
void i2c_gyro_sensor_read(void)
{
	        uint8_t accel_XOUT_H = i2c_master_read_data(0x68, 0x3B);
	        uint8_t accel_XOUT_L = i2c_master_read_data(0x68, 0x3C);
	        uint16_t accel_XOUT  = (int16_t)((accel_XOUT_H<<8) | accel_XOUT_L);

	        uint8_t accel_YOUT_H = i2c_master_read_data(0x68, 0x3D);
	        uint8_t accel_YOUT_L = i2c_master_read_data(0x68, 0x3E);
	        uint16_t accel_YOUT  = (int16_t)((accel_YOUT_H<<8) | accel_YOUT_L);

			uint8_t accel_ZOUT_H = i2c_master_read_data(0x68, 0x3F);
			uint8_t accel_ZOUT_L = i2c_master_read_data(0x68, 0x40);
			uint16_t accel_ZOUT  = (int16_t)((accel_ZOUT_H<<8) | accel_ZOUT_L);

			cb_push_gyro(accel_XOUT, accel_YOUT, accel_ZOUT);

			i2c_gyro_log_data();
}
