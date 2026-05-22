/*
 * stm32l4xx.h
 *
 *  Created on: May 7, 2026
 *      Author: manohar kuduchella
 */

#ifndef INC_STM32L476XX_H_
#define INC_STM32L476XX_H_

#include <stdint.h>
#include <stddef.h>

#define __vo volatile
#define __weak __attribute__((weak))
/****************************************************/
//ARM Cortex Mx Processor NVIC ISERx register addresses
/****************************************************/
#define NVIC_ISER0		((__vo uint32_t*)0xE000E100 )
#define NVIC_ISER1		((__vo uint32_t*)0xE000E104 )
#define NVIC_ISER2		((__vo uint32_t*)0xE000E108 )
#define NVIC_ISER3		((__vo uint32_t*)0xE000E10c )
#define NVIC_ISER4		((__vo uint32_t*)0xE000E110 )


#define NVIC_ICER0		((__vo uint32_t*)0xE000E180 )
#define NVIC_ICER1		((__vo uint32_t*)0xE000E184 )
#define NVIC_ICER2		((__vo uint32_t*)0xE000E188 )
#define NVIC_ICER3		((__vo uint32_t*)0xE000E18C )

#define NVIC_PR_BASE_ADDR	((__vo uint32_t*)0xE000E400)

#define NO_PR_BITS_IMPLEMENTED 				4

// returns port code for given GPIOx base address
#define GPIO_BASEADDR_TO_CODE(x)  ((x == GPIOA) ? 0 : \
                                   (x == GPIOB) ? 1 : \
                                   (x == GPIOC) ? 2 : \
                                   (x == GPIOD) ? 3 : \
                                   (x == GPIOE) ? 4 : \
                                   (x == GPIOF) ? 5 : \
                                   (x == GPIOG) ? 6 : \
                                   (x == GPIOH) ? 7 : 0)



/*
 * Base addresses of flash and SRAM Memories
 */
#define FLASH_BASEADDR		0x08000000UL
#define SRAM1_BASEADDR		0x20000000UL
#define SRAM2_BASEADDR		0x10000000UL
#define ROM_BASEADDR		0x1FFF0000UL
#define SRAM 				SRAM1_BASEADDR

#define PERIPH_BASEADDR 		0x40000000UL
#define APB1PERIPH_BASEADDR		PERIPH_BASEADDR
#define APB2PERIPH_BASEADDR		0x40010000UL
#define AHB1PERIPH_BASEADDR 	0x40020000UL
#define AHB2PERIPH_BASEADDR 	0x48000000UL

/*
 * Base addresses of peripherals which are hanging on AHB2 bus
 * TODO: complete for all peripherals
 * */

#define GPIOA_BASEADDR			(AHB2PERIPH_BASEADDR + 0x0000UL)
#define GPIOB_BASEADDR			(AHB2PERIPH_BASEADDR + 0x0400UL)
#define GPIOC_BASEADDR			(AHB2PERIPH_BASEADDR + 0x0800UL)
#define GPIOD_BASEADDR			(AHB2PERIPH_BASEADDR + 0x0C00UL)
#define GPIOE_BASEADDR			(AHB2PERIPH_BASEADDR + 0x1000UL)
#define GPIOF_BASEADDR			(AHB2PERIPH_BASEADDR + 0x1400UL)
#define GPIOG_BASEADDR			(AHB2PERIPH_BASEADDR + 0x1800UL)
#define GPIOH_BASEADDR			(AHB2PERIPH_BASEADDR + 0x1C00UL)
#define GPIOI_BASEADDR			(AHB2PERIPH_BASEADDR + 0x2000UL)

/*
 * Base addresses of peripherals which are hanging on AHB1 bus
 * TODO: complete for all peripherals
 * */

#define RCC_BASEADDR 			(AHB1PERIPH_BASEADDR + 0x1000UL)

/*
 * Base addresses of peripherals which are hanging on APB1 bus
 * TODO: complete for all other peripherals
*/

#define I2C1_BASEADDR 			(APB1PERIPH_BASEADDR + 0x5400UL)
#define I2C2_BASEADDR			(APB1PERIPH_BASEADDR + 0x5800UL)
#define I2C3_BASEADDR			(APB1PERIPH_BASEADDR + 0x5C00UL)

#define SPI2_BASEADDR			(APB1PERIPH_BASEADDR + 0x3800UL)
#define SPI3_BASEADDR			(APB1PERIPH_BASEADDR + 0x3C00UL)

#define USART2_BASEADDR			(APB1PERIPH_BASEADDR + 0x4400UL)
#define USART3_BASEADDR			(APB1PERIPH_BASEADDR + 0x4800UL)

#define UART4_BASEADDR			(APB1PERIPH_BASEADDR + 0x4C00UL)
#define UART5_BASEADDR			(APB1PERIPH_BASEADDR + 0x5000UL)


/*
 *
 * Base addresses of peripherals which are hanging on APB2 bus
 * TODO: complete for all other peripherals
*/
#define EXTI_BASEADDR			(APB2PERIPH_BASEADDR + 0x0400UL)
#define SPI1_BASEADDR			(APB2PERIPH_BASEADDR + 0x3000UL)
#define USART1_BASEADDR			(APB2PERIPH_BASEADDR + 0x3800UL)
#define SYSCFG_BASEADDR			(APB2PERIPH_BASEADDR + 0x0000UL)

/*
 * Peripheral register definition structures of STM32L476XX
 *
 * */

typedef struct
{
	__vo uint32_t MODER;
	__vo uint32_t OTYPER;
	__vo uint32_t OSPEEDR;
	__vo uint32_t PUPDR;
	__vo uint32_t IDR;
	__vo uint32_t ODR;
	__vo uint32_t BSRR;
	__vo uint32_t LCKR;
	__vo uint32_t AFR[2];    /*AFR[0] : GPIO alternate function low register, AF[1] : GPIO alternate function High register*/

}GPIO_RegDef_t;


/*
 * Peripheral register definition structure for SPI
 * */
typedef struct
{
	__vo uint32_t CR1;
	__vo uint32_t CR2;
	__vo uint32_t SR;
	__vo uint32_t DR;
	__vo uint32_t CRCPR;
	__vo uint32_t RXCRCR;
	__vo uint32_t TXCRCR;
} SPI_RegDef_t;

/*
 * Peripheral register definition structure for I2C
 * */
typedef struct
{
	__vo uint32_t CR1;
	__vo uint32_t CR2;
	__vo uint32_t OAR1;
	__vo uint32_t OAR2;
	__vo uint32_t TIMINGR;
	__vo uint32_t TIMEOUTR;
	__vo uint32_t ISR;
	__vo uint32_t ICR;
	__vo uint32_t PECR;
	__vo uint32_t RXDR;
	__vo uint32_t TXDR;
} I2C_RegDef_t;


/*
 * Peripheral register definition structure for USART
 * */
typedef struct
{
	__vo uint32_t CR1;
	__vo uint32_t CR2;
	__vo uint32_t CR3;
	__vo uint32_t BRR;
	__vo uint32_t GTPR;
	__vo uint32_t RTOR;
	__vo uint32_t RQR;
	__vo uint32_t ISR;
	__vo uint32_t ICR;
	__vo uint32_t RDR;
	__vo uint32_t TDR;
} USART_RegDef_t;




/*
 * Peripheral register definition structure for RCC
 */
typedef struct
{
	__vo uint32_t CR;
	__vo uint32_t ICSCR;
	__vo uint32_t CFGR;
	__vo uint32_t PLLCFGR;
	__vo uint32_t PLLSAI1CFGR;
	__vo uint32_t PLLSAI2CFGR;
	__vo uint32_t CIER;
	__vo uint32_t CIFR;
	__vo uint32_t CICR;

	__vo uint32_t RESERVED0;

	__vo uint32_t AHB1RSTR;
	__vo uint32_t AHB2RSTR;
	__vo uint32_t AHB3RSTR;

	__vo uint32_t RESERVED1;

	__vo uint32_t APB1RSTR1;
	__vo uint32_t APB1RSTR2;
	__vo uint32_t APB2RSTR;

	__vo uint32_t RESERVED2;

	__vo uint32_t AHB1ENR;
	__vo uint32_t AHB2ENR;
	__vo uint32_t AHB3ENR;

	__vo uint32_t RESERVED3;

	__vo uint32_t APB1ENR1;
	__vo uint32_t APB1ENR2;
	__vo uint32_t APB2ENR;

	__vo uint32_t RESERVED4;

	__vo uint32_t AHB1SMENR;
	__vo uint32_t AHB2SMENR;
	__vo uint32_t AHB3SMENR;

	__vo uint32_t RESERVED5;

	__vo uint32_t APB1SMENR1;
	__vo uint32_t APB1SMENR2;
	__vo uint32_t APB2SMENR;

	__vo uint32_t RESERVED6;

	__vo uint32_t CCIPR;

	__vo uint32_t RESERVED7;

	__vo uint32_t BDCR;
	__vo uint32_t CSR;
	__vo uint32_t CRRCR;
	__vo uint32_t CCIPR2;

}RCC_RegDef_t;



/*
 * Peripheral register definition structure for EXTI
 */

typedef struct
{
	volatile uint32_t IMR1;      // 0x00 Interrupt mask register 1
	volatile uint32_t EMR1;      // 0x04 Event mask register 1
	volatile uint32_t RTSR1;     // 0x08 Rising trigger selection register 1
	volatile uint32_t FTSR1;     // 0x0C Falling trigger selection register 1
	volatile uint32_t SWIER1;    // 0x10 Software interrupt event register 1
	volatile uint32_t PR1;       // 0x14 Pending register 1

	uint32_t RESERVED1[2];       // 0x18 - 0x1C

	volatile uint32_t IMR2;      // 0x20 Interrupt mask register 2
	volatile uint32_t EMR2;      // 0x24 Event mask register 2
	volatile uint32_t RTSR2;     // 0x28 Rising trigger selection register 2
	volatile uint32_t FTSR2;     // 0x2C Falling trigger selection register 2
	volatile uint32_t SWIER2;    // 0x30 Software interrupt event register 2
	volatile uint32_t PR2;       // 0x34 Pending register 2

} EXTI_RegDef_t;

/*
 * Peripheral register definition structure for EXTI
 */

typedef struct
{
	volatile uint32_t MEMRMP;        // 0x00 Memory remap register
	volatile uint32_t CFGR1;         // 0x04 Configuration register 1
	volatile uint32_t EXTICR[4];       // 0x08 External interrupt configuration register 1
	//volatile uint32_t EXTICR2;       // 0x0C External interrupt configuration register 2
	//volatile uint32_t EXTICR3;       // 0x10 External interrupt configuration register 3
	//volatile uint32_t EXTICR4;       // 0x14 External interrupt configuration register 4
	volatile uint32_t SCSR;          // 0x18 SRAM2 control and status register
	volatile uint32_t CFGR2;         // 0x1C Configuration register 2
	volatile uint32_t SWPR;          // 0x20 SRAM2 write protection register
	volatile uint32_t SKR;           // 0x24 SRAM2 key register
	volatile uint32_t SWPR2;         // 0x28 SRAM2 write protection register 2

} SYSCFG_RegDef_t;


/*
 * Peripheral definition (Peripheral base address typecasted  to xxx_RegDef_t)
 */
#define GPIOA 			((GPIO_RegDef_t*)GPIOA_BASEADDR)
#define GPIOB 			((GPIO_RegDef_t*)GPIOB_BASEADDR)
#define GPIOC 			((GPIO_RegDef_t*)GPIOC_BASEADDR)
#define GPIOD 			((GPIO_RegDef_t*)GPIOD_BASEADDR)
#define GPIOE 			((GPIO_RegDef_t*)GPIOE_BASEADDR)
#define GPIOF 			((GPIO_RegDef_t*)GPIOF_BASEADDR)
#define GPIOG 			((GPIO_RegDef_t*)GPIOG_BASEADDR)
#define GPIOH 			((GPIO_RegDef_t*)GPIOH_BASEADDR)
#define GPIOI 			((GPIO_RegDef_t*)GPIOI_BASEADDR)


#define RCC				((RCC_RegDef_t*)RCC_BASEADDR)
#define EXTI 			((EXTI_RegDef_t*)EXTI_BASEADDR)
#define SYSCFG          ((SYSCFG_RegDef_t*)SYSCFG_BASEADDR)

#define SPI1 			((SPI_RegDef_t*)SPI1_BASEADDR)
#define SPI2			((SPI_RegDef_t*)SPI2_BASEADDR)
#define SPI3 			((SPI_RegDef_t*)SPI3_BASEADDR)


#define I2C1			((I2C_RegDef_t*)I2C1_BASEADDR)
#define I2C2			((I2C_RegDef_t*)I2C2_BASEADDR)
#define I2C3			((I2C_RegDef_t*)I2C3_BASEADDR)


#define USART1          ((USART_RegDef_t*)USART1_BASEADDR)
#define USART2          ((USART_RegDef_t*)USART2_BASEADDR)
#define USART3          ((USART_RegDef_t*)USART3_BASEADDR)
#define UART4           ((USART_RegDef_t*)UART4_BASEADDR)
#define UART5           ((USART_RegDef_t*)UART5_BASEADDR)

/*
 * Clock Enable Macros for GPIOx peripherals
 * */

#define GPIOA_PCLK_EN()		(RCC->AHB2ENR |= (1<<0))
#define GPIOB_PCLK_EN()		(RCC->AHB2ENR |= (1<<1))
#define GPIOC_PCLK_EN()		(RCC->AHB2ENR |= (1<<2))
#define GPIOD_PCLK_EN()		(RCC->AHB2ENR |= (1<<3))
#define GPIOE_PCLK_EN()		(RCC->AHB2ENR |= (1<<4))
#define GPIOF_PCLK_EN()		(RCC->AHB2ENR |= (1<<5))
#define GPIOG_PCLK_EN()		(RCC->AHB2ENR |= (1<<6))
#define GPIOH_PCLK_EN()		(RCC->AHB2ENR |= (1<<7))
#define GPIOI_PCLK_EN()		(RCC->AHB2ENR |= (1<<8))

/*
 * Clock Enable Macros for I2Cx peripherals
 * */

#define I2C1_PCLK_EN()		(RCC->APB1ENR1 |= (1<<21))
#define I2C2_PCLK_EN()		(RCC->APB1ENR1 |= (1<<22))
#define I2C3_PCLK_EN()		(RCC->APB1ENR1 |= (1<<23))

/*
 * Clock Enable Macros for SPIx peripherals
 * */
#define SPI1_PCLK_EN()		(RCC->APB2ENR |= (1<<12))
#define SPI2_PCLK_EN()		(RCC->APB1ENR1 |= (1<<14))
#define SPI3_PCLK_EN()		(RCC->APB1ENR1 |= (1<<15))
/*
 * Clock Enable Macros for USARTx peripherals
 * */
#define USART1_PCLK_EN()        (RCC->APB2ENR |= (1 << 14))
#define USART2_PCLK_EN()		(RCC->APB1ENR1 |= (1<<17))
#define USART3_PCLK_EN()		(RCC->APB1ENR1 |= (1<<18))
#define UART4_PCLK_EN()         (RCC->APB1ENR1 |= (1 << 19))
#define UART5_PCLK_EN()         (RCC->APB1ENR1 |= (1 << 20))

/*
 * Clock Enable Macros for SYSCFG peripherals
 * */

#define SYSCFG_PCLK_EN()		(RCC->APB2ENR |= (1<<0))

/*
 * Clock Disable Macros for GPIOx peripherals
 * */

#define GPIOA_PCLK_DI()		(RCC->AHB2ENR &= ~(1<<0))
#define GPIOB_PCLK_DI()		(RCC->AHB2ENR &= ~(1<<1))
#define GPIOC_PCLK_DI()		(RCC->AHB2ENR &= ~(1<<2))
#define GPIOD_PCLK_DI()		(RCC->AHB2ENR &= ~(1<<3))
#define GPIOE_PCLK_DI()		(RCC->AHB2ENR &= ~(1<<4))
#define GPIOF_PCLK_DI()		(RCC->AHB2ENR &= ~(1<<5))
#define GPIOG_PCLK_DI()		(RCC->AHB2ENR &= ~(1<<6))
#define GPIOH_PCLK_DI()		(RCC->AHB2ENR &= ~(1<<7))
#define GPIOI_PCLK_DI()		(RCC->AHB2ENR &= ~(1<<8))

/*
 * Clock Disable Macros for I2Cx peripherals
 * */
#define I2C1_PCLK_DI()		(RCC->APB1ENR1 &= ~(1<<21))
#define I2C2_PCLK_DI()		(RCC->APB1ENR1 &= ~(1<<22))
#define I2C3_PCLK_DI()		(RCC->APB1ENR1 &= ~(1<<23))

/*
 * Clock Disable Macros for SPIx peripherals
 * */
#define SPI1_PCLK_DI()		(RCC->APB2ENR &= ~(1<<12))
#define SPI2_PCLK_DI()		(RCC->APB1ENR1 &= ~(1<<14))
#define SPI3_PCLK_DI()		(RCC->APB1ENR1 &= ~(1<<15))




/*
 * Clock Disable Macros for USARTx peripherals
 * */

#define USART1_PCLK_DI()        (RCC->APB2ENR &= ~(1 << 14))
#define USART2_PCLK_DI()        (RCC->APB1ENR1 &= ~(1 << 17))
#define USART3_PCLK_DI()        (RCC->APB1ENR1 &= ~(1 << 18))

#define UART4_PCLK_DI()         (RCC->APB1ENR1 &= ~(1 << 19))
#define UART5_PCLK_DI()         (RCC->APB1ENR1 &= ~(1 << 20))

/*
 * Clock Disable Macros for SYSCFG peripherals
 * */

/*
 * Macros to reset GPIOx peripherals
 * */
#define GPIOA_REG_RESET()	do { (RCC->AHB2RSTR |= (1<<0)); (RCC->AHB2RSTR &= ~(1<<0)); }while(0)
#define GPIOB_REG_RESET()	do { (RCC->AHB2RSTR |= (1<<1)); (RCC->AHB2RSTR &= ~(1<<1)); }while(0)
#define GPIOC_REG_RESET()	do { (RCC->AHB2RSTR |= (1<<2)); (RCC->AHB2RSTR &= ~(1<<2)); }while(0)
#define GPIOD_REG_RESET()	do { (RCC->AHB2RSTR |= (1<<3)); (RCC->AHB2RSTR &= ~(1<<3)); }while(0)
#define GPIOE_REG_RESET()	do { (RCC->AHB2RSTR |= (1<<4)); (RCC->AHB2RSTR &= ~(1<<4)); }while(0)
#define GPIOF_REG_RESET()	do { (RCC->AHB2RSTR |= (1<<5)); (RCC->AHB2RSTR &= ~(1<<5)); }while(0)
#define GPIOG_REG_RESET()	do { (RCC->AHB2RSTR |= (1<<6)); (RCC->AHB2RSTR &= ~(1<<6)); }while(0)
#define GPIOH_REG_RESET()	do { (RCC->AHB2RSTR |= (1<<7)); (RCC->AHB2RSTR &= ~(1<<7)); }while(0)
#define GPIOI_REG_RESET()	do { (RCC->AHB2RSTR |= (1<<8)); (RCC->AHB2RSTR &= ~(1<<8)); }while(0)

/*
 * Macros to reset SPIx peripherals
 * */
#define SPI1_REG_RESET()	do { (RCC->APB2RSTR |= (1<<12)); (RCC->APB2RSTR &= ~(1<<12)); }while(0)
#define SPI2_REG_RESET()	do { (RCC->APB1RSTR1 |= (1<<14)); (RCC->APB1RSTR1 &= ~(1<<14)); }while(0)
#define SPI3_REG_RESET()	do { (RCC->APB1RSTR1 |= (1<<15)); (RCC->APB1RSTR1 &= ~(1<<15)); }while(0)


/*
 * Macros to reset I2Cx peripherals
 * */
#define I2C1_REG_RESET()	do { (RCC->APB1RSTR1 |= (1<<21)); (RCC->APB1RSTR1 &= ~(1<<21)); }while(0)
#define I2C2_REG_RESET()	do { (RCC->APB1RSTR1 |= (1<<22)); (RCC->APB1RSTR1 &= ~(1<<22)); }while(0)
#define I2C3_REG_RESET()	do { (RCC->APB1RSTR1 |= (1<<23)); (RCC->APB1RSTR1 &= ~(1<<23)); }while(0)


/*
 * Macros to reset USARTx peripherals
 * */
#define USART1_REG_RESET()      do { (RCC->APB2RSTR |= (1 << 14));  (RCC->APB2RSTR &= ~(1 << 14)); } while(0)

#define USART2_REG_RESET()      do { (RCC->APB1RSTR1 |= (1 << 17)); (RCC->APB1RSTR1 &= ~(1 << 17)); } while(0)

#define USART3_REG_RESET()      do { (RCC->APB1RSTR1 |= (1 << 18)); (RCC->APB1RSTR1 &= ~(1 << 18)); } while(0)

#define UART4_REG_RESET()       do { (RCC->APB1RSTR1 |= (1 << 19)); (RCC->APB1RSTR1 &= ~(1 << 19)); } while(0)

#define UART5_REG_RESET()       do { (RCC->APB1RSTR1 |= (1 << 20)); (RCC->APB1RSTR1 &= ~(1 << 20)); } while(0)

/*
 * IRQ Numbers of STM32L4xx MCU
 * */

#define IRQ_NO_EXTI0 		6
#define IRQ_NO_EXTI1 		7
#define IRQ_NO_EXTI2 		8
#define IRQ_NO_EXTI3 		9
#define IRQ_NO_EXTI4 		10
#define IRQ_NO_EXTI9_5 		23
#define IRQ_NO_EXTI15_10 	40



/*IRQ priority */
#define NVIC_IRQ_PRI0		0
#define NVIC_IRQ_PRI1		1
#define NVIC_IRQ_PRI2		2
#define NVIC_IRQ_PRI3		3
#define NVIC_IRQ_PRI4		4
#define NVIC_IRQ_PRI5		5
#define NVIC_IRQ_PRI6		6
#define NVIC_IRQ_PRI7		7
#define NVIC_IRQ_PRI8		8
#define NVIC_IRQ_PRI9		9
#define NVIC_IRQ_PRI10		10
#define NVIC_IRQ_PRI11		11
#define NVIC_IRQ_PRI12		12
#define NVIC_IRQ_PRI13		13
#define NVIC_IRQ_PRI14		14
#define NVIC_IRQ_PRI15		15


/*
 * Helper macros
 * */

#define ENABLE 			1
#define DISABLE 		0
#define SET 			ENABLE
#define RESET 			DISABLE

#define GPIO_PIN_SET 	SET
#define GPIO_PIN_RESET 	RESET

#define FLAG_RESET 		RESET
#define FLAG_SET 		SET


#include "stm32l476xx_spi2.h"
#include "stm32l476xx_gpio_driver.h"
//#include "stm32l476xx_spi_driver.h"
#include "stm32l476xx_i2c_driver.h"
#include "stm32l476xx_usart_driver.h"
#include "stm32l476xx_rcc_driver.h"


#endif /* INC_STM32L476XX_H_ */
