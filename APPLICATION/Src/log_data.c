/*
 * log_data.c
 *
 *  Created on: Aug 14, 2025
 *      Author: Sujith S Babu
 */

#include "log_data.h"
extern circular_buffer circ_buffer;
extern circular_buffer_i2c_gyro circ_buffer_i2c_gyro;
circular_buffer_i2c_gyro i2c_gyro_data_store;

uint16_t lsb_Sensitivity = 16384; //AFS_SEL = 0(default,so ±2 g)
uint16_t accel_gravity    = 981; // 9.81 * 100
USART_RegDef_Struct* pusart2 = USART2;

/* API to log SPI Loop Back Data */
void log_data(uint32_t tx_frame)
{
   uint8_t data_read;
   cb_pop(&circ_buffer,&data_read);
   usart_send_string(pusart2, "RX: ");
   usart_send_hex(pusart2, (uint32_t)data_read);
   if((uint32_t)data_read == tx_frame)
   {
	 usart_send_string(pusart2, "   [PASS]");
   }
   else
   {
	 usart_send_string(pusart2, "   [FAIL]");
   }
   usart_send_string(pusart2, "\r\n");
}

/* API to log I2C Accel sensor Data */
void i2c_gyro_log_data()
{
   cb_pop_gyro(&i2c_gyro_data_store);
   usart_send_string(pusart2, "[ACCEL Sensor-Linear Acceleration] ");
   usart_send_string(pusart2, "X-Axix[");
   usart_send_hex(pusart2, (uint32_t)i2c_gyro_data_store.accel_x);
   usart_send_string(pusart2, "]: ");
   usart_send_string(pusart2, "Y-Axix[");
   usart_send_hex(pusart2, (uint32_t)i2c_gyro_data_store.accel_y);
   usart_send_string(pusart2, "]: ");
   usart_send_string(pusart2, "Z-Axix[");
   usart_send_hex(pusart2, (uint32_t)i2c_gyro_data_store.accel_z);
   usart_send_string(pusart2, "]");
   usart_send_string(pusart2, "\r\n");
}
