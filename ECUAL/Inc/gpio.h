/*
 * gpio.h
 *
 *  Created on: Aug 10, 2025
 *      Author: Sujith S Babu
 */

#ifndef ECUAL_INC_GPIO_H_
#define ECUAL_INC_GPIO_H_
#include "stm32f407_xx_MemMap.h"

/* Structure for GPIO User configurations */
typedef struct
{
	uint32_t gpio_port;
	uint8_t  gpio_pin;
	uint8_t  gpio_pin_mode;
	uint8_t  gpio_alt_func;
	uint8_t  gpio_pin_pupd;
	uint8_t  gpio_pin_otype;
	uint8_t  gpio_pin_speed;

}GPIO_user_Cfg_Struct;


/* Structure for accessing GPIO_user_Cfg_Struct and GPIO_RegDef_Struct */
typedef struct
{
   GPIO_user_Cfg_Struct gpio_cfg;
   GPIO_RegDef_Struct*  gpio_reg_def;

}GPIO_Hanlde_Struct;

/*Function Prototypes */
void gpio_user_cfg_init();
void gpio_init(GPIO_Hanlde_Struct*);



#endif /* ECUAL_INC_GPIO_H_ */
