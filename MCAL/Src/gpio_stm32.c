/*
 * gpio_stm32.c
 *
 *  Created on: Aug 10, 2025
 *      Author: Sujith S Babu
 */

#include "gpio_stm32.h"

/* API for initializing GPIOA peripheral for enabling USART2 based communication - MCAL */
void gpio_stm32_init(GPIO_Hanlde_Struct* pGpio_cfg)
{

	GPIOA_CLK_EN();
	GPIOB_CLK_EN();


	/*MODER Configuration */
	pGpio_cfg->gpio_reg_def->MODER   &= ~(3U << ((pGpio_cfg->gpio_cfg.gpio_pin)*2));
	pGpio_cfg->gpio_reg_def->MODER   |=  (pGpio_cfg->gpio_cfg.gpio_pin_mode << ((pGpio_cfg->gpio_cfg.gpio_pin)*2));

	/*OTYPE Configuration */
	pGpio_cfg->gpio_reg_def->OTYPER  &= ~(1 << (pGpio_cfg->gpio_cfg.gpio_pin));
	pGpio_cfg->gpio_reg_def->OTYPER  |=  (pGpio_cfg->gpio_cfg.gpio_pin_otype << pGpio_cfg->gpio_cfg.gpio_pin);

	/*OSPEEDR Configuration */
	pGpio_cfg->gpio_reg_def->OSPEEDR &= ~(3U << ((pGpio_cfg->gpio_cfg.gpio_pin)*2));
	pGpio_cfg->gpio_reg_def->OSPEEDR |= (pGpio_cfg->gpio_cfg.gpio_pin_speed << ((pGpio_cfg->gpio_cfg.gpio_pin)*2));

	/*PUPDR Configurations */
	pGpio_cfg->gpio_reg_def->PUPDR   &= ~(3U << ((pGpio_cfg->gpio_cfg.gpio_pin)*2));
	pGpio_cfg->gpio_reg_def->PUPDR   |=  (pGpio_cfg->gpio_cfg.gpio_pin_pupd << ((pGpio_cfg->gpio_cfg.gpio_pin)*2));

	/*AFR Configurations */
    uint8_t AFR_index           =  pGpio_cfg->gpio_cfg.gpio_pin / 8;
    pGpio_cfg->gpio_reg_def->AFR[AFR_index] &= ~(0xF << ((pGpio_cfg->gpio_cfg.gpio_pin%8)*4));
    pGpio_cfg->gpio_reg_def->AFR[AFR_index] |= (pGpio_cfg->gpio_cfg.gpio_alt_func << ((pGpio_cfg->gpio_cfg.gpio_pin%8)*4));

    /* UART initialization call - MCAL */
    usart_init();
}
