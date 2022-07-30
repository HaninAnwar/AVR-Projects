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

#include "LED_interface.h"

#include "DIO_interface.h"
#include "SW_interface.h"
#include "SW_config.h"
#include "SW_private.h"

u8 SW_u8GetState(SW_T *SW,u8 *Copy_pu8State)
{
	u8 Local_u8ErrorState = 0;
	u8 Local_u8get;



	DIO_u8GetPinValue(SW->Port,SW->Pin,&Local_u8get);

	if(SW->SelfLockType == SW_u8SELF_LOCK)
	{
		if(SW->PullType == SW_u8PULL_UP)
		{
			if(Local_u8get == DIO_u8PIN_LOW)

				*Copy_pu8State = SW_u8PRESSED;

			else

				*Copy_pu8State = SW_u8NOT_PRESSED;


		}

		else if(SW->PullType == SW_u8PULL_DN)
		{

			if(Local_u8get == DIO_u8PIN_HIGH)

				*Copy_pu8State = SW_u8PRESSED;

			else
				*Copy_pu8State = SW_u8NOT_PRESSED;
		}

		else
			Local_u8ErrorState = 1;
	}

	else if(SW->SelfLockType == SW_u8NOT_SELF_LOCK)
	{
		if(SW->PullType == SW_u8PULL_UP)
		{

			if(Local_u8get == DIO_u8PIN_LOW)
			{
				_delay_ms(50);
				*Copy_pu8State = SW_u8PRESSED;
			}
			else
			{
				_delay_ms(50);
				*Copy_pu8State = SW_u8NOT_PRESSED;
			}

		}

		else if(SW->PullType == SW_u8PULL_DN)
		{

			if(Local_u8get == DIO_u8PIN_HIGH)
			{
				_delay_ms(50);
				*Copy_pu8State = SW_u8PRESSED;
			}
			else
			{
				_delay_ms(50);
				*Copy_pu8State = SW_u8NOT_PRESSED;
			}

		}

		else
			Local_u8ErrorState = 1;

	}

	else
		Local_u8ErrorState = 1;


	return Local_u8ErrorState;
}
