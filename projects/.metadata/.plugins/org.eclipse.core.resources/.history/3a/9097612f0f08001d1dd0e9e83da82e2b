/***********************************************************************/
/***********************************************************************/
/************************ AUTHER : Hanin Anwar  ************************/
/************************ LAYER  : HAL          ************************/
/************************ SWC    : DIO          ************************/
/************************ VERSIO : 1.00         ************************/
/***********************************************************************/
/***********************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <util/delay.h>


#include "DIO_interface.h"
#include "LED_interface.h"
#include "LED_config.h"
#include "LED_private.h"

u8 LED_u8TurnOn(LED_T *LED)
{
    u8 Local_Errorstate = 0;

	if(LED->ConnectionType == LED_u8SOURCE)
	{
		DIO_u8SetPinValue(LED->Port , LED->Pin ,DIO_u8PIN_HIGH);
	}
	else if(LED->ConnectionType == LED_u8SINK)
	{
		DIO_u8SetPinValue(LED->Port , LED->Pin ,DIO_u8PIN_LOW);
	}
	else
	{
		Local_Errorstate = 1;
	}
	return Local_Errorstate;
}
u8 LED_u8TurnOff(LED_T *LED)
{
	u8 Local_Errorstate = 0;

	if(LED->ConnectionType == LED_u8SOURCE)
	{
		DIO_u8SetPinDirection(LED->Port , LED->Pin , DIO_u8PIN_OUTPUT);
		DIO_u8SetPinValue(LED->Port , LED->Pin ,DIO_u8PIN_LOW);
	}
	else if(LED->ConnectionType == LED_u8SINK)
	{
		DIO_u8SetPinDirection(LED->Port , LED->Pin , DIO_u8PIN_OUTPUT);
		DIO_u8SetPinValue(LED->Port , LED->Pin ,DIO_u8PIN_HIGH);
	}
	else
	{
		Local_Errorstate = 1;
	}
	return Local_Errorstate;
}

u8 LED_u8Blink(u8 Copy_u8Delay ,LED_T *LED)
{
	LED_u8TurnOn(LED);
	_delay_ms(Copy_u8Delay);
	LED_u8TurnOff(LED);
	_delay_ms(Copy_u8Delay);


}
