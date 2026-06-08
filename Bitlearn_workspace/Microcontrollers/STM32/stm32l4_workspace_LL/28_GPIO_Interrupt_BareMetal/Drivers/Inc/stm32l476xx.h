/*
 * stm32l476xx.h

 */

#ifndef INC_STM32L476XX_H_
#define INC_STM32L476XX_H_

#include <stddef.h>
#include <stdio.h>
#include <stdint.h>

//PROCESSOR INTERRUPT REGISTERS
#define NVIC_ICER0   (*(volatile uint32_t*)0xE000E180)
#define NVIC_ICER1   (*(volatile uint32_t*)0xE000E184)
#define NVIC_ICER2   (*(volatile uint32_t*)0xE000E188)
#define NVIC_ICER3   (*(volatile uint32_t*)0xE000E18C)

#define NVIC_IPR     ((volatile uint32_t*)0xE000E400)

#define NVIC_ISER0   (*(volatile uint32_t*)0xE000E100)
#define NVIC_ISER1   (*(volatile uint32_t*)0xE000E104)
#define NVIC_ISER2   (*(volatile uint32_t*)0xE000E108)
#define NVIC_ISER3   (*(volatile uint32_t*)0xE000E10C)

#define NVIC_PR_BASE_ADDR ((volatile uint32_t*)0xE000E400)

#define FLASH_BASE   0x08000000UL
#define SRAM1_BASE   0x20000000UL
#define SRAM2_BASE   0x10000000UL

#define PERIPH_BASE        0x40000000UL

//AHB
#define AHB1PERIPH_BASE    (PERIPH_BASE + 0x0020000UL)
#define AHB2PERIPH_BASE    (PERIPH_BASE + 0x08000000UL)
#define AHB3PERIPH_BASE    (PERIPH_BASE + 0x0C000000UL)

//APB
#define APB1PERIPH_BASE    0x40000000UL
#define APB2PERIPH_BASE    0x40010000UL

//RCC
#define RCC_BASE           (PERIPH_BASE + 0x21000UL)

#define GPIOA_BASE         (AHB2PERIPH_BASE + 0x0000UL)
#define GPIOB_BASE         (AHB2PERIPH_BASE + 0x0400UL)
#define GPIOC_BASE         (AHB2PERIPH_BASE + 0x0800UL)
#define GPIOD_BASE         (AHB2PERIPH_BASE + 0x0C00UL)
#define GPIOE_BASE         (AHB2PERIPH_BASE + 0x1000UL)
#define GPIOF_BASE         (AHB2PERIPH_BASE + 0x1400UL)
#define GPIOG_BASE         (AHB2PERIPH_BASE + 0x1800UL)
#define GPIOH_BASE         (AHB2PERIPH_BASE + 0x1C00UL)

//USART
//#define USART1_BASE        (APB2PERIPH_BASE + 0x3800UL)
//#define USART2_BASE        (APB1PERIPH_BASE + 0x4400UL)
//#define USART3_BASE        (APB1PERIPH_BASE + 0x4800UL)

//SPI
#define SPI1_BASE          (APB2PERIPH_BASE + 0x3000UL)
#define SPI2_BASE          (APB1PERIPH_BASE + 0x3800UL)
#define SPI3_BASE          (APB1PERIPH_BASE + 0x3C00UL)

//I2C
#define I2C1_BASE          (APB1PERIPH_BASE + 0x5400UL)
#define I2C2_BASE          (APB1PERIPH_BASE + 0x5800UL)
#define I2C3_BASE          (APB1PERIPH_BASE + 0x5C00UL)

//TIMERS
#define TIM1_BASE          (APB2PERIPH_BASE + 0x2C00UL)
#define TIM2_BASE          (APB1PERIPH_BASE + 0x0000UL)
#define TIM3_BASE          (APB1PERIPH_BASE + 0x0400UL)

//EXTI
#define EXTI_BASE 		   (0x40010400UL)

typedef struct {
	volatile uint32_t MODER;    // 0x00
	volatile uint32_t OTYPER;   // 0x04
	volatile uint32_t OSPEEDR;  // 0x08
	volatile uint32_t PUPDR;    // 0x0C
	volatile uint32_t IDR;      // 0x10
	volatile uint32_t ODR;      // 0x14
	volatile uint32_t BSRR;     // 0x18
	volatile uint32_t LCKR;     // 0x1C
	volatile uint32_t AFR[2];   // 0x20 (AFRL), 0x24 (AFRH)
	volatile uint32_t BRR;      // 0x28
	volatile uint32_t ASCR;     // 0x2C
} GPIO_TypeDef;

#define GPIO_PIN_SET    			1
#define GPIO_PIN_RESET  			0

#define GPIOA ((GPIO_TypeDef*)GPIOA_BASE)
#define GPIOB ((GPIO_TypeDef*)GPIOB_BASE)
#define GPIOC ((GPIO_TypeDef*)GPIOC_BASE)
#define GPIOD ((GPIO_TypeDef*)GPIOD_BASE)
#define GPIOE ((GPIO_TypeDef*)GPIOE_BASE)
#define GPIOF ((GPIO_TypeDef*)GPIOF_BASE)
#define GPIOG ((GPIO_TypeDef*)GPIOG_BASE)
#define GPIOH ((GPIO_TypeDef*)GPIOH_BASE)

typedef struct {
	volatile uint32_t CR;            // 0x00
	volatile uint32_t ICSCR;         // 0x04
	volatile uint32_t CFGR;          // 0x08
	volatile uint32_t PLLCFGR;       // 0x0C

	volatile uint32_t PLLSAI1CFGR;   // 0x10
	volatile uint32_t PLLSAI2CFGR;   // 0x14

	volatile uint32_t CIER;          // 0x18
	volatile uint32_t CIFR;          // 0x1C
	volatile uint32_t CICR;          // 0x20

	volatile uint32_t RESERVED0;     // 0x24

	volatile uint32_t AHB1RSTR;      // 0x28
	volatile uint32_t AHB2RSTR;      // 0x2C
	volatile uint32_t AHB3RSTR;      // 0x30

	volatile uint32_t RESERVED1;     // 0x34

	volatile uint32_t APB1RSTR1;     // 0x38
	volatile uint32_t APB1RSTR2;     // 0x3C
	volatile uint32_t APB2RSTR;      // 0x40

	volatile uint32_t RESERVED2;     // 0x44

	volatile uint32_t AHB1ENR;       // 0x48
	volatile uint32_t AHB2ENR;       // 0x4C
	volatile uint32_t AHB3ENR;       // 0x50

	volatile uint32_t RESERVED3;     // 0x54

	volatile uint32_t APB1ENR1;      // 0x58
	volatile uint32_t APB1ENR2;      // 0x5C
	volatile uint32_t APB2ENR;       // 0x60

	volatile uint32_t RESERVED4;     // 0x64

	volatile uint32_t AHB1SMENR;     // 0x68
	volatile uint32_t AHB2SMENR;     // 0x6C
	volatile uint32_t AHB3SMENR;     // 0x70

	volatile uint32_t RESERVED5;     // 0x74

	volatile uint32_t APB1SMENR1;    // 0x78
	volatile uint32_t APB1SMENR2;    // 0x7C
	volatile uint32_t APB2SMENR;     // 0x80

	volatile uint32_t RESERVED6;     // 0x84

	volatile uint32_t CCIPR;         // 0x88

	volatile uint32_t RESERVED7;     // 0x8C

	volatile uint32_t BDCR;          // 0x90
	volatile uint32_t CSR;           // 0x94

	volatile uint32_t CRRCR;         // 0x98

	volatile uint32_t CCIPR2;        // 0x9C

} RCC_TypeDef;

#define RCC ((RCC_TypeDef*)RCC_BASE)

// GPIO CLOCK ENABLE
#define GPIOA_CLK_EN() (RCC->AHB2ENR |= (1 << 0))
#define GPIOB_CLK_EN() (RCC->AHB2ENR |= (1 << 1))
#define GPIOC_CLK_EN() (RCC->AHB2ENR |= (1 << 2))
#define GPIOD_CLK_EN() (RCC->AHB2ENR |= (1 << 3))
#define GPIOE_CLK_EN() (RCC->AHB2ENR |= (1 << 4))
#define GPIOF_CLK_EN() (RCC->AHB2ENR |= (1 << 5))
#define GPIOG_CLK_EN() (RCC->AHB2ENR |= (1 << 6))
#define GPIOH_CLK_EN() (RCC->AHB2ENR |= (1 << 7))

// GPIO CLOCK DISABLE
#define GPIOA_CLK_DI() (RCC->AHB2ENR &= ~(1 << 0))
#define GPIOB_CLK_DI() (RCC->AHB2ENR &= ~(1 << 1))
#define GPIOC_CLK_DI() (RCC->AHB2ENR &= ~(1 << 2))
#define GPIOD_CLK_DI() (RCC->AHB2ENR &= ~(1 << 3))
#define GPIOE_CLK_DI() (RCC->AHB2ENR &= ~(1 << 4))
#define GPIOF_CLK_DI() (RCC->AHB2ENR &= ~(1 << 5))
#define GPIOG_CLK_DI() (RCC->AHB2ENR &= ~(1 << 6))
#define GPIOH_CLK_DI() (RCC->AHB2ENR &= ~(1 << 7))

// GPIO REGISTER RESET (SET + CLEAR)
#define GPIOA_REG_RESET() do { \
    RCC->AHB2RSTR |=  (1 << 0); \
    RCC->AHB2RSTR &= ~(1 << 0); \
} while(0)

#define GPIOB_REG_RESET() do { \
    RCC->AHB2RSTR |=  (1 << 1); \
    RCC->AHB2RSTR &= ~(1 << 1); \
} while(0)

#define GPIOC_REG_RESET() do { \
    RCC->AHB2RSTR |=  (1 << 2); \
    RCC->AHB2RSTR &= ~(1 << 2); \
} while(0)

#define GPIOD_REG_RESET() do { \
    RCC->AHB2RSTR |=  (1 << 3); \
    RCC->AHB2RSTR &= ~(1 << 3); \
} while(0)

#define GPIOE_REG_RESET() do { \
    RCC->AHB2RSTR |=  (1 << 4); \
    RCC->AHB2RSTR &= ~(1 << 4); \
} while(0)

#define GPIOF_REG_RESET() do { \
    RCC->AHB2RSTR |=  (1 << 5); \
    RCC->AHB2RSTR &= ~(1 << 5); \
} while(0)

#define GPIOG_REG_RESET() do { \
    RCC->AHB2RSTR |=  (1 << 6); \
    RCC->AHB2RSTR &= ~(1 << 6); \
} while(0)

#define GPIOH_REG_RESET() do { \
    RCC->AHB2RSTR |=  (1 << 7); \
    RCC->AHB2RSTR &= ~(1 << 7); \
} while(0)

#define ENABLE  		1
#define DISABLE 		0
#define SET     		ENABLE
#define RESET   		DISABLE

typedef struct {
	volatile uint32_t IMR1;
	volatile uint32_t EMR1;
	volatile uint32_t RTSR1;
	volatile uint32_t FTSR1;
	volatile uint32_t SWIER1;
	volatile uint32_t PR1;
} EXTI_RegDef_t;

#define EXTI       ((EXTI_RegDef_t*)EXTI_BASE)

#define SYSCFG_BASE   (APB2PERIPH_BASE + 0x0000UL)

typedef struct {
	volatile uint32_t MEMRMP;
	volatile uint32_t CFGR1;
	volatile uint32_t EXTICR[4];
	volatile uint32_t RESERVED[2];
	volatile uint32_t CFGR2;
} SYSCFG_RegDef_t;

#define SYSCFG_CLK_ENABLE() (RCC->APB2ENR |= (1 << 0))

#define SYSCFG ((SYSCFG_RegDef_t*)SYSCFG_BASE)


//SPI REGISTER STRUCT

typedef struct
{
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t SR;
    volatile uint32_t DR;
    volatile uint32_t CRCPR;
    volatile uint32_t RXCRCR;
    volatile uint32_t TXCRCR;
} SPI_RegDef_t;

#define SPI1 ((SPI_RegDef_t*)SPI1_BASE)
#define SPI2 ((SPI_RegDef_t*)SPI2_BASE)
#define SPI3 ((SPI_RegDef_t*)SPI3_BASE)

#define SPI1_CLK_ENABLE() (RCC->APB2ENR |= (1 << 12))
#define SPI2_CLK_ENABLE()   (RCC->APB1ENR1 |= (1 << 14))
#define SPI3_CLK_ENABLE()   (RCC->APB1ENR1 |= (1 << 15))

#define SPI1_CLK_DISABLE()  (RCC->APB2ENR &= ~(1 << 12))
#define SPI2_CLK_DISABLE()  (RCC->APB1ENR1 &= ~(1 << 14))
#define SPI3_CLK_DISABLE()  (RCC->APB1ENR1 &= ~(1 << 15))

/* ================= SPI_CR1 BIT POSITIONS ================= */

#define SPI_CR1_CPHA        0
#define SPI_CR1_CPOL        1
#define SPI_CR1_MSTR        2
#define SPI_CR1_BR          3   // 3 bits: [5:3]
#define SPI_CR1_SPE         6
#define SPI_CR1_LSBFIRST    7
#define SPI_CR1_SSI         8
#define SPI_CR1_SSM         9
#define SPI_CR1_RXONLY      10
#define SPI_CR1_CRCL        11
#define SPI_CR1_CRCEN       13
#define SPI_CR1_BIDIOE      14
#define SPI_CR1_BIDIMODE    15

/* ================= SPI_CR2 BIT POSITIONS ================= */

#define SPI_CR2_RXDMAEN      0
#define SPI_CR2_TXDMAEN      1
#define SPI_CR2_SSOE         2
#define SPI_CR2_NSSP         3
#define SPI_CR2_FRF          4
#define SPI_CR2_ERRIE        5
#define SPI_CR2_RXNEIE       6
#define SPI_CR2_TXEIE        7
#define SPI_CR2_DS           8    // [11:8] data size
#define SPI_CR2_FRXTH        12
#define SPI_CR2_LDMA_RX      13
#define SPI_CR2_LDMA_TX      14

/* ================= SPI_SR BIT POSITIONS ================= */

#define SPI_SR_RXNE       0   // Receive buffer not empty
#define SPI_SR_TXE        1   // Transmit buffer empty
#define SPI_SR_CRCERR     4
#define SPI_SR_MODF       5
#define SPI_SR_OVR        6
#define SPI_SR_BSY        7   // Busy flag
#define SPI_SR_FRE        8

/* ================= SPI IRQ NUMBERS ================= */

#define IRQ_NO_SPI1      35
#define IRQ_NO_SPI2      36
#define IRQ_NO_SPI3      51


#define ENABLE    1
#define DISABLE   0
#define SET       ENABLE
#define RESET     DISABLE
//#define GPIO_PIN_SET     SET
//#define GPIO_PIN_RESET   RESET

/**************  I2C ****************/
typedef struct {
	volatile uint32_t CR1;       // 0x00
	volatile uint32_t CR2;       // 0x04
	volatile uint32_t OAR1;      // 0x08
	volatile uint32_t OAR2;      // 0x0C
	volatile uint32_t TIMINGR;   // 0x10
	volatile uint32_t TIMEOUTR;  // 0x14
	volatile uint32_t ISR;       // 0x18
	volatile uint32_t ICR;       // 0x1C
	volatile uint32_t PECR;      // 0x20
	volatile uint32_t RXDR;      // 0x24
	volatile uint32_t TXDR;      // 0x28
} I2C_TypeDef;

#define I2C1    ((I2C_TypeDef*)I2C1_BASE)
#define I2C2    ((I2C_TypeDef*)I2C2_BASE)
#define I2C3    ((I2C_TypeDef*)I2C3_BASE)

//CLOCK MACROS
#define I2C1_CLK_ENABLE()   (RCC->APB1ENR1 |= (1 << 21))
#define I2C2_CLK_ENABLE()   (RCC->APB1ENR1 |= (1 << 22))
#define I2C3_CLK_ENABLE()   (RCC->APB1ENR1 |= (1 << 23))

#define I2C_CR1_PE_Pos                0
#define I2C_CR1_TXIE_Pos              1
#define I2C_CR1_RXIE_Pos              2
#define I2C_CR1_ADDRIE_Pos            3
#define I2C_CR1_NACKIE_Pos            4
#define I2C_CR1_STOPIE_Pos            5
#define I2C_CR1_TCIE_Pos              6
#define I2C_CR1_ERRIE_Pos             7
#define I2C_CR1_DNF_Pos               8
#define I2C_CR1_ANFOFF_Pos            12
#define I2C_CR1_TXDMAEN_Pos           14
#define I2C_CR1_RXDMAEN_Pos           15
#define I2C_CR1_SBC_Pos               16
#define I2C_CR1_NOSTRETCH_Pos         17
#define I2C_CR1_WUPEN_Pos             18
#define I2C_CR1_GCEN_Pos              19
#define I2C_CR1_SMBHEN_Pos            20
#define I2C_CR1_SMBDEN_Pos            21
#define I2C_CR1_ALERTEN_Pos           22
#define I2C_CR1_PECEN_Pos             23

/* I2C ICR BIT POSITIONS */

#define I2C_ICR_ADDRCF_Pos          3
#define I2C_ICR_NACKCF_Pos          4
#define I2C_ICR_STOPCF_Pos          5
#define I2C_ICR_BERRCF_Pos          8
#define I2C_ICR_ARLOCF_Pos          9
#define I2C_ICR_OVRCF_Pos           10
#define I2C_ICR_PECCF_Pos           11
#define I2C_ICR_TIMOUTCF_Pos        12
#define I2C_ICR_ALERTCF_Pos         13

/*I2C CR2 BIT POSITIONS  */

#define I2C_CR2_SADD_Pos              0
#define I2C_CR2_RD_WRN_Pos            10
#define I2C_CR2_ADD10_Pos             11
#define I2C_CR2_HEAD10R_Pos           12
#define I2C_CR2_START_Pos             13
#define I2C_CR2_STOP_Pos              14
#define I2C_CR2_NACK_Pos              15
#define I2C_CR2_NBYTES_Pos            16
#define I2C_CR2_RELOAD_Pos            24
#define I2C_CR2_AUTOEND_Pos           25
#define I2C_CR2_PECBYTE_Pos           26

/* I2C ISR BIT POSITIONS*/
#define I2C_ISR_TXE_Pos           0
#define I2C_ISR_TXIS_Pos          1
#define I2C_ISR_RXNE_Pos          2
#define I2C_ISR_ADDR_Pos          3
#define I2C_ISR_NACKF_Pos         4
#define I2C_ISR_STOPF_Pos         5
#define I2C_ISR_TC_Pos            6
#define I2C_ISR_BUSY_Pos          15

/*I2C TIMINGR BIT POSITIONS  */
#define I2C_TIMINGR_SCLL_Pos      0
#define I2C_TIMINGR_SCLH_Pos      8
#define I2C_TIMINGR_SDADEL_Pos    16
#define I2C_TIMINGR_SCLDEL_Pos    20
#define I2C_TIMINGR_PRESC_Pos     28

/* I2C ICR BIT MASKS */

#define I2C_ICR_ADDRCF        (1 << I2C_ICR_ADDRCF_Pos)
#define I2C_ICR_NACKCF        (1 << I2C_ICR_NACKCF_Pos)
#define I2C_ICR_STOPCF        (1 << I2C_ICR_STOPCF_Pos)
#define I2C_ICR_BERRCF        (1 << I2C_ICR_BERRCF_Pos)
#define I2C_ICR_ARLOCF        (1 << I2C_ICR_ARLOCF_Pos)
#define I2C_ICR_OVRCF         (1 << I2C_ICR_OVRCF_Pos)
#define I2C_ICR_PECCF         (1 << I2C_ICR_PECCF_Pos)
#define I2C_ICR_TIMOUTCF      (1 << I2C_ICR_TIMOUTCF_Pos)
#define I2C_ICR_ALERTCF       (1 << I2C_ICR_ALERTCF_Pos)


#define IRQ_NO_I2C1_EV 31
#define IRQ_NO_I2C1_ER 32

#define IRQ_NO_I2C2_EV 33
#define IRQ_NO_I2C2_ER 34


/******************************************************************
 * USART REGISTER DEFINITION STRUCTURE
 ******************************************************************/
typedef struct
{
    volatile uint32_t CR1;      /* 0x00 */
    volatile uint32_t CR2;      /* 0x04 */
    volatile uint32_t CR3;      /* 0x08 */
    volatile uint32_t BRR;      /* 0x0C */
    volatile uint32_t GTPR;     /* 0x10 */
    volatile uint32_t RTOR;     /* 0x14 */
    volatile uint32_t RQR;      /* 0x18 */
    volatile uint32_t ISR;      /* 0x1C */
    volatile uint32_t ICR;      /* 0x20 */
    volatile uint32_t RDR;      /* 0x24 */
    volatile uint32_t TDR;      /* 0x28 */

}USART_RegDef_t;



/******************************************************************
 * USART BASE ADDRESSES (STM32L476RG)
 **********************************************/
#define USART1_BASEADDR      0x40013800U
#define USART2_BASEADDR      0x40004400U
#define USART3_BASEADDR      0x40004800U
#define UART4_BASEADDR       0x40004C00U
#define UART5_BASEADDR       0x40005000U


/******************************************************************
 * USART PERIPHERAL DEFINITIONS
 ******************************************************************/
#define USART1    ((USART_RegDef_t*)USART1_BASEADDR)
#define USART2    ((USART_RegDef_t*)USART2_BASEADDR)
#define USART3    ((USART_RegDef_t*)USART3_BASEADDR)
#define UART4     ((USART_RegDef_t*)UART4_BASEADDR)
#define UART5     ((USART_RegDef_t*)UART5_BASEADDR)


/******************************************************************
 * USART CLOCK ENABLE MACROS
 ******************************************************************/
#define USART1_PCLK_EN()    (RCC->APB2ENR |= (1 << 14))
#define USART2_PCLK_EN()    (RCC->APB1ENR1 |= (1 << 17))
#define USART3_PCLK_EN()    (RCC->APB1ENR1 |= (1 << 18))
#define UART4_PCLK_EN()     (RCC->APB1ENR1 |= (1 << 19))
#define UART5_PCLK_EN()     (RCC->APB1ENR1 |= (1 << 20))


/******************************************************************
 * USART CLOCK DISABLE MACROS
 ******************************************************************/
#define USART1_PCLK_DI()    (RCC->APB2ENR &= ~(1 << 14))
#define USART2_PCLK_DI()    (RCC->APB1ENR1 &= ~(1 << 17))
#define USART3_PCLK_DI()    (RCC->APB1ENR1 &= ~(1 << 18))
#define UART4_PCLK_DI()     (RCC->APB1ENR1 &= ~(1 << 19))
#define UART5_PCLK_DI()     (RCC->APB1ENR1 &= ~(1 << 20))


/******************************************************************
 * USART RESET MACROS
 ******************************************************************/
#define USART1_REG_RESET()   do{ \
(RCC->APB2RSTR |= (1 << 14)); \
(RCC->APB2RSTR &= ~(1 << 14)); \
}while(0)

#define USART2_REG_RESET()   do{ \
(RCC->APB1RSTR1 |= (1 << 17)); \
(RCC->APB1RSTR1 &= ~(1 << 17)); \
}while(0)

#define USART3_REG_RESET()   do{ \
(RCC->APB1RSTR1 |= (1 << 18)); \
(RCC->APB1RSTR1 &= ~(1 << 18)); \
}while(0)

#define UART4_REG_RESET()    do{ \
(RCC->APB1RSTR1 |= (1 << 19)); \
(RCC->APB1RSTR1 &= ~(1 << 19)); \
}while(0)

#define UART5_REG_RESET()    do{ \
(RCC->APB1RSTR1 |= (1 << 20)); \
(RCC->APB1RSTR1 &= ~(1 << 20)); \
}while(0)


/******************************************************************
 * USART MODES
 ******************************************************************/
#define USART_MODE_ONLY_TX        (1 << 3)
#define USART_MODE_ONLY_RX        (1 << 2)
#define USART_MODE_TXRX           ((1 << 2) | (1 << 3))


/******************************************************************
 * USART BAUD RATES
 ******************************************************************/
#define USART_STD_BAUD_1200       1200
#define USART_STD_BAUD_2400       2400
#define USART_STD_BAUD_9600       9600
#define USART_STD_BAUD_19200      19200
#define USART_STD_BAUD_38400      38400
#define USART_STD_BAUD_57600      57600
#define USART_STD_BAUD_115200     115200


/******************************************************************
 * USART PARITY CONTROL
 ******************************************************************/
#define USART_PARITY_DISABLE      0
#define USART_PARITY_EN_EVEN      (1 << 10)
#define USART_PARITY_EN_ODD       ((1 << 10) | (1 << 9))


/******************************************************************
 * USART WORD LENGTH
 ******************************************************************/
#define USART_WORDLEN_8BITS       0
#define USART_WORDLEN_9BITS       (1 << 12)


/******************************************************************
 * USART STOP BITS
 ******************************************************************/
#define USART_STOPBITS_1          0
#define USART_STOPBITS_0_5        1
#define USART_STOPBITS_2          2
#define USART_STOPBITS_1_5        3


/******************************************************************
 * USART FLAGS
 ******************************************************************/
#define USART_FLAG_TXE            (1 << 7)
#define USART_FLAG_TC             (1 << 6)
#define USART_FLAG_RXNE           (1 << 5)


/******************************************************************
 * USART APPLICATION STATES
 ******************************************************************/
#define USART_READY               0
#define USART_BUSY_IN_RX          1
#define USART_BUSY_IN_TX          2


/******************************************************************
 * USART EVENTS
 ******************************************************************/
#define USART_EVENT_TX_CMPLT      1
#define USART_EVENT_RX_CMPLT      2


/******************************************************************
 * ENABLE / DISABLE MACROS
 ******************************************************************/
#define ENABLE                    1
#define DISABLE                   0

#define FLAG_SET                  ENABLE
#define FLAG_RESET                DISABLE


/******************************************************************
 * USART CR1 BIT POSITIONS
 ******************************************************************/
#define USART_CR1_UE_Pos          0
#define USART_CR1_RE_Pos          2
#define USART_CR1_TE_Pos          3
#define USART_CR1_RXNEIE_Pos      5
#define USART_CR1_TXEIE_Pos       7


/******************************************************************
 * USART CR2 BIT POSITIONS
 ******************************************************************/
#define USART_CR2_STOP_Pos        12


#endif /* INC_STM32L476XX_H_ */
