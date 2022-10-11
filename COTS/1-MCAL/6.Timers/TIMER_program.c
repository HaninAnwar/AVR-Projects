/***********************************************************************/
/***********************************************************************/
/************************ AUTHER : Hanin Anwar  ************************/
/************************ LAYER  : MCAL         ************************/
/************************ SWC    : TIMER          ************************/
/************************ VERSION : 1.00         ************************/
/***********************************************************************/
/***********************************************************************/


#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "TIMER_register.h"
#include "TIMER_config.h"
#include "TIMER_private.h"
#include "TIMER_interface.h"

static void (*TIMER0_pvCallBackFunc)(void) = NULL;

void TIMER0_voidInit(void)
{
	/*Choose fast PWM mode*/
	SET_BIT(TCCR0,TCCR0_WGM00);
	SET_BIT(TCCR0,TCCR0_WGM01);


	/*Enable compare match interrupt*/
//	SET_BIT(TIMSK,TIMSK_OCIE0);

	/*Set compare match value*/
//	OCR0 = 125;

	/*Choose prescaler :division by 64*/
	SET_BIT(TCCR0,TCCR0_CS00);
	SET_BIT(TCCR0,TCCR0_CS01);
	CLR_BIT(TCCR0,TCCR0_CS02);


	/*Choose Fast PWM mode : set on top,clear on compare*/
	CLR_BIT(TCCR0,TCCR0_COM00);
	SET_BIT(TCCR0,TCCR0_COM01);

}

void TIMER0_voidSetCompMatchVal(u8 Copy_u8Value)
{
	OCR0 = Copy_u8Value;
}

u8 TIMER0_u8SetCallBack(void (*Copy_pvCallBackFunc)(void))
{
	u8 Local_u8ErrorState = OK;

	if(Copy_pvCallBackFunc != NULL)
	{
		TIMER0_pvCallBackFunc = Copy_pvCallBackFunc;
	}

	else
	{
		Local_u8ErrorState = NULL_POINTER;
	}
	return Local_u8ErrorState;

}


void __vector_10 (void)	__attribute__((signal));
void __vector_10 (void)
{
	if(TIMER0_pvCallBackFunc != NULL)
	{
		TIMER0_pvCallBackFunc();
	}
}

void TIMER1_voidInit(void)
{
	/*Choose Compare o/p mode : Fast PWM*/
	CLR_BIT(TCCR1A,TCCR1A_COMA0);
	SET_BIT(TCCR1A,TCCR1A_COMA1);

	/*Choose waveform generation mode : PWM,Phase correct*/
	CLR_BIT(TCCR1A,TCCR1A_WGM10);
	SET_BIT(TCCR1A,TCCR1A_WGM11);
	CLR_BIT(TCCR1B,TCCR1B_WGM12);
	SET_BIT(TCCR1B,TCCR1B_WGM13);


	/*Prescaler : division by 8*/
	CLR_BIT(TCCR1B,TCCR1B_CS10);
	SET_BIT(TCCR1B,TCCR1B_CS11);
	CLR_BIT(TCCR1B,TCCR1B_CS12);

}

u8 TIMER1_u8SetICR(u16 Copy_u16Top)
{
	ICR1 = Copy_u16Top;
}

u8 TIMER1_u8SetChannelACompMatchVal(u16 Copy_u16Value)
{
	OCR1A = Copy_u16Value;
}
