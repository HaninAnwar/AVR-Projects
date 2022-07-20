/***********************************************************************/
/***********************************************************************/
/************************ AUTHER : Hanin Anwar  ************************/
/************************ LAYER  : HAL          ************************/
/************************ SWC    : DIO          ************************/
/************************ VERSION : 1.00         ************************/
/***********************************************************************/
/***********************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <util/delay.h>


#include "DIO_interface.h"
#include "LED_interface.h"
#include "LED_config.h"
#include "LED_private.h"

void LED_voidTurnOn(LED_T *LED)
{

	if(LED->ConnectionType == LED_u8SOURCE)
	{
		DIO_u8SetPinValue(LED->Port , LED->Pin ,DIO_u8PIN_HIGH);
	}
	else if(LED->ConnectionType == LED_u8SINK)
	{
		DIO_u8SetPinValue(LED->Port , LED->Pin ,DIO_u8PIN_LOW);
	}

}
void LED_voidTurnOff(LED_T *LED)
{

	if(LED->ConnectionType == LED_u8SOURCE)
	{
		DIO_u8SetPinValue(LED->Port , LED->Pin ,DIO_u8PIN_LOW);
	}
	else if(LED->ConnectionType == LED_u8SINK)
	{
		DIO_u8SetPinValue(LED->Port , LED->Pin ,DIO_u8PIN_HIGH);
	}

}

void LED_voidBlink(u32 Copy_u8Delay ,LED_T *LED)
{
	LED_voidTurnOn(LED);
	_delay_ms(Copy_u8Delay);
	LED_voidTurnOff(LED);
	_delay_ms(Copy_u8Delay);


}
