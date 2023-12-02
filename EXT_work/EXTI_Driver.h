#ifndef EITI_Driver_H
#define EITI_Driver_H
#include "GPIO.h"
#include<stdlib.h>
#include<stdint.h>
#include "STM32F103x8.h"




//=======================================================================================




typedef struct
{
	uint16_t  EXI_Inputline_number;
	GPIO_TypeDef*   GPIO_Port;
	uint16_t   GPIO_PIN;
	uint8_t IVT_IRQ_Number ;
}EXTI_GPIO_Maping_t;

typedef struct
{
	EXTI_GPIO_Maping_t EXTI_PIN;

	uint8_t    Trigger_Case ;

	uint8_t    IQR_EN ;

	void (* P_IQR_CallBack)(void);

}EXTI_PinConfig_t;

typedef struct
{
	void (* P_Peripheral_CallBack)(void);  // to pass the function you
	                                     	// need to do when interrupt happend

	uint8_t    Peripheral_T ;//should be choese from micros
							  // Peripheral interrupt IRQ

	uint8_t    Peripheral_IQR ; //should be choese from micros
								// Peripheral interrupt IRQ
	uint8_t    IQR_EN ;
}Software_t;

//EXTI_Trigger
#define EXTI_Trigger_RISING       0
#define EXTI_Trigger_FALLING      1
#define EXTI_Trigger_BOTH         2

// EXTI_IQR_define
#define EXTI_IQR_Disable	 0
#define EXTI_IQR_Enable      1
//API's
void MCAL_EXTI_GPIO_Init (EXTI_PinConfig_t* EXTI_Config);
void MCAL_EXTI_GPIO_DeInit (void);
void MCAL_EXTI_GPIO_Upate (EXTI_PinConfig_t* EXTI_Config);

void MCAL_UART_Init (Software_t* Function_callBack );
void MCAL_TIMER_Init (Software_t* Function_callBack );
void MCAL_I2C_Init (Software_t* Function_callBack );
void MCAL_Event_Init(void); //to enable the Event mask 19



#endif
