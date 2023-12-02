/*
 * STM32F103x8.h
 *
 * Master Embedded System Diploma
 * Eng. Kareem Abelkader
 */

#ifndef STM32F103X8_H_
#define STM32F103X8_H_

/******************************
 * Includes
 *******************************/
#include "stdlib.h"
#include <stdint.h>

//==========================================================================

/***********************************
 * Base Addresses for Memories
 ***********************************/
#define FLASH_MEM_BASE						0x08000000
#define SESTYM_MEM_BASE						0x1ffff000
#define SRAM_MEM							0x20000000
#define Peripherals_BASE					0x40000000
#define Cortex_Internal_Per					0xe0000000

/*************************************
 * Base Addresses for Bus Peripheral
 ************************************/
//RCC
#define RCC_BASE              (Peripherals_BASE + 0x00021000UL)

//GPIO
#define GPIOA_BASE							0x40010800
#define GPIOB_BASE							0x40010c00
#define GPIOC_BASE							0x40011000
#define GPIOD_BASE							0x40011400

//AFIO
#define AFIO_BASE							0x40010000

//Timer
#define TIM1_BASE             	(Peripherals_BASE + 0x00012C00UL)
#define IWDG_BASE             	(Peripherals_BASE + 0x00003000UL)
#define TIM2_BASE             	(Peripherals_BASE + 0x00000800UL)
#define TIM3_BASE             	(Peripherals_BASE + 0x00000400UL)
#define TIM4_BASE             	(Peripherals_BASE + 0x00000000UL)

//USART
#define USART1_BASE							0x40013800
#define USART2_BASE							0x40004400
#define USART3_BASE							0x40004800


//================================================================================

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: GPIO
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
typedef struct {
	volatile uint32_t CRL;		//Port configuration register low (P0:p7)
	volatile uint32_t CRH;		//Port configuration register high (P8:P15)
	volatile uint32_t IDR;		//Port input data register
	volatile uint32_t ODR;		//Port output data register
	volatile uint32_t BSRR;		//Port bit set/reset register
	volatile uint32_t BRR;		//Port bit reset register
	volatile uint32_t LCKR;		//Port configuration lock register
}GPIO_TypeDef;

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: AFIO
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
typedef struct {
	volatile uint32_t EVCR;			//Event control register
	volatile uint32_t MAPR;			//AF remap and debug I/O configuration register
	volatile uint32_t EXTICR[4];		//External interrupt configuration register 1
	volatile uint32_t RESERVED0;
	volatile uint32_t MAPR2;		//AF remap and debug I/O configuration register2
}AFIO_TypeDef;

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: RCC
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
typedef struct
{
	volatile uint32_t CR;
	volatile uint32_t CFGR;
	volatile uint32_t CIR;
	volatile uint32_t APB2RSTR;
	volatile uint32_t APB1RSTR;
	volatile uint32_t AHBENR;
	volatile uint32_t APB2ENR;
	volatile uint32_t APB1ENR;
	volatile uint32_t BDCR;
	volatile uint32_t CSR;
	volatile uint32_t AHBSTR;
	volatile uint32_t CFGR2;
} RCC_TypeDef;

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//Peripheral register: TIM1
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
typedef struct
{
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t SMCR;
	volatile uint32_t DIER;
	volatile uint32_t SR;
	volatile uint32_t EGR;
	volatile uint32_t CCMR1;
	volatile uint32_t CCMR2;
	volatile uint32_t CCER;
	volatile uint32_t CNT;
	volatile uint32_t PSC;
	volatile uint32_t ARR;
	volatile uint32_t RCR;//not included in TIM2 , TIM3 and TIM4
	volatile uint32_t CCR1;
	volatile uint32_t CCR2;
	volatile uint32_t CCR3;
	volatile uint32_t CCR4;
	volatile uint32_t BDTR;//not included in TIM2 , TIM3 and TIM4
	volatile uint32_t DCR;
	volatile uint32_t DMAR;
} TIMx_TypeDef;

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: IWDG
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
typedef struct
{
	volatile uint32_t KR;
	volatile uint32_t PR;
	volatile uint32_t RLR;
	volatile uint32_t SR;
} IWDG_TypeDef;

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: USART
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
typedef struct{
	volatile uint32_t SR;
	volatile uint32_t DR;
	volatile uint32_t BRR;
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t CR3;
	volatile uint32_t GTPR;
}USART_TypeDef;


//================================================================================

/*************************************
 * Peripheral instant
 ************************************/

//RCC
#define RCC                 ((RCC_TypeDef *)RCC_BASE)

//GPIO
//GPIO A/B are fully included
#define GPIOA				((GPIO_TypeDef *)GPIOA_BASE)
#define GPIOB				((GPIO_TypeDef *)GPIOB_BASE)
//GPIO C/D are partial included
#define GPIOC				((GPIO_TypeDef *)GPIOC_BASE)
#define GPIOD				((GPIO_TypeDef *)GPIOD_BASE)

//AFIO
#define AFIO 				 ((AFIO_TypeDef *) AFIO_BASE)

//TIMER
#define TIM1                 ((TIMx_TypeDef *)TIM1_BASE)
#define TIM2                 ((TIMx_TypeDef *)TIM2_BASE)
#define TIM3                 ((TIMx_TypeDef *)TIM3_BASE)
#define TIM4                 ((TIMx_TypeDef *)TIM4_BASE)
#define IWDG                 ((IWDG_TypeDef *)IWDG_BASE)

//USART
#define USART1				 ((USART_TypeDef *)USART1_BASE)
#define USART2				 ((USART_TypeDef *)USART2_BASE)
#define USART3				 ((USART_TypeDef *)USART3_BASE)
//================================================================================

//EXTI
#define EXTI_BASE							   0x40010400

#define EXTI				    	((EXTI_TypeDef* )EXTI_BASE)


//AFIO
#define AFIO_BASE                              0x40010000

//NVIC
#define NVIC_BASE							   0xE000E100
#define NVIC_ISER0				*(volatile uint16_t*)(NVIC_BASE + 0x00)
#define NVIC_ISER1				*(volatile uint16_t*)(NVIC_BASE + 0x04)
#define NVIC_ISER2				*(volatile uint16_t*)(NVIC_BASE + 0x08)
#define NVIC_ICER0				*(volatile uint16_t*)(NVIC_BASE + 0x80)
#define NVIC_ICER1				*(volatile uint16_t*)(NVIC_BASE + 0x84)
#define NVIC_ICER2				*(volatile uint16_t*)(NVIC_BASE + 0x88)


//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: EXTI
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
typedef struct{
	volatile uint32_t IMR;
	volatile uint32_t EMR;
	volatile uint32_t RTSR;
	volatile uint32_t FTSR;
	volatile uint32_t SWIER;
	volatile uint32_t PR;
}EXTI_TypeDef;


/*************************************
 * EXTI Macros
 ************************************/

//micors for EXTI
#define EXTI0PA0  (EXTI_GPIO_Maping_t){EXTI0,GPIOA,PIN_0,EXTI0_IRQ}
#define EXTI0PB0  (EXTI_GPIO_Maping_t){EXTI0, GPIOB,PIN_0,EXTI0_IRQ}
#define EXTI0PC0  (EXTI_GPIO_Maping_t){EXTI0, GPIOC,PIN_0,EXTI0_IRQ}
#define EXTI0PD0  (EXTI_GPIO_Maping_t){EXTI0, GPIOD,PIN_0,EXTI0_IRQ}
#define EXTI1PA1  (EXTI_GPIO_Maping_t){EXTI1,GPIOA ,PIN_1,EXTI1_IRQ}
#define EXTI1PB1  (EXTI_GPIO_Maping_t){EXTI1, GPIOB,PIN_1,EXTI1_IRQ}
#define EXTI1PC1  (EXTI_GPIO_Maping_t){EXTI1, GPIOC,PIN_1,EXTI1_IRQ}
#define EXTI1PD1  (EXTI_GPIO_Maping_t){EXTI1, GPIOD,PIN_1,EXTI1_IRQ}
#define EXTI2PA2  (EXTI_GPIO_Maping_t){EXTI2,GPIOA ,PIN_2,EXTI2_IRQ}
#define EXTI2PB2  (EXTI_GPIO_Maping_t){EXTI2, GPIOB,PIN_2,EXTI2_IRQ}
#define EXTI2PC2  (EXTI_GPIO_Maping_t){EXTI2, GPIOC,PIN_2,EXTI2_IRQ}
#define EXTI2PD2  (EXTI_GPIO_Maping_t){EXTI2, GPIOD,PIN_2,EXTI2_IRQ}
#define EXTI3PA3  (EXTI_GPIO_Maping_t){EXTI3,GPIOA ,PIN_3,EXTI3_IRQ}
#define EXTI3PB3  (EXTI_GPIO_Maping_t){EXTI3, GPIOB,PIN_3,EXTI3_IRQ}
#define EXTI3PC3  (EXTI_GPIO_Maping_t){EXTI3, GPIOC,PIN_3,EXTI3_IRQ}
#define EXTI3PD3  (EXTI_GPIO_Maping_t){EXTI3, GPIOD,PIN_3,EXTI3_IRQ}
#define EXTI4PA4  (EXTI_GPIO_Maping_t){EXTI4,GPIOA ,PIN_4,EXTI4_IRQ}
#define EXTI4PB4  (EXTI_GPIO_Maping_t){EXTI4, GPIOB,PIN_4,EXTI4_IRQ}
#define EXTI4PC4  (EXTI_GPIO_Maping_t){EXTI4, GPIOC,PIN_4,EXTI4_IRQ}
#define EXTI4PD4  (EXTI_GPIO_Maping_t){EXTI4, GPIOD,PIN_4,EXTI4_IRQ}
#define EXTI5PA5  (EXTI_GPIO_Maping_t){EXTI5,GPIOA ,PIN_5,EXTI5_IRQ}
#define EXTI5PB5  (EXTI_GPIO_Maping_t){EXTI5, GPIOB,PIN_5,EXTI5_IRQ}
#define EXTI5PC5  (EXTI_GPIO_Maping_t){EXTI5, GPIOC,PIN_5,EXTI5_IRQ}
#define EXTI5PD5  (EXTI_GPIO_Maping_t){EXTI5, GPIOD,PIN_5,EXTI5_IRQ}
#define EXTI6PA6  (EXTI_GPIO_Maping_t){EXTI6,GPIOA ,PIN_6,EXTI6_IRQ}
#define EXTI6PB6  (EXTI_GPIO_Maping_t){EXTI6, GPIOB,PIN_6,EXTI6_IRQ}
#define EXTI6PC6  (EXTI_GPIO_Maping_t){EXTI6, GPIOC,PIN_6,EXTI6_IRQ}
#define EXTI6PD6  (EXTI_GPIO_Maping_t){EXTI6, GPIOD,PIN_6,EXTI6_IRQ}
#define EXTI7PA7  (EXTI_GPIO_Maping_t){EXTI7,GPIOA ,PIN_7,EXTI7_IRQ}
#define EXTI7PB7  (EXTI_GPIO_Maping_t){EXTI7, GPIOB,PIN_7,EXTI7_IRQ}
#define EXTI7PC7  (EXTI_GPIO_Maping_t){EXTI7, GPIOC,PIN_7,EXTI7_IRQ}
#define EXTI7PD7  (EXTI_GPIO_Maping_t){EXTI7, GPIOD,PIN_7,EXTI7_IRQ}
#define EXTI8PA8  (EXTI_GPIO_Maping_t){EXTI8,GPIOA ,PIN_8,EXTI8_IRQ}
#define EXTI8PB8  (EXTI_GPIO_Maping_t){EXTI8, GPIOB,PIN_8,EXTI8_IRQ}
#define EXTI8PC8  (EXTI_GPIO_Maping_t){EXTI8, GPIOC,PIN_8,EXTI8_IRQ}
#define EXTI8PD8  (EXTI_GPIO_Maping_t){EXTI8, GPIOD,PIN_8,EXTI8_IRQ}
#define EXTI9PA9  (EXTI_GPIO_Maping_t){EXTI9,GPIOA ,PIN_9,EXTI9_IRQ}
#define EXTI9PB9  (EXTI_GPIO_Maping_t){EXTI9, GPIOB,PIN_9,EXTI9_IRQ}
#define EXTI9PC9  (EXTI_GPIO_Maping_t){EXTI9, GPIOC,PIN_9,EXTI9_IRQ}
#define EXTI9PD9  (EXTI_GPIO_Maping_t){EXTI9, GPIOD,PIN_9,EXTI9_IRQ}
#define EXTI10PA10  (EXTI_GPIO_Maping_t){EXTI10,GPIOA ,PIN_10,EXTI10_IRQ}
#define EXTI10PB10  (EXTI_GPIO_Maping_t){EXTI10, GPIOB,PIN_10,EXTI10_IRQ}
#define EXTI10PC10  (EXTI_GPIO_Maping_t){EXTI10, GPIOC,PIN_10,EXTI10_IRQ}
#define EXTI10PD10  (EXTI_GPIO_Maping_t){EXTI10, GPIOD,PIN_10,EXTI10_IRQ}
#define EXTI11PA11  (EXTI_GPIO_Maping_t){EXTI11,GPIOA ,PIN_11,EXTI11_IRQ}
#define EXTI11PB11  (EXTI_GPIO_Maping_t){EXTI11, GPIOB,PIN_11,EXTI11_IRQ}
#define EXTI11PC11  (EXTI_GPIO_Maping_t){EXTI11, GPIOC,PIN_11,EXTI11_IRQ}
#define EXTI11PD11  (EXTI_GPIO_Maping_t){EXTI11, GPIOD,PIN_11,EXTI11_IRQ}
#define EXTI12PA12  (EXTI_GPIO_Maping_t){EXTI12,GPIOA ,PIN_12,EXTI12_IRQ}
#define EXTI12PB12  (EXTI_GPIO_Maping_t){EXTI12, GPIOB,PIN_12,EXTI12_IRQ}
#define EXTI12PC12  (EXTI_GPIO_Maping_t){EXTI12, GPIOC,PIN_12,EXTI12_IRQ}
#define EXTI12PD12  (EXTI_GPIO_Maping_t){EXTI12, GPIOD,PIN_12,EXTI12_IRQ}
#define EXTI13PA13  (EXTI_GPIO_Maping_t){EXTI13,GPIOA ,PIN_13,EXTI13_IRQ}
#define EXTI13PB13  (EXTI_GPIO_Maping_t){EXTI13, GPIOB,PIN_13,EXTI13_IRQ}
#define EXTI13PC13  (EXTI_GPIO_Maping_t){EXTI13, GPIOC,PIN_13,EXTI13_IRQ}
#define EXTI13PD13  (EXTI_GPIO_Maping_t){EXTI13, GPIOD,PIN_13,EXTI13_IRQ}
#define EXTI14PA14  (EXTI_GPIO_Maping_t){EXTI14,GPIOA ,PIN_14,EXTI14_IRQ}
#define EXTI14PB14  (EXTI_GPIO_Maping_t){EXTI14, GPIOB,PIN_14,EXTI14_IRQ}
#define EXTI14PC14  (EXTI_GPIO_Maping_t){EXTI14, GPIOC,PIN_14,EXTI14_IRQ}
#define EXTI14PD14  (EXTI_GPIO_Maping_t){EXTI14, GPIOD,PIN_14,EXTI14_IRQ}
#define EXTI15PA15  (EXTI_GPIO_Maping_t){EXTI15,GPIOA ,PIN_15,EXTI15_IRQ}
#define EXTI15PB15  (EXTI_GPIO_Maping_t){EXTI15, GPIOB,PIN_15,EXTI15_IRQ}
#define EXTI15PC15  (EXTI_GPIO_Maping_t){EXTI15, GPIOC,PIN_15,EXTI15_IRQ}
#define EXTI15PD15  (EXTI_GPIO_Maping_t){EXTI15, GPIOD,PIN_15,EXTI15_IRQ}

//EXTI
#define EXTI0				0
#define EXTI0_IRQ			6
#define EXTI1_IRQ			7
#define EXTI2_IRQ			8
#define EXTI3_IRQ			9
#define EXTI4_IRQ			10
#define EXTI5_IRQ			23
#define EXTI6_IRQ			23
#define EXTI7_IRQ			23
#define EXTI8_IRQ			23
#define EXTI9_IRQ			23
#define EXTI10_IRQ			40
#define EXTI11_IRQ			40
#define EXTI12_IRQ			40
#define EXTI13_IRQ			40
#define EXTI14_IRQ			40
#define EXTI15_IRQ			40
//----------------- timer interrupt IRQ -------------------------------------------------
#define TIM1_BRK             0
#define TIM1_UP              1
#define TIM1_TRG_COM         2
#define TIM1_CC              3
#define TIM2_                 4
#define TIM3_                 5
#define TIM4_                 6
//************************************************


//----------------- I2C interrupt IRQ -------------------------------------------------
#define I2C1_EV                 0
#define I2C1_ER                 1
#define I2C2_EV                 2
#define I2C2_ER 				3
//----------------- Uart interrupt IRQ -------------------------------------------------

#define USART1_                 0
#define USART2_                 1
#define USART3_                 2
//////////////////////////////////////////
// to access  Peripheral_T and PR  max 19
//for UART
#define USART1_I                5
#define USART2_I                6
#define USART3_I                7
//-----------------------------------------------------------------------------------

//for I2C
#define I2C1_EV_I                8
#define I2C1_ER_I                9
#define I2C2_EV_I                10
#define I2C2_ER_I                11
//-----------------------------------------------------------------------------------
//for TIMER
#define TIM1_BRK_I          11
#define TIM1_UP_I           13
#define TIM1_TRG_COM_I      14
#define TIM1_CC_I           15
#define TIM2_I                16
#define TIM3_I                17
#define TIM4_I                18
//-----------------------------------------------------------------------------------




//NVIC_EXTI_Enable
#define NVIC_IRQ6_EXTI0_Enable 			(NVIC_ISER0 |= 1<<6)
#define NVIC_IRQ7_EXTI1_Enable 			(NVIC_ISER0 |= 1<<7)
#define NVIC_IRQ8_EXTI2_Enable 			(NVIC_ISER0 |= 1<<8)
#define NVIC_IRQ9_EXTI3_Enable 			(NVIC_ISER0 |= 1<<9)
#define NVIC_IRQ10_EXTI4_Enable 			(NVIC_ISER0 |= 1<<10)
#define NVIC_IRQ23_EXTI5_9_Enable 			(NVIC_ISER0 |= 1<<23)
#define NVIC_IRQ40_EXTI10_15_Enable 		(NVIC_ISER1 |= 1<<8)  //40 - 32 = 8

//---------------------- Enable_Timer_NVIC ---------------------------------------------------------------
#define NVIC_TIM1_BRK_Enable     	 (NVIC_ISER0 |= 1<<24)
#define NVIC_TIM1_UP_Enable          (NVIC_ISER0 |= 1<<25)
#define NVIC_TIM1_TRG_COM_Enable     (NVIC_ISER0 |= 1<<26)
#define NVIC_TIM1_CC_Enable          (NVIC_ISER0 |= 1<<27)
#define NVIC_TIM2_Enable             (NVIC_ISER0 |= 1<<28)
#define NVIC_TIM3_BRK_Enable         (NVIC_ISER0 |= 1<<29)
#define NVIC_TIM4_BRK_Enable         (NVIC_ISER0 |= 1<<30)
//---------------------- Enable_I2C_NVIC ---------------------------------------------------------------
#define NVIC_I2C1_EV_Enable                (NVIC_ISER0 |= 1<<31)
#define NVIC_I2C1_ER_Enable                (NVIC_ISER1 |= 1<<0) //32-32
#define NVIC_I2C2_EV_Enable                (NVIC_ISER1 |= 1<<1) //33-32
#define NVIC_I2C2_ER_Enable                (NVIC_ISER1 |= 1<<2) //34-32
//---------------------- Enable_UART_NVIC ---------------------------------------------------------------
#define NVIC_USART1_Enable                (NVIC_ISER1 |= 1<<5)
#define NVIC_USART2_Enable                (NVIC_ISER1 |= 1<<6)
#define NVIC_USART3_Enable                (NVIC_ISER1 |= 1<<7)
//---------------------- Disable  ------------------------------
//-----------------------Disable_EXTI------------------------------
#define NVIC_IRQ6_EXTI0_Disable			(NVIC_ICER0 |= (1<<6)
#define NVIC_IRQ7_EXTI1_Disable		  	(NVIC_ICER0 |= (1<<7)
#define NVIC_IRQ8_EXTI2_Disable			(NVIC_ICER0 |= (1<<8)
#define NVIC_IRQ9_EXTI3_Disable			(NVIC_ICER0 |= 1<<9)
#define NVIC_IRQ10_EXTI4_Disable		(NVIC_ICER0 |= 1<<10)
#define NVIC_IRQ23_EXTI5_9_Disable      (NVIC_ICER0 |= 1<<23)
#define NVIC_IRQ40_EXTI10_15_Disable	(NVIC_ICER1 |= 1<<8)  //40 - 32 = 8

//---------------------- Diable_Timer_NVIC ---------------------------------------------------------------
#define NVIC_TIM1_BRK_Disable     	  (NVIC_ICER0 |= 1<<24)
#define NVIC_TIM1_UP_Disable          (NVIC_ICER0 |= 1<<25)
#define NVIC_TIM1_TRG_COM_Disable     (NVIC_ICER0 |= 1<<26)
#define NVIC_TIM1_CC_Disable          (NVIC_ICER0 |= 1<<27)
#define NVIC_TIM2_Disable             (NVIC_ICER0 |= 1<<28)
#define NVIC_TIM3_BRK_Disable         (NVIC_ICER0 |= 1<<29)
#define NVIC_TIM4_BRK_Disable         (NVIC_ICER0 |= 1<<30)
//---------------------- Disable_I2C_NVIC ---------------------------------------------------------------
#define NVIC_I2C1_EV_Disable                (NVIC_ICER0 |= 1<<31)
#define NVIC_I2C1_ER_Disable                (NVIC_ICER1 |= 1<<0) //32-32
#define NVIC_I2C2_EV_Disable                (NVIC_ICER1 |= 1<<1) //33-32
#define NVIC_I2C2_ER_Disable                (NVIC_ICER1 |= 1<<2) //34-32
//---------------------- Disable_UART_NVIC ---------------------------------------------------------------
#define NVIC_USART1_Disable                (NVIC_ICER1 |= 1<<5)
#define NVIC_USART2_Disable                (NVIC_ICER1 |= 1<<6)
#define NVIC_USART3_Disable                (NVIC_ICER1 |= 1<<7)
//===============================================================================================


//=====================================================================================
//************************************



#endif /* STM32F103X8_H_ */
