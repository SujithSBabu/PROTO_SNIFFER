/*
 * gpio.c
 *
 *  Created on: Aug 10, 2025
 *      Author: Sujith S Babu
 */

#include "gpio.h"
#include "gpio_stm32.h"

/*GPIO-UART Alternate Function USer Config.*/
GPIO_Hanlde_Struct gpio_uart_cfg[]={

		{.gpio_cfg = {.gpio_pin = GPIO_PIN_2, .gpio_pin_mode = GPIO_ALT_FUNC_MODE, .gpio_pin_speed = GPIO_HIGH_SPEED, .gpio_pin_pupd = GPIO_PIN_PU, .gpio_alt_func = AF7}, .gpio_reg_def = GPIOA},
		{.gpio_cfg = {.gpio_pin = GPIO_PIN_3, .gpio_pin_mode = GPIO_ALT_FUNC_MODE, .gpio_pin_speed = GPIO_HIGH_SPEED, .gpio_pin_pupd = GPIO_PIN_PU, .gpio_alt_func = AF7}, .gpio_reg_def = GPIOA}
};





/*GPIO-SPI Alternate Function user config. */
/* Created array of structure to handle different pin initializations effectively */
GPIO_Hanlde_Struct gpio_spi_cfg[] = {
		{.gpio_cfg = {.gpio_pin = GPIO_PIN_12, .gpio_pin_mode = GPIO_ALT_FUNC_MODE, .gpio_pin_speed = GPIO_HIGH_SPEED, .gpio_pin_pupd = GPIO_PIN_NO_PUPD, .gpio_alt_func = AF5},.gpio_reg_def = GPIOB},
		{.gpio_cfg = {.gpio_pin = GPIO_PIN_13, .gpio_pin_mode = GPIO_ALT_FUNC_MODE, .gpio_pin_speed = GPIO_HIGH_SPEED, .gpio_pin_pupd = GPIO_PIN_NO_PUPD, .gpio_alt_func = AF5},.gpio_reg_def = GPIOB},
		{.gpio_cfg = {.gpio_pin = GPIO_PIN_14, .gpio_pin_mode = GPIO_ALT_FUNC_MODE, .gpio_pin_speed = GPIO_HIGH_SPEED, .gpio_pin_pupd = GPIO_PIN_NO_PUPD, .gpio_alt_func = AF5},.gpio_reg_def = GPIOB},
		{.gpio_cfg = {.gpio_pin = GPIO_PIN_15, .gpio_pin_mode = GPIO_ALT_FUNC_MODE, .gpio_pin_speed = GPIO_HIGH_SPEED, .gpio_pin_pupd = GPIO_PIN_NO_PUPD, .gpio_alt_func = AF5},.gpio_reg_def = GPIOB}

};

/*GPIO-I2C Alternate Function user config. */
/* Created array of structure to handle different pin initializations effectively */
GPIO_Hanlde_Struct gpio_i2c_cfg[]={
		{.gpio_cfg = {.gpio_pin = GPIO_PIN_6, .gpio_pin_mode = GPIO_ALT_FUNC_MODE, .gpio_pin_otype = GPIO_PIN_OPEN_DRAIN, .gpio_pin_speed = GPIO_HIGH_SPEED, .gpio_pin_pupd = GPIO_PIN_PU, .gpio_alt_func =AF4}, .gpio_reg_def = GPIOB},
		{.gpio_cfg = {.gpio_pin = GPIO_PIN_7, .gpio_pin_mode = GPIO_ALT_FUNC_MODE, .gpio_pin_otype = GPIO_PIN_OPEN_DRAIN, .gpio_pin_speed = GPIO_HIGH_SPEED, .gpio_pin_pupd = GPIO_PIN_PU, .gpio_alt_func =AF4}, .gpio_reg_def = GPIOB}
};

const uint8_t gpio_uart_array_size = sizeof(gpio_uart_cfg)/sizeof(gpio_uart_cfg[0]);
const uint8_t gpio_spi_array_size = sizeof(gpio_spi_cfg)/sizeof(gpio_spi_cfg[0]);
const uint8_t gpio_i2c_array_size = sizeof(gpio_i2c_cfg)/sizeof(gpio_i2c_cfg[0]);

/*API to handle GPIO user configurations */
void gpio_user_cfg_init()
{

	for(uint8_t i = 0 ; i < gpio_uart_array_size; i++)
	{
		gpio_init(&gpio_uart_cfg[i]);
	}

	for(uint8_t i = 0 ; i < gpio_spi_array_size; i++)
	{
		gpio_init(&gpio_spi_cfg[i]);
	}
	for(uint8_t i =0; i < gpio_i2c_array_size; i++)
	{
		gpio_init(&gpio_i2c_cfg[i]);
	}
}

/* API to initialize GPIO with user configurations */
void gpio_init(GPIO_Hanlde_Struct* pGpio_cfg)
{
	gpio_stm32_init(pGpio_cfg);
}
