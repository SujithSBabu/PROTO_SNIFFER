/*
 * uart_stm32.h
 *
 *  Created on: Aug 10, 2025
 *      Author: Sujith S Babu
 */

#ifndef MCAL_INC_UART_STM32_H_
#define MCAL_INC_UART_STM32_H_

#include "stm32f407_xx_MemMap.h"

extern volatile char usart_command;

/* Function prototypes - MCAL*/
void usart_stm32_init(void);
void usart_set_baudrate(USART_RegDef_Struct*);
uint32_t get_pclk_value(void);
void usart_stm32_send_char(USART_RegDef_Struct*, char);
void usart_stm32_send_string(USART_RegDef_Struct*, char*);
void usart_stm32_send_hex(USART_RegDef_Struct*, uint32_t);
void enable_usart2_irq(void);

#endif /* MCAL_INC_UART_STM32_H_ */
