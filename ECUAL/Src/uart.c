/*
 * uart.c
 *
 *  Created on: Aug 10, 2025
 *      Author: Sujith S Babu
 */

/* header file inclusions */
#include "uart.h"
#include "uart_stm32.h"

/* UART abstraction layer api's implementation */
void usart_init()
{
	usart_stm32_init();
}

void usart_send_char(USART_RegDef_Struct* pUSART,char ch)
{
	usart_stm32_send_char(pUSART, ch);
}

void usart_send_string(USART_RegDef_Struct* pUsart,char* pStr)
{
	usart_stm32_send_string(pUsart, pStr);
}

void usart_send_hex(USART_RegDef_Struct* pUSARTx, uint32_t hex_value)
{
	usart_stm32_send_hex(pUSARTx, hex_value);
}
