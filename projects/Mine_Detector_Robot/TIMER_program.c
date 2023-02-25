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

static void	(* TIMER_pvCallBackFunc[8])(void) = {NULL};


u8 TIMER0_u8Init(u8 Copy_u8WaveMode , u8 Copy_u8CompereMode ,u8 Copy_u8Prescaler)
{
	u8 Local_u8ErrorState = OK;

	/*Set waveform generation mode*/
	switch(Copy_u8WaveMode)
	{
	case NORMAL :
		CLR_BIT(TCCR0,TCCR0_WGM00);
		CLR_BIT(TCCR0,TCCR0_WGM01);

		/*Enable overflow interrupt*/
		SET_BIT(TIMSK,TIMSK_TOIE0);

		break;

	case PHASE_CORRECT :
		SET_BIT(TCCR0,TCCR0_WGM00);
		CLR_BIT(TCCR0,TCCR0_WGM01);
		break;

	case CTC :
		CLR_BIT(TCCR0,TCCR0_WGM00);
		SET_BIT(TCCR0,TCCR0_WGM01);

		/*Enable output Compare interrupt*/
		SET_BIT(TIMSK,TIMSK_OCIE0);
		break;

	case FAST_PWM :
		SET_BIT(TCCR0,TCCR0_WGM00);
		SET_BIT(TCCR0,TCCR0_WGM01);
		break;

	default : Local_u8ErrorState = NOK;
	}

	/*Set Output compare mode*/
	TCCR0 &= TIMER0_COM_MASK;
	TCCR0 |= Copy_u8CompereMode << 4;

	/*Set prescaler */
	TCCR0 &= TIMER_PRESCALER_MASK;
	TCCR0 |= Copy_u8Prescaler;

	return Local_u8ErrorState;
}

u8 TIMER1_u8Init(u8 Copy_u8Channel , u8 Copy_u8WaveMode , u8 Copy_u8CompereMode ,u8 Copy_u8Prescaler)
{
	u8 Local_u8Errorstate = OK;

	/*check timer channel*/

	if(Copy_u8Channel == TIMER1_CHANNEL_A)
	{
		/*Set output compare mode*/
		TCCR1A &= TIMER1_COM_MASK_A;
		TCCR1A |= Copy_u8CompereMode << 6;

		/*Set Wave generation mode*/
		switch(Copy_u8WaveMode)
		{
		case NORMAL :
			CLR_BIT(TCCR1A,TCCR1A_WGM10);
			CLR_BIT(TCCR1A,TCCR1A_WGM11);

			/*Enable overflow interrupt*/
			SET_BIT(TIMSK,TIMSK_TOIE1);

			break;

		case CTC :
			CLR_BIT(TCCR1A,TCCR1A_WGM10);
			CLR_BIT(TCCR1A,TCCR1A_WGM11);

			/*Enable output Compare interrupt*/
			SET_BIT(TIMSK,TIMSK_OCIE1A);

			break;

		case PHASE_CORRECT :
			CLR_BIT(TCCR1A,TCCR1A_WGM10);
			SET_BIT(TCCR1A,TCCR1A_WGM11);
			break;

		case FAST_PWM :
			CLR_BIT(TCCR1A,TCCR1A_WGM10);
			SET_BIT(TCCR1A,TCCR1A_WGM11);
			break;

		default : Local_u8Errorstate = NOK;

		}
	}

	else if (Copy_u8Channel == TIMER1_CHANNEL_B)
	{
		/*Set output compare mode*/
		TCCR1B &= TIMER1_COM_MASK_B;
		TCCR1B |= Copy_u8CompereMode << 4;

		/*Set Wave generation mode*/
		switch(Copy_u8WaveMode)
		{
		case NORMAL :
			CLR_BIT(TCCR1B,TCCR1B_WGM12);
			CLR_BIT(TCCR1B,TCCR1B_WGM13);

			/*Enable overflow interrupt*/
			SET_BIT(TIMSK,TIMSK_TOIE1);

			break;

		case CTC :
			SET_BIT(TCCR1B,TCCR1B_WGM12);
			CLR_BIT(TCCR1B,TCCR1B_WGM13);

			/*Enable output Compare interrupt*/
			SET_BIT(TIMSK,TIMSK_OCIE1B);
			break;

		case PHASE_CORRECT :
			CLR_BIT(TCCR1B,TCCR1B_WGM12);
			SET_BIT(TCCR1B,TCCR1B_WGM13);
			break;

		case FAST_PWM :
			SET_BIT(TCCR1B,TCCR1B_WGM12);
			SET_BIT(TCCR1B,TCCR1B_WGM13);
			break;

		default : Local_u8Errorstate = NOK;

		}
	}

	else
	{
		Local_u8Errorstate = NOK;
	}

	/*Set prescalre*/
	TCCR1B &= TIMER_PRESCALER_MASK;
	TCCR1B |= Copy_u8Prescaler;

	return Local_u8Errorstate;
}


u8 TIMER2_u8Init(u8 Copy_u8WaveMode , u8 Copy_u8CompereMode ,u8 Copy_u8Prescaler)
{
	u8 Local_u8ErrorState = OK;

	/*Set waveform generation mode*/
	switch(Copy_u8WaveMode)
	{
	case NORMAL :
		CLR_BIT(TCCR2,TCCR2_WGM20);
		CLR_BIT(TCCR2,TCCR2_WGM21);

		/*Enable overflow interrupt*/
		SET_BIT(TIMSK,TIMSK_TOIE2);
		break;

	case PHASE_CORRECT :
		SET_BIT(TCCR2,TCCR2_WGM20);
		CLR_BIT(TCCR2,TCCR2_WGM21);
		break;

	case CTC :
		CLR_BIT(TCCR2,TCCR2_WGM20);
		SET_BIT(TCCR2,TCCR2_WGM21);

		/*Enable output Compare interrupt*/
		SET_BIT(TIMSK,TIMSK_OCIE2);
		break;

	case FAST_PWM :
		SET_BIT(TCCR2,TCCR2_WGM20);
		SET_BIT(TCCR2,TCCR2_WGM21);

		break;

	default : Local_u8ErrorState = NOK;
	}

	/*Set Output compare mode*/
	TCCR2 &= TIMER2_COM_MASK;
	TCCR2 |= Copy_u8CompereMode << 4;

	/*Set prescaler */
	TCCR2 &= TIMER_PRESCALER_MASK;
	TCCR2 |= Copy_u8Prescaler;

	return Local_u8ErrorState;
}

void TIMER0_voidSetCompMatchVal(u8 Copy_u8Value)
{
	OCR0 = Copy_u8Value;
}

void TIMER1_voidSetICR(u16 Copy_u16Top)
{
	ICR1 = Copy_u16Top;
}

void TIMER1_voidSetChannelACompMatchVal(u16 Copy_u16Value)
{
	OCR1A = Copy_u16Value;
}

void TIMER1_voidSetTimerValue(u16 Copy_u16Value)
{
	TCNT1 = Copy_u16Value;
}

u16 TIMER1_u16ReadTimerValue(void)
{
	return TCNT1;
}

void TIMER2_voidSetCompMatchVal(u8 Copy_u8Value)
{
	OCR2 = Copy_u8Value;
}
void ICU_voidInit(void)
{

	/*Select triggered edge : rising edge*/
	SET_BIT(TCCR1B,TCCR1B_ICES);

	/*Enable ICU interrupt*/
	SET_BIT(TIMSK,TIMSK_TICIE1);
}

u8 ICU_u8SetTiggerEdge(u8 Copy_u8Edge)
{
	u8 Local_u8ErrorState = OK;

	if(Copy_u8Edge == ICU_RISING_EDGE)
	{
		SET_BIT(TCCR1B,TCCR1B_ICES);
	}
	else if (Copy_u8Edge == ICU_FALLING_EDGE)
	{
		CLR_BIT(TCCR1B,TCCR1B_ICES);
	}
	else
	{
		Local_u8ErrorState = NOK;
	}
	return Local_u8ErrorState;
}

u8 ICU_u8EnableControl(u8 Copy_u8Enable)
{
	u8 Local_u8ErrorState = OK;

	if(Copy_u8Enable == ICU_INT_ENABLE)
	{
		SET_BIT(TIMSK,TIMSK_TICIE1);
	}
	else if(Copy_u8Enable == ICU_INT_DISABLE)
	{
		CLR_BIT(TIMSK,TIMSK_TICIE1);
	}
	else
	{
		Local_u8ErrorState = NOK;
	}
	return Local_u8ErrorState;
}

u16 ICU_u16ReadingICU(void)
{
	return ICR1;
}

u8 TIMER_u8SetCallBack(u8 Copy_u8INT_ID,void (*Copy_pvCallBackFunc)(void))
{
	u8 Local_u8ErrorState = OK;

	if(Copy_pvCallBackFunc != NULL)
	{
		TIMER_pvCallBackFunc[Copy_u8INT_ID] = Copy_pvCallBackFunc;
	}
	else
	{
		Local_u8ErrorState = NULL_POINTER;
	}

	return Local_u8ErrorState;
}


void PWM_voidSetPWM(u8 Copy_u8TimerNum,u16 Copy_u16Duration)
{
	switch(Copy_u8TimerNum)
	{
	case TIMER_0 	: OCR0  = Copy_u16Duration;break;
	case TIMER_1A 	: OCR1A = Copy_u16Duration;break;
	case TIMER_1B 	: OCR1B = Copy_u16Duration;break;
	case TIMER_2 	: OCR2  = Copy_u16Duration;break;

	}
}
void __vector_4 (void) __attribute__ ((signal));
void __vector_4 (void)
{
	if(TIMER_pvCallBackFunc[TIMER2_OUTPUT_COM_INT] != NULL)
	{
		TIMER_pvCallBackFunc[TIMER2_OUTPUT_COM_INT]();
	}
}

void __vector_5 (void) __attribute__ ((signal));
void __vector_5 (void)
{
	if(TIMER_pvCallBackFunc[TIMER2_OVERFLOW_INT] != NULL)
	{
		TIMER_pvCallBackFunc[TIMER2_OVERFLOW_INT]();
	}
}

void __vector_6 (void) __attribute__ ((signal));
void __vector_6 (void)
{
	if(TIMER_pvCallBackFunc[TIMER1_ICU_INT] != NULL)
	{
		TIMER_pvCallBackFunc[TIMER1_ICU_INT]();
	}
}

void __vector_7 (void) __attribute__ ((signal));
void __vector_7 (void)
{
	if(TIMER_pvCallBackFunc[TIMER1_OUTPUT_COM_A_INT] != NULL)
	{
		TIMER_pvCallBackFunc[TIMER1_OUTPUT_COM_A_INT]();
	}
}

void __vector_8 (void) __attribute__ ((signal));
void __vector_8 (void)
{
	if(TIMER_pvCallBackFunc[TIMER1_OUTPUT_COM_B_INT] != NULL)
	{
		TIMER_pvCallBackFunc[TIMER1_OUTPUT_COM_B_INT]();
	}
}

void __vector_9 (void) __attribute__ ((signal));
void __vector_9 (void)
{
	if(TIMER_pvCallBackFunc[TIMER1_OVERFLOW_INT] != NULL)
	{
		TIMER_pvCallBackFunc[TIMER1_OVERFLOW_INT]();
	}
}

void __vector_10 (void)	__attribute__((signal));
void __vector_10 (void)
{
	if(TIMER_pvCallBackFunc[TIMER0_OUTPUT_COM_INT] != NULL)
	{
		TIMER_pvCallBackFunc[TIMER0_OUTPUT_COM_INT]();
	}
}

void __vector_11 (void)	__attribute__((signal));
void __vector_11 (void)
{
	if(TIMER_pvCallBackFunc[TIMER0_OVERFLOW_INT] != NULL)
	{
		TIMER_pvCallBackFunc[TIMER0_OVERFLOW_INT]();
	}
}

