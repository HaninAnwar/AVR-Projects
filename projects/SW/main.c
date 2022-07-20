#include "STD_TYPES.h"
#include "DIO_interface.h"
#include "LED_interface.h"
#include "SW_interface.h"
#include <util/delay.h>


void main()
{
	u8 Local_u8Pressed ;
	SW_T *SW1;
	LED_T *LED1;

	SW1->Port = DIO_u8PORTA;
	SW1->Pin = DIO_u8PIN7;
	SW1->PullType = SW_u8PULL_UP;
	SW1->SelfLockType = SW_u8NOT_SELF_LOCK;

	LED1->Port = DIO_u8PORTA;
	LED1->Pin = DIO_u8PIN0;
	LED1->ConnectionType = LED_u8SOURCE;

	DIO_u8SetPinDirection(SW1->Port ,SW1->Pin , DIO_u8PIN_INPUT);
	DIO_u8SetPinValue(SW1->Port ,SW1->Pin , DIO_u8PIN_HIGH);

	DIO_u8SetPinDirection(LED1->Port , LED1->Pin , DIO_u8PIN_OUTPUT);


	while (1)
	{

		SW_u8GetState(SW1,&Local_u8Pressed);
		_delay_ms(150);

		if(Local_u8Pressed == SW_u8PRESSED)
		{
			LED_voidTurnOn(LED1);
		}
		else if(Local_u8Pressed == SW_u8NOT_PRESSED)

		{
			LED_voidTurnOff(LED1);
		}

	}
}
