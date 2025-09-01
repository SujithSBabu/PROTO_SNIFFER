/*
 * uart.h
 *
 *  Created on: Aug 10, 2025
 *      Author: Sujith S Babu
 */

#ifndef ECUAL_INC_UART_H_
#define ECUAL_INC_UART_H_

#include "stm32f407_xx_MemMap.h"

/* Function prototypes- Abstraction layer */
void usart_init(void);
void usart_send_char(USART_RegDef_Struct*, char);
void usart_send_string(USART_RegDef_Struct*, char*);
void usart_send_hex(USART_RegDef_Struct*, uint32_t);

#endif /* ECUAL_INC_UART_H_ */
