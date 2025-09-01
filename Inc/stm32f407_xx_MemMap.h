/*
 * stm32f407_xx_MemMap.h
 *
 *  Created on: Jul 20, 2025
 *      Author: Sujith S Babu
 */

#ifndef STM32F407_XX_MEMMAP_H_
#define STM32F407_XX_MEMMAP_H_
#include <stdint.h>

#define __vo volatile
/*
 * Base addresses for FLASH and SRAM1
 */
#define FLASH_BASEADDR       0x08000000U /* base address of flash memory/main memory */
#define SRAM1_BASEADDR       0x20000000U /* base address of SRAM1 */
#define SRAM2_BASEADDR       0x2001C000U /* base address of SRAM2 */
#define ROM_BASEADDR         0x1FFF0000U /* base address of ROM or system memory */
#define SRAM                 SRAM1_BASEADDR

/*
 * BASE address of NVIC ISER0 and ISER1 registers
 */
#define NVIC_ISER0           (*(__vo uint32_t*)(0xE000E100)) //casts 0xE000E100 to a pointer to uint32_t and dereferences to access the register.
#define NVIC_ISER1           (*(__vo uint32_t*)(0xE000E104)) //casts 0xE000E104 to a pointer to uint32_t and dereferences to access the register.

/*
 * Modifying PRIMASK,which holds the interrupt enable flag .Using direct assembly instructions
 */
#define __disable_irq()        __asm volatile ("cpsid i")// Setting PRIMASK = 1,disables Maskable interrupts via PRIMASK
#define __enable_irq()         __asm volatile ("cpsie i")// Setting PRIMASK = 0,enables Maskable interrupts via PRIMASK

/*
 * Base addresses for AHB and APB buses
 */
#define PERIPH_BASEADDR      0x40000000U       /* base address of Peripherals */
#define APB1PERIPH_BASEADDR  PERIPH_BASEADDR   /* base address of APB1 peripherals */
#define APB2PERIPH_BASEADDR  0x40010000U       /* base address of APB2 peripherals */
#define AHB1PERIPH_BASEADDR  0x40020000U       /* base address of AHB1 peripherals */
#define AHB2PERIPH_BASEADDR  0x50000000U       /* base address of AHB2 peripherals */

/*
 * Base addresses of peripherals hanging on AHB1 bus
 */

#define GPIOA_BASEADDR       (AHB1PERIPH_BASEADDR + 0x0000U) /* base address of GPIOA peripheral */
#define GPIOB_BASEADDR       (AHB1PERIPH_BASEADDR + 0x0400U) /* base address of GPIOB peripheral */
#define GPIOC_BASEADDR       (AHB1PERIPH_BASEADDR + 0x0800U) /* base address of GPIOC peripheral */
#define GPIOD_BASEADDR       (AHB1PERIPH_BASEADDR + 0x0C00U) /* base address of GPIOD peripheral */
#define GPIOE_BASEADDR       (AHB1PERIPH_BASEADDR + 0x1000U) /* base address of GPIOE peripheral */
#define GPIOF_BASEADDR       (AHB1PERIPH_BASEADDR + 0x1400U) /* base address of GPIOF peripheral */
#define GPIOG_BASEADDR       (AHB1PERIPH_BASEADDR + 0x1800U) /* base address of GPIOG peripheral */
#define GPIOH_BASEADDR       (AHB1PERIPH_BASEADDR + 0x1C00U) /* base address of GPIOH peripheral */
#define GPIOI_BASEADDR       (AHB1PERIPH_BASEADDR + 0x2000U) /* base address of GPIOI peripheral */
#define GPOIJ_BASEADDR       (AHB1PERIPH_BASEADDR + 0x2400U) /* base address of GPIOJ peripheral */
#define GPIOK_BASEADDR       (AHB1PERIPH_BASEADDR + 0x2800U) /* base address of GPIOK peripheral */

#define RCC_BASEADDR         (AHB1PERIPH_BASEADDR + 0x3800U) /* base address of RCC peripheral */


#define SYST_CSR   (*(volatile unsigned int *)0xE000E010) // Control and Status
#define SYST_RVR   (*(volatile unsigned int *)0xE000E014) // Reload Value
#define SYST_CVR   (*(volatile unsigned int *)0xE000E018) // Current Value
#define SYST_CALIB (*(volatile unsigned int *)0xE000E01C) // Calibration (optional)
/*
 * Base address of USART2 hanging on APB1 bus
 */
#define USART_1_BASEADDR             (APB2PERIPH_BASEADDR + 0x1000U)
#define USART_2_BASEADDR             (APB1PERIPH_BASEADDR + 0x4400U)

/*
 * Base address of SPI2 peripheral
 */
#define SPI_2_BASEADDR               (APB1PERIPH_BASEADDR + 0x3800U)

/*
 * Base address of I2C1 peripheral
 */
#define I2C_1_BASEADDR               (APB1PERIPH_BASEADDR + 0x5400U)

/*GPIO register structure definition */
typedef struct{

	__vo uint32_t MODER;
	__vo uint32_t OTYPER;
	__vo uint32_t OSPEEDR;
	__vo uint32_t PUPDR;
	__vo uint32_t IDR;
	__vo uint32_t ODR;
	__vo uint32_t BSRR;
	__vo uint32_t LCKR;
	__vo uint32_t AFR[2];


} GPIO_RegDef_Struct;

/*RCC register definition structure */
typedef struct{

   __vo uint32_t CR;
   __vo	uint32_t PLLCFGR;
   __vo	uint32_t CFGR;
   __vo	uint32_t CIR;
   __vo	uint32_t AHB1RSTR;
   __vo	uint32_t AHB2RSTR;
   __vo	uint32_t AHB3RSTR;
   uint32_t      Reserved0;
   __vo	uint32_t APB1RSTR;
   __vo uint32_t APB2RSTR;
   uint32_t      Reserved1[2];
   __vo	uint32_t AHB1ENR;
   __vo	uint32_t AHB2ENR;
   __vo	uint32_t AHB3ENR;
   uint32_t      Reserved2;
   __vo	uint32_t APB1ENR;
   __vo uint32_t APB2ENR;
   uint32_t      Reserved3[2];
   __vo uint32_t AHB1LPENR;
   __vo uint32_t AHB2LPENR;
   __vo uint32_t AHB3LPENR;
   uint32_t      Reserved4;
   __vo uint32_t APB1LPENR;
   __vo uint32_t APB2LPENR;
   uint32_t      Reserved5[2];
   __vo uint32_t BDCR;
   __vo uint32_t CSR;
   uint32_t      Reserved6[2];
   __vo uint32_t SSCGR;
   __vo uint32_t PLLI2SCFGR;
   __vo uint32_t PLLSAICFGR;
   __vo uint32_t DCKCFGR;

} RCC_RegDef_Struct;

/*
 * USART register structure definition
 */
typedef struct
{
	__vo uint32_t USART_SR;
	__vo uint32_t USART_DR;
	__vo uint32_t USART_BRR;
	__vo uint32_t USART_CR1;
	__vo uint32_t USART_CR2;
	__vo uint32_t USART_CR3;
	__vo uint32_t USART_GTPR;

}USART_RegDef_Struct;

/*
 * SPI register structure definition
 */
typedef struct
{
	__vo uint32_t SPI_CR1;
	__vo uint32_t SPI_CR2;
	__vo uint32_t SPI_SR;
	__vo uint32_t SPI_DR;
	__vo uint32_t SPI_CRCPR;
	__vo uint32_t SPI_RXCRCR;
	__vo uint32_t SPI_TXCRCR;
	__vo uint32_t SPI_I2SCFGR;
	__vo uint32_t SPI_I2SPR;
}SPI_RegDef_Struct;

/*
 * I2C register structure definition
 */
typedef struct
{
     __vo uint32_t I2C_CR1;
     __vo uint32_t I2C_CR2;
     __vo uint32_t I2C_OAR1;
     __vo uint32_t I2C_OAR2;
     __vo uint32_t I2C_DR;
     __vo uint32_t I2C_SR1;
     __vo uint32_t I2C_SR2;
     __vo uint32_t I2C_CCR;
     __vo uint32_t I2C_TRISE;
     __vo uint32_t I2C_FLTR;

}I2C_RegDef_Struct;

/* USART2 base address is type casted to structure USART_RefDef_Struct */
#define USART1 ((USART_RegDef_Struct*)USART_1_BASEADDR)
#define USART2 ((USART_RegDef_Struct*)USART_2_BASEADDR)

/* GPIO base address is type casted to structure GPIO_RegDEf_struct */
#define GPIOA ((GPIO_RegDef_Struct*)GPIOA_BASEADDR)
#define GPIOB ((GPIO_RegDef_Struct*)GPIOB_BASEADDR)

/* RCC base address is type casted to structure RCC_RegDef_struct */
#define RCC ((RCC_RegDef_Struct*)RCC_BASEADDR)

/* SPI2 base address is type casted to structure SPI_RegDef_Struct */
#define SPI2 ((SPI_RegDef_Struct*)SPI_2_BASEADDR)

/*I2C1 base address is type casted to structure I2C_RegDef_Struct */
#define I2C1  ((I2C_RegDef_Struct*)I2C_1_BASEADDR)

/* Clock enable macros for GPIO peripherals */
#define GPIOA_CLK_EN() do{RCC->AHB1ENR |= (1<<0);} while(0)
#define GPIOB_CLK_EN() do{RCC->AHB1ENR |= (1<<1);} while(0)

/* clock enable macro for USART2 peripheral */
#define USART1_CLK_EN() do{RCC->APB2ENR |= (1<<4);} while(0)
#define USART2_CLK_EN() do{RCC->APB1ENR |= (1<<17);} while(0)

/* clock enable for SPI peripherals */
#define SPI2_CLK_EN()   do{RCC->APB1ENR |= (1 << 14);} while(0)

/* Clock enable for I2C1 peripheral */
#define I2C1_CLK_EN()   do{RCC->APB1ENR |= (1 << 21);} while(0)

/* Bus reset macros */
#define GPIOA_RESET() do{RCC->AHB1ENR |= (1<<0); RCC->AHB1ENR |= ~(1<<0);} while(0)
#define GPIOB_RESET() do{RCC->AHB1ENR |= (1<<1); RCC->AHB1ENR |= ~(1<<1);} while(0)

/* Macros for GPIO PINS */
#define GPIO_PIN_0   0
#define GPIO_PIN_1   1
#define GPIO_PIN_2   2
#define GPIO_PIN_3   3
#define GPIO_PIN_4   4
#define GPIO_PIN_5   5
#define GPIO_PIN_6   6
#define GPIO_PIN_7   7
#define GPIO_PIN_8   8
#define GPIO_PIN_9   9
#define GPIO_PIN_10  10
#define GPIO_PIN_11  11
#define GPIO_PIN_12  12
#define GPIO_PIN_13  13
#define GPIO_PIN_14  14
#define GPIO_PIN_15  15

/* Macros for GPIO PIN MODES */
#define GPIO_INPUT_MODE        0
#define GPIO_OUTPUT_MODE       1
#define GPIO_ALT_FUNC_MODE     2
#define GPIO_ANALOG_MODE       3

/* Macros for GPIO PIN OUTPUT TYPE */
#define GPIO_PIN_PUSH_PULL     0
#define GPIO_PIN_OPEN_DRAIN    1

/* Macros for GPIO PIN OUTPUT SPEED */
#define GPIO_LOW_SPEED         0
#define GPIO_MEDIUM_SPEED      1
#define GPIO_HIGH_SPEED        2
#define GPIO_VHIGH_SPEED       3

/* Macros for GPIO PIN PULL UP/PULL DOWN*/
#define GPIO_PIN_NO_PUPD       0
#define GPIO_PIN_PU            1
#define GPIO_PIN_PD            2
#define GPIO_PIN_RESERVED      3

/* Macros For Alternate Function */
#define AF0                    0
#define AF1                    1
#define AF2                    2
#define AF3                    3
#define AF4                    4
#define AF5                    5
#define AF6                    6
#define AF7                    7
#define AF8                    8
#define AF9                    9
#define AF10                   A
#define AF11                   B
#define AF12                   C
#define AF13                   D
#define AF14                   E
#define AF15                   F

/*General Macros for GPIO PIN state */
#define GPIO_PIN_LOW           0
#define GPIO_PIN_HIGH          1


#include "uart.h"

#endif /* STM32F407_XX_MEMMAP_H_ */
