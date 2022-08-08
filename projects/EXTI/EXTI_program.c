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

void EXTI_voidInt0Init(void)
{
	/*Set sense control for INT0 to falling edge*/
	CLR_BIT(MCUCR,MCUCR_ISC00);
	SET_BIT(MCUCR,MCUCR_ISC01);

	/*Peripheral interrupt enable for INT0*/
	SET_BIT(GICR,GICR_INT0);
}

void EXTI_voidInt1Init(void)
{

}

void EXTI_voidInt2Init(void)
{

}
