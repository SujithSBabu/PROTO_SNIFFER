/*
 * spi_stm32.c
 *
 *  Created on: Aug 11, 2025
 *      Author: Sujith S Babu
 */
#include "spi_stm32.h"
#include "circular_buffer.h"
#include "log_data.h"

extern circular_buffer circ_buffer;
USART_RegDef_Struct* pUsart2 = USART2;

uint8_t spi_frame = 0;

/* API to handle stm32 SPI2 initializations - MCAL */
void spi_stm32_init()
{

	/* SPI peripheral clock enable */
    SPI2_CLK_EN();

    /*Pointer initialization*/
    SPI_RegDef_Struct* pSpi2 = SPI2;

	/*SPI CR1 register configuration */
    pSpi2->SPI_CR1 = 0;
    /* Peripheral disable configuration */
    pSpi2->SPI_CR1 &= ~(1<<6);

    /* CPHA configuration */
    pSpi2->SPI_CR1 &= ~(1<<0);

    /*CPOL configuration */
    pSpi2->SPI_CR1 &= ~(1<<1);

    /*MASTER mode configuration*/
    pSpi2->SPI_CR1 &= ~(1<<2);
    pSpi2->SPI_CR1 |=  (1<<2);

    /* Baud rate configuration */
    pSpi2->SPI_CR1 &= ~(7<<3);
    pSpi2->SPI_CR1 |=  (4<<3);

    /*SW slave management */
    pSpi2->SPI_CR1 &= ~(1<<9);
    pSpi2->SPI_CR1 |=  (1<<9);

    /* Internal slave select */
    pSpi2->SPI_CR1 &= ~(1<<8);
    pSpi2->SPI_CR1 |=  (1<<8);

    /* RX interrupt configuration SPI_CR2 */
    pSpi2->SPI_CR2 &= ~(1<<6);
    pSpi2->SPI_CR2 |=  (1<<6);

    /* Peripheral enable configuration */
    pSpi2->SPI_CR1 |=  (1<<6);

    spi2_irq_enable();

}

/* API to transmit 8bits TX loop back frame - MCAL */
void spi_stm32_send_frame(uint8_t* pSpi_Frame, SPI_RegDef_Struct* pSpi2)
{
	spi_frame = 0;

	for(uint8_t i=0; i < 8;i++)
     {
		spi_frame |= ((pSpi_Frame[i] & 1) << (7-i)); //MSB is transmitted first
     }

    usart_send_string(pUsart2, "TX: ");
	usart_send_hex(pUsart2, (uint32_t)spi_frame);
	usart_send_string(pUsart2, "   ");

	while(!(pSpi2->SPI_SR & (1<<1))); //Wait till TXE flag is set to make sure TX buffer is empty.
	pSpi2->SPI_DR = spi_frame;
	while(pSpi2->SPI_SR & (1<<7)); //Wait till Busy flag is cleared to make sure SPI communication is not busy.
}

/* API to enable IrQ for SPI2 in ISER1 - MCAL */
void spi2_irq_enable()
{
	NVIC_ISER1 |= (1<<(36-32)); //Enable SPI2 interrupt (irq=36)
}

/* API to handle SPI2 RX interrupts - MCAL */
void SPI2_IRQHandler()
{
	bool flag = false;
	SPI_RegDef_Struct* pSPI2 = SPI2;
	if(pSPI2->SPI_SR & (1<<0))
	{
	 uint8_t spi_frame_8 = (uint8_t)pSPI2->SPI_DR;
     flag = cb_push(&circ_buffer,spi_frame_8);
	}
	if(flag == true)
	{
      log_data(spi_frame); //to log the data stored in the circular buffer
	}
}
