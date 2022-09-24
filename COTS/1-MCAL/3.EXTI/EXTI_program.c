/***********************************************************************/
/***********************************************************************/
/************************ AUTHER : Hanin Anwar  ************************/
/************************ LAYER  : MCAL         ************************/
/************************ SWC    : EXTI          ************************/
/************************ VERSION : 1.00         ************************/
/***********************************************************************/
/***********************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "EXTI_interface.h"
#include "EXTI_config.h"
#include "EXTI_private.h"
#include "EXTI_register.h"

/*Global pointers to functions to hold INT ISR addresses*/
void (*EXTI_pvInt0Func)(void) = NULL;
void (*EXTI_pvInt1Func)(void) = NULL;
void (*EXTI_pvInt2Func)(void) = NULL;

void EXTI_voidInt0Init(void)
{
	/*1. Check  sense control*/
#if INT0_SENSE == LOW_LEVEL
	CLR_BIT(MCUCR,MCUCR_ISC00);
	CLR_BIT(MCUCR,MCUCR_ISC01);

#elif INT0_SENSE == ON_CHANGE
	SET_BIT(MCUCR,MCUCR_ISC00);
	CLR_BIT(MCUCR,MCUCR_ISC01);

#elif INT0_SENSE == FALLING_EDGE
	CLR_BIT(MCUCR,MCUCR_ISC00);
	SET_BIT(MCUCR,MCUCR_ISC01);

#elif INT0_SENSE == RISING_EDGE
	SET_BIT(MCUCR,MCUCR_ISC00);
	SET_BIT(MCUCR,MCUCR_ISC01);

#else
#error "Wrong INT0_SENSE configuration option"

#endif

	/*2. Check peripheral interrupt enable initial state*/
#if INT0_INITIAL_STATE == ENABLED
	SET_BIT(GICR,GICR_INT0);

#elif INT0_INITIAL_STATE == DISABLED
	CLR_BIT(GICR,GICR_INT0);

#else
#error "Wrong INT0_INITIAL_STATE configuration option"

#endif

}

void EXTI_voidInt1Init(void)
{
	/*1. Check  sense control*/
#if INT1_SENSE == LOW_LEVEL
	CLR_BIT(MCUCR,MCUCR_ISC10);
	CLR_BIT(MCUCR,MCUCR_ISC11);

#elif INT1_SENSE == ON_CHANGE
	SET_BIT(MCUCR,MCUCR_ISC10);
	CLR_BIT(MCUCR,MCUCR_ISC11);

#elif INT1_SENSE == FALLING_EDGE
	CLR_BIT(MCUCR,MCUCR_ISC10);
	SET_BIT(MCUCR,MCUCR_ISC11);

#elif INT1_SENSE == RISING_EDGE
	SET_BIT(MCUCR,MCUCR_ISC10);
	SET_BIT(MCUCR,MCUCR_ISC11);

#else
#error "Wrong INT1_SENSE configuration option"

#endif

	/*2. Check peripheral interrupt enable initial state*/
#if INT1_INITIAL_STATE == ENABLED
	SET_BIT(GICR,GICR_INT1);

#elif INT1_INITIAL_STATE == DISABLED
	CLR_BIT(GICR,GICR_INT1);

#else
#error "Wrong INT1_INITIAL_STATE configuration option"

#endif

}

void EXTI_voidInt2Init(void)
{
#if INT2_SENSE == FALLING_EDGE
	CLR_BIT(MCUCSR,MCUCSR_ISC2);

#elif INT2_SENSE == RISING_EDGE
	SET_BIT(MCUCSR,MCUCSR_ISC2);

#else
#error "Wrong INT2_SENSE configuration option"

#endif

#if INT2_INITIAL_STATE == ENABLED
	SET_BIT(GICR,GICR_INT2);

#elif INT2_INITIAL_STATE == DISABLED
	cLR_BIT(GICR,GICR_INT2);

#else
#error  "Wrong INT2_INITIAL_STATE configuration option"

#endif
}

u8 EXTI_u8IntSetSenseControl(u8 Copy_IntNum,u8 Copy_u8Sense)
{
	u8 Local_u8ErrorState = OK;

	if(Copy_IntNum == EXTI_INT0)
	{
		switch(Copy_u8Sense)
		{
		case LOW_LEVEL: CLR_BIT(MCUCR,MCUCR_ISC00);CLR_BIT(MCUCR,MCUCR_ISC01);break;
		case ON_CHANGE:SET_BIT(MCUCR,MCUCR_ISC00);CLR_BIT(MCUCR,MCUCR_ISC01);break;
		case FALLING_EDGE:CLR_BIT(MCUCR,MCUCR_ISC00);SET_BIT(MCUCR,MCUCR_ISC01);break;
		case RISING_EDGE:CLR_BIT(MCUCR,MCUCR_ISC00);SET_BIT(MCUCR,MCUCR_ISC01);break;
		default :Local_u8ErrorState = NOK;
		}
	}

	else if (Copy_IntNum == EXTI_INT1)
	{
		switch(Copy_u8Sense)
		{
		case LOW_LEVEL: CLR_BIT(MCUCR,MCUCR_ISC10);CLR_BIT(MCUCR,MCUCR_ISC11);break;
		case ON_CHANGE:SET_BIT(MCUCR,MCUCR_ISC10);CLR_BIT(MCUCR,MCUCR_ISC11);break;
		case FALLING_EDGE:CLR_BIT(MCUCR,MCUCR_ISC10);SET_BIT(MCUCR,MCUCR_ISC11);break;
		case RISING_EDGE:CLR_BIT(MCUCR,MCUCR_ISC10);SET_BIT(MCUCR,MCUCR_ISC11);break;
		default :Local_u8ErrorState = NOK;
		}
	}

	else if (Copy_IntNum == EXTI_INT2)
	{
		switch(Copy_u8Sense)
		{
		case FALLING_EDGE:CLR_BIT(MCUCSR,MCUCSR_ISC2);break;
		case RISING_EDGE:SET_BIT(MCUCSR,MCUCSR_ISC2);break;
		default :Local_u8ErrorState = NOK;
		}
	}

	else
	{
		Local_u8ErrorState = NOK;
	}


	return Local_u8ErrorState;
}
u8 EXTI_u8IntEnableControl(u8 Copy_IntNum , u8 Copy_u8Enable)
{
	u8 Local_u8ErrorState = OK;

	switch(Copy_IntNum)
	{
	case EXTI_INT0 :
		if(Copy_u8Enable == ENABLED)
			SET_BIT(GICR,GICR_INT0);
		else if (Copy_u8Enable == DISABLED)
			CLR_BIT(GICR,GICR_INT0);
		else
			Local_u8ErrorState = NOK;
		break;

	case EXTI_INT1 :
		if(Copy_u8Enable == ENABLED)
			SET_BIT(GICR,GICR_INT1);
		else if (Copy_u8Enable == DISABLED)
			CLR_BIT(GICR,GICR_INT1);
		else
			Local_u8ErrorState = NOK;
		break;

	case EXTI_INT2 :
		if(Copy_u8Enable == ENABLED)
			SET_BIT(GICR,GICR_INT2);
		else if (Copy_u8Enable == DISABLED)
			CLR_BIT(GICR,GICR_INT2);
		else
			Local_u8ErrorState = NOK;
		break;

	default : Local_u8ErrorState = NOK;
	}
	return Local_u8ErrorState;
}

u8 EXTI_u8Int0SetCallback(void (* Copy_pvInt0Func) (void))
{
	u8 Local_u8ErrorState = OK;

	if (Copy_pvInt0Func != NULL)
	{
		EXTI_pvInt0Func = Copy_pvInt0Func;
	}
	else
	{
		Local_u8ErrorState = NULL_POINTER;
	}

	return Local_u8ErrorState;
}

u8 EXTI_u8Int1SetCallback(void (* Copy_pvInt1Func) (void))
{
	u8 Local_u8ErrorState = OK;

	if(Copy_pvInt1Func != NULL)
	{
		EXTI_pvInt1Func = Copy_pvInt1Func;
	}
	else
	{
		Local_u8ErrorState = NULL_POINTER;
	}

	return Local_u8ErrorState;
}

u8 EXTI_u8Int2SetCallback(void (* Copy_pvInt2Func) (void))
{
	u8 Local_u8ErrorState = OK;

	if(Copy_pvInt2Func != NULL)
	{
		EXTI_pvInt2Func = Copy_pvInt2Func;
	}

	else
	{
		Local_u8ErrorState = NULL_POINTER;
	}

	return Local_u8ErrorState;
}

/*ISR of INT0*/
void __vector_1 (void) __attribute__((signal));
void __vector_1 (void)
{
	if (EXTI_pvInt0Func != NULL)
	{
		EXTI_pvInt0Func();
	}

}

/*ISR of INT1*/
void __vector_2 (void) __attribute__((signal));
void __vector_2 (void)
{
	if(EXTI_pvInt1Func != NULL)
	{
		EXTI_pvInt1Func();
	}
}

/*ISR of INT2*/
void __vector_3 (void) __attribute__((signal));
void __vector_3 (void)
{
	if(EXTI_pvInt2Func != NULL)
	{
		EXTI_pvInt2Func();
	}
}
