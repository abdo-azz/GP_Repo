#include "EXTI_Driver.h"
#include "GPIO.h"


//=====================================================================================

void (*GP_IRQ_EXTI_callback[15] ) (void) ;
void (*GP_IRQ_Timer_callback[6] ) (void) ;
void (*GP_IRQ_I2C_callback[3] ) (void) ;
void (*GP_IRQ_UART_callback[2] ) (void) ;

//Enable && Disable NVIC EXTI
void Disable_NVIC(uint16_t IRQ)
{
	switch (IRQ)
	{
	case 0: 	(*(volatile uint16_t*)(0xE000E100 + 0x80) |= 1<<6);
	break;
	case 1:	(*(volatile uint16_t*)(0xE000E100 + 0x80) |= 1<<7);
	break;
	case 2: 	(*(volatile uint16_t*)(0xE000E100 + 0x80) |= 1<<8);
	break;
	case 3: NVIC_IRQ9_EXTI3_Disable;
	break;
	case 4: NVIC_IRQ10_EXTI4_Disable;
	break;
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		NVIC_IRQ23_EXTI5_9_Disable;
		break;
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
		NVIC_IRQ40_EXTI10_15_Disable;
		break;
	}

}

void Enable_NVIC(uint16_t IRQ)
{
	switch (IRQ)
	{
	case 0: 	NVIC_IRQ6_EXTI0_Enable;
	break;
	case 1:	NVIC_IRQ7_EXTI1_Enable;
	break;
	case 2: 	NVIC_IRQ8_EXTI2_Enable;
	break;
	case 3: NVIC_IRQ9_EXTI3_Enable;
	break;
	case 4: NVIC_IRQ10_EXTI4_Enable;
	break;
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		NVIC_IRQ23_EXTI5_9_Enable;
		break;
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
		NVIC_IRQ40_EXTI10_15_Enable;
		break;
	}

}
//----------------------------------------------------------

//Enable && Disable NVIC UART
void Enable_NVIC_UART (uint16_t IRQ)
{
	switch (IRQ)
	{
	case 0: 	NVIC_USART1_Enable;
	break;
	case 1:	NVIC_USART2_Enable;
	break;
	case 2: 	NVIC_USART3_Enable;
	break;
	}
}
void Disable_NVIC_UART (uint16_t IRQ)
{
	switch (IRQ)
	{
	case 0: 	NVIC_USART1_Disable;
	break;
	case 1:	NVIC_USART2_Disable;
	break;
	case 2: 	NVIC_USART3_Disable;
	break;
	}
}
//----------------------------------------------------------

//Enable && Disable NVIC TIMER

void Disable_NVIC_TIMER (uint16_t IRQ)
{

switch (IRQ)
{
case 0: 	NVIC_TIM1_BRK_Disable;
break;
case 1:	    NVIC_TIM1_UP_Disable;
break;
case 2: 	NVIC_TIM1_TRG_COM_Disable;
break;
case 3: 	NVIC_TIM1_CC_Disable;
break;
case 4:	    NVIC_TIM2_Disable;
break;
case 5: 	NVIC_TIM3_BRK_Disable;
break;
case 6: 	NVIC_TIM4_BRK_Disable;
break;
}
}

void Enable_NVIC_TIMER (uint16_t IRQ)
{

switch (IRQ)
{
case 0: 	NVIC_TIM1_BRK_Enable;
break;
case 1:	    NVIC_TIM1_UP_Enable;
break;
case 2: 	NVIC_TIM1_TRG_COM_Enable;
break;
case 3: 	NVIC_TIM1_BRK_Enable;
break;
case 4:	    NVIC_TIM1_CC_Enable;
break;
case 5: 	NVIC_TIM2_Enable;
break;
case 6: 	NVIC_TIM3_BRK_Enable;
break;
case 7:	    NVIC_TIM4_BRK_Enable;
break;

}
}

//----------------------------------------------------------

//Enable && Disable NVIC I2C

void Enable_NVIC_I2C (uint16_t IRQ)
{
	switch (IRQ)
	{
	case 0: 	NVIC_I2C1_EV_Enable;
	break;
	case 1:	    NVIC_I2C1_ER_Enable;
	break;
	case 2: 	NVIC_I2C2_EV_Enable;
	break;
	case 3:	    NVIC_I2C2_ER_Enable;
	break;
	}
}
void Disable_NVIC_I2C (uint16_t IRQ)
{
	switch (IRQ)
	{
	case 0: 	NVIC_I2C1_EV_Disable;
	break;
	case 1:	    NVIC_I2C1_ER_Disable;
	break;
	case 2: 	NVIC_I2C2_EV_Disable;
	break;
	case 3:	    NVIC_I2C2_ER_Disable;
	break;
	}
}

//=====================================================================================


#define AFIO_GPIO_EXTI(x) ( (x==GPIOA)  ?0:\
		(x==GPIOB)  ?1:\
				(x==GPIOC)  ?2:\
						(x==GPIOD)  ?3:0 )



/*************************************
 * Genaric function instant
 ************************************/

void Update_EXTI (EXTI_PinConfig_t* EXTI_Config)
{
	GPIO_PinConfig_t Pincfg ;
	Pincfg.Pin_Num =EXTI_Config->EXTI_PIN.GPIO_PIN ;
	Pincfg.Pin_Mode = INPUT_FLO_MODE ;
	MCAL_GPIO_INIT(EXTI_Config->EXTI_PIN.GPIO_Port,&Pincfg);
	//(EXTI_Config->EXTI_PIN.GPIO_Port,&Pincfg);
	//update AFIO
	uint8_t AFIO_EXTI_Index= EXTI_Config->EXTI_PIN.EXI_Inputline_number /4 ;
	uint8_t AFIO_EXTI_Position= (EXTI_Config->EXTI_PIN.EXI_Inputline_number % 4)*4;
	//clear bit
	AFIO-> EXTICR[AFIO_EXTI_Index] &=~ (0xf<<AFIO_EXTI_Position);
	AFIO->EXTICR[AFIO_EXTI_Index] |= ((AFIO_GPIO_EXTI(EXTI_Config->EXTI_PIN.GPIO_Port)&0xF)<<AFIO_EXTI_Position);

	// Rising And Falling Edg
	// SET  all value
	EXTI->RTSR &=~ (1<<EXTI_Config->EXTI_PIN.EXI_Inputline_number);
	EXTI->FTSR &=~ (1<<EXTI_Config->EXTI_PIN.EXI_Inputline_number);

	if(EXTI_Trigger_RISING==0)
	{
		EXTI->RTSR |= (1<<EXTI_Config->EXTI_PIN.EXI_Inputline_number);

	}
	else if(EXTI_Trigger_FALLING==1)
	{
		EXTI->FTSR |= (1<<EXTI_Config->EXTI_PIN.EXI_Inputline_number);


	} else if(EXTI_Trigger_BOTH==2)
	{

		EXTI->FTSR |= (1<<EXTI_Config->EXTI_PIN.EXI_Inputline_number);
		EXTI->RTSR |= (1<<EXTI_Config->EXTI_PIN.EXI_Inputline_number);

	}
	//update IRQ_Handler

	GP_IRQ_EXTI_callback[EXTI_Config->EXTI_PIN.EXI_Inputline_number]=EXTI_Config->P_IQR_CallBack;

	//Enable or Disable IRQ & NVIC
	if(EXTI_Config->IQR_EN==EXTI_IQR_Enable)
	{
		//Enable IRQ
		EXTI->IMR |=(1<<EXTI_Config->EXTI_PIN.EXI_Inputline_number);
		// Enable NVIC
		Enable_NVIC (EXTI_Config->EXTI_PIN.EXI_Inputline_number) ;


	}
	else
	{
		EXTI->IMR &=~(1<<EXTI_Config->EXTI_PIN.EXI_Inputline_number);
		Disable_NVIC (EXTI_Config->EXTI_PIN.EXI_Inputline_number) ;

	}


}
void MCAL_EXTI_GPIO_DeInit (void)
{
	EXTI->IMR =		0x00000000;
	EXTI->EMR =		0x00000000;
	EXTI->RTSR =	0x00000000;
	EXTI->FTSR =	0x00000000;
	EXTI->SWIER=	0x00000000;
	//rc_w1
	EXTI->PR=	0xffffffff;
	//------------------------------------------------------
	//Disable the IRQ handler
	//NVIC_IRQ9_EXTI0_Disable			;

	(*(volatile uint16_t*)(0xE000E100 + 0x80) |= 1<<6);
	//	  NVIC_IRQ7_EXTI1_Enable			;

	(*(volatile uint16_t*)(0xE000E100 + 0x80) |= 1<<7);
	// NVIC_IRQ9_EXTI2_Disable			;
	(*(volatile uint16_t*)(0xE000E100 + 0x80) |= 1<<8);



	NVIC_IRQ9_EXTI3_Disable			;
	NVIC_IRQ10_EXTI4_Disable	     	;
	NVIC_IRQ23_EXTI5_9_Disable		;
	NVIC_IRQ40_EXTI10_15_Disable		;

	//Disable the Timer
	NVIC_TIM1_BRK_Disable ;
	NVIC_TIM1_UP_Disable ;
	NVIC_TIM1_TRG_COM_Disable ;
	NVIC_TIM1_CC_Disable ;
	NVIC_TIM2_Disable;
	NVIC_TIM3_BRK_Disable ;
	NVIC_TIM3_BRK_Disable;
	//Disable the I2C
	NVIC_I2C1_EV_Disable ;
	NVIC_I2C1_ER_Disable ;
	NVIC_I2C2_EV_Disable ;
	NVIC_I2C2_ER_Disable ;
	//Disable the UART
	NVIC_USART1_Disable ;
	NVIC_USART2_Disable ;
	NVIC_USART3_Disable ;


}

void MCAL_EXTI_GPIO_Init (EXTI_PinConfig_t* EXTI_Config)
{
	Update_EXTI(EXTI_Config);
}
void MCAL_EXTI_GPIO_Upate (EXTI_PinConfig_t* EXTI_Config)
{
	Update_EXTI(EXTI_Config);

}
void MCAL_UART_Init (Software_t* Function_callBack )
{
	Software_t fun;
	//update IRQ_Handler
	GP_IRQ_UART_callback[fun.Peripheral_IQR]= fun.P_Peripheral_CallBack;

	if(Function_callBack->IQR_EN ==EXTI_IQR_Enable)
	{
		//enable SWIER
		EXTI->SWIER |= (1<<fun.Peripheral_T);
		//Enable IRQ
		EXTI->IMR    |= (1<<fun.Peripheral_T);
		// Enable NVIC
		Enable_NVIC_UART(fun.Peripheral_T) ;

	}
	else
	{
		//disable IRQ
		EXTI->IMR  &=~(1<<fun.Peripheral_T);
		//Disable NVIC
		Disable_NVIC_UART(fun.Peripheral_T);
	}

}
void MCAL_TIMER_Init (Software_t* Function_callBack )
{
	Software_t fun;
	//update IRQ_Handler
	GP_IRQ_Timer_callback[fun.Peripheral_IQR]= fun.P_Peripheral_CallBack;

	if(Function_callBack->IQR_EN ==EXTI_IQR_Enable)
	{
		//enable SWIER
		EXTI->SWIER |= (1<<fun.Peripheral_T);
		//Enable IRQ
		EXTI->IMR    |= (1<<fun.Peripheral_T);
		// Enable NVIC
		Enable_NVIC_TIMER(fun.Peripheral_T) ;

	}
	else
	{
		//disable IRQ
		EXTI->IMR  &=~(1<<fun.Peripheral_T);
		//Disable NVIC
		Disable_NVIC_TIMER(fun.Peripheral_T);
	}

}

void MCAL_I2C_Init (Software_t* Function_callBack )
{

	Software_t fun;
	//update IRQ_Handler
	GP_IRQ_Timer_callback[fun.Peripheral_IQR]= fun.P_Peripheral_CallBack;

	if(Function_callBack->IQR_EN ==EXTI_IQR_Enable)
	{
		//enable SWIER
		EXTI->SWIER |= (1<<fun.Peripheral_T);
		//Enable IRQ
		EXTI->IMR    |= (1<<fun.Peripheral_T);
		// Enable NVIC
		Enable_NVIC_I2C(fun.Peripheral_T) ;

	}
	else
	{
		//disable IRQ
		EXTI->IMR  &=~ (1<<fun.Peripheral_T);
		//Disable NVIC
		Disable_NVIC_I2C(fun.Peripheral_T);
	}

}
void MCAL_Event_Enable(void)
{
	EXTI->PR =(1<<19);
	EXTI->EMR =(1<<19);
}


//==================================================================================
//=======================  ISR Function  ====================================================
//==================================================================================

void EXTI0_IRQHandler(void)
{
	EXTI->PR = (1<<0) ;
	GP_IRQ_EXTI_callback[0] () ;

}
void EXTI1_IRQHandler(void)
{
	EXTI->PR = (1<<1) ;
	GP_IRQ_EXTI_callback[1] () ;

}
void EXTI2_IRQHandler(void)
{
	EXTI->PR = (1<<2) ;
	GP_IRQ_EXTI_callback[2] () ;

}
void EXTI3_IRQHandler(void)
{
	EXTI->PR = (1<<3) ;
	GP_IRQ_EXTI_callback[3] () ;

}
void EXTI4_IRQHandler(void)
{
	EXTI->PR = (1<<4) ;
	GP_IRQ_EXTI_callback[4] () ;

}
void EXTI9_5_IRQHandler(void)
{
	if (EXTI->PR & 1<<5) {EXTI->PR = (1<<5)  ;   GP_IRQ_EXTI_callback[5] () ;}
	if (EXTI->PR & 1<<6) {EXTI->PR = (1<<6) ;	GP_IRQ_EXTI_callback[6] () ;}
	if (EXTI->PR & 1<<7) {EXTI->PR = (1<<7) ;	GP_IRQ_EXTI_callback[7] () ;}
	if (EXTI->PR & 1<<8) {EXTI->PR = (1<<8) ;	GP_IRQ_EXTI_callback[8] () ;}
	if (EXTI->PR & 1<<9) {EXTI->PR = (1<<9) ;	GP_IRQ_EXTI_callback[9] () ;}
}
void EXTI15_10_IRQHandler(void)
{
	if (EXTI->PR & 1<<10) {EXTI->PR = (1<<10)  ;   GP_IRQ_EXTI_callback[10] () ;}
	if (EXTI->PR & 1<<11) {EXTI->PR = (1<<11)  ;   GP_IRQ_EXTI_callback[11] () ;}
	if (EXTI->PR & 1<<12) {EXTI->PR = (1<<12)  ;   GP_IRQ_EXTI_callback[12] () ;}
	if (EXTI->PR & 1<<13) {EXTI->PR = (1<<13)  ;   GP_IRQ_EXTI_callback[13] () ;}
	if (EXTI->PR & 1<<14) {EXTI->PR = (1<<14)  ;   GP_IRQ_EXTI_callback[14] () ;}
	if (EXTI->PR & 1<<15) {EXTI->PR = (1<<15)  ;   GP_IRQ_EXTI_callback[15] () ;}
}
//---------------------Timer_IRQhandler--------------------------------------------
void TIM1_BRK_IRQHandler (void)
{
	EXTI->PR =(1<<0);
	GP_IRQ_Timer_callback[0] ();
}

void TIM1_UP_IRQHandler (void)
{
	GP_IRQ_Timer_callback[1] ();
}

void TIM1_TRG_COM_IRQHandler (void)
{
	GP_IRQ_Timer_callback[2] ();
}
void TIM1_CC_IRQHandler (void)
{
	GP_IRQ_Timer_callback[3] ();
}
void TIM2_IRQHandler (void)
{
	GP_IRQ_Timer_callback[4] ();
}
void TIM3_IRQHandler (void)
{
	GP_IRQ_Timer_callback[5] ();
}
void TIM4_IRQHandler (void)
{
	GP_IRQ_Timer_callback[6] ();
}
//---------------------I2C_IRQhandler--------------------------------------------

void I2C1_EV_IRQHandler (void)
{
	GP_IRQ_I2C_callback[0] ();
}
void I2C1_ER_IRQHandler (void)
{
	GP_IRQ_I2C_callback[1] ();
}

void I2C2_EV_IRQHandler (void)
{
	GP_IRQ_I2C_callback[3] ();
}
void I2C2_ER_IRQHandler (void)
{
	GP_IRQ_I2C_callback[4] ();
}
//---------------------UART_IRQhandler--------------------------------------------
void USART1_IRQHandler (void)
{
	EXTI->PR =(1<<0);
	GP_IRQ_UART_callback[0] ();
}
void USART2_IRQHandler (void)
{
	EXTI->PR =(1<<1);
	GP_IRQ_UART_callback[1] ();
}
void USART3_IRQHandler (void)
{
	EXTI->PR =(1<<2);

	GP_IRQ_UART_callback[2] ();
}



