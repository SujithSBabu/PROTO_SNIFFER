/*
 * uart_stm32.c
 *
 *  Created on: Aug 10, 2025
 *      Author: Sujith S Babu
 */

/* header file inclusions */
#include "uart_stm32.h"

volatile char usart_command = 0;

/* API to handle the stm32 usart2 initialization - MCAL */
void usart_stm32_init()
{
	    USART2_CLK_EN();

		enable_usart2_irq();//To Enable USART2 interrupt in NVIC_ISER1

		USART_RegDef_Struct* pUsart = USART2;

		/*Setting up CR1 register */

		pUsart->USART_CR1 &= ~(1U<<13);//clearing UE bit in CR1
		usart_set_baudrate(pUsart);


		pUsart->USART_CR1 &= ~(1U<<2);//clearing RE bit in CR1
		pUsart->USART_CR1 |=  (1U<<2);//setting up RE bit in CR1

		pUsart->USART_CR1 &= ~(1U<<3);//clearing TE bit in CR1
		pUsart->USART_CR1 |=  (1U<<3);//setting up TE bit in CR1

		pUsart->USART_CR1 &= ~(1U<<5);//clearing RXNEIE
		pUsart->USART_CR1 |=  (1U<<5);//setting RXNEIE bit in CR1

		pUsart->USART_CR1 |=  (1U<<13);//setting up UE bit in CR1

}

/*API to set the baud rate register for USART2 */
void usart_set_baudrate(USART_RegDef_Struct* pUsart2)
{
	uint32_t pclkx,usart_div,M_Part,F_Part;
	uint32_t temp_reg = 0;

	/*API call to fetch peripheral clock value*/
	pclkx = get_pclk_value();

	if(pUsart2->USART_CR1 & (1<<15))
	{
		usart_div = (25 * pclkx)/ (2 * 9600);  //floating point math is expensive in embedded systems,so multiplied by 100.
	}
	else
	{
		usart_div = (25 * pclkx)/ (4 * 9600); //floating point math is expensive in embedded systems,so multiplied by 100.
	}

	/* Calculate mantissa part */
	M_Part = usart_div/100;

	temp_reg |= M_Part << 4;

	/* Calculate fractional part */
	F_Part = usart_div - (M_Part * 100);

	/* Calculate the final fractional part */
	if(pUsart2->USART_CR1 & (1<< 15))
	{
		F_Part = (((F_Part * 8) + 50)/100) & (0x7);//adding 50 to get the correct nearest value
	}
	else
	{
		F_Part = (((F_Part * 16) + 50)/100) & (0x0F);//adding 50 to get the correct nearest value
	}
    temp_reg |= F_Part;

    /* set USART BRR register */
    pUsart2->USART_BRR = temp_reg;
}


/*API to handle transmission of a character*/
void usart_stm32_send_char(USART_RegDef_Struct* pUSART,char ch)
{
	/* wait until TXE flag is set */
	while(!(pUSART->USART_SR & (1 << 7)));
	pUSART->USART_DR = ch;
	/* wait until whole transmission completes */
	while(!(pUSART->USART_SR & (1 << 6)));
}

/*API to handle transmission of a string*/
void usart_stm32_send_string(USART_RegDef_Struct* pUsart,char* pStr)
{
	while(*pStr)
	{
		usart_send_char(pUsart,*(pStr++));
	}
}

/*API to handle transmission of a hex value*/
void usart_stm32_send_hex(USART_RegDef_Struct* pUSARTx, uint32_t hex_value)
{
	char hex_char = '0' ;
	usart_send_string(pUSARTx, "0x");
	for(int8_t i = 28; i >= 0; i-=4)
	{
		uint8_t nibble = (hex_value >> i) & 0xF;
		if(nibble < 10)
		{
		  hex_char = '0' + nibble;
		}
		else if(nibble > 10)
		{
			hex_char = 'A' + (nibble - 10);
		}

		usart_send_char(pUSARTx, hex_char);
	}
}

/*API to enable USART2 interrupt*/
void enable_usart2_irq(void)
{
    NVIC_ISER1 = (1 << (38-32)); //Enable USART2 interrupt (Irq 38)
}

/*USART2 IRQ handler*/
void USART2_IRQHandler(void)
{
    USART_RegDef_Struct* pusart2 = USART2;
	while(!(pusart2->USART_SR & (1 << 5)));//Wait until RXE flag is set
	usart_command = pusart2->USART_DR;

}
