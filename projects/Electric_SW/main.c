#include "STD_TYPES.h"
#include "DIO_interface.h"
#include "PORT_interface.h"
#include <util/delay.h>

void main (void)
{
	PORT_voidInit();
	u16 Local_u16Counter,Local_u16Revolution;

	Local_u16Revolution = 90 / (0.175*4);

	for(Local_u16Counter = 0; Local_u16Counter < Local_u16Revolution ;Local_u16Counter++)
	{
		DIO_u8SetPinValue(DIO_u8PORTB,DIO_u8PIN2,DIO_u8PIN_LOW);
		DIO_u8SetPinValue(DIO_u8PORTB,DIO_u8PIN3,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(DIO_u8PORTB,DIO_u8PIN4,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(DIO_u8PORTB,DIO_u8PIN5,DIO_u8PIN_HIGH);
		_delay_ms(2);
		DIO_u8SetPinValue(DIO_u8PORTB,DIO_u8PIN3,DIO_u8PIN_LOW);
		DIO_u8SetPinValue(DIO_u8PORTB,DIO_u8PIN2,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(DIO_u8PORTB,DIO_u8PIN4,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(DIO_u8PORTB,DIO_u8PIN5,DIO_u8PIN_HIGH);
		_delay_ms(2);
		DIO_u8SetPinValue(DIO_u8PORTB,DIO_u8PIN4,DIO_u8PIN_LOW);
		DIO_u8SetPinValue(DIO_u8PORTB,DIO_u8PIN2,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(DIO_u8PORTB,DIO_u8PIN3,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(DIO_u8PORTB,DIO_u8PIN5,DIO_u8PIN_HIGH);
		_delay_ms(2);
		DIO_u8SetPinValue(DIO_u8PORTB,DIO_u8PIN5,DIO_u8PIN_LOW);
		DIO_u8SetPinValue(DIO_u8PORTB,DIO_u8PIN2,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(DIO_u8PORTB,DIO_u8PIN3,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(DIO_u8PORTB,DIO_u8PIN4,DIO_u8PIN_HIGH);
		_delay_ms(2);
	}

	while(1)
	{




		//		DIO_u8SetPinValue(DIO_u8PORTB,DIO_u8PIN6,DIO_u8PIN_LOW);
		//		DIO_u8SetPinValue(DIO_u8PORTB,DIO_u8PIN7,DIO_u8PIN_HIGH);
		//		_delay_ms(500);
		//
		//		DIO_u8SetPinValue(DIO_u8PORTB,DIO_u8PIN7,DIO_u8PIN_LOW);
		//		DIO_u8SetPinValue(DIO_u8PORTB,DIO_u8PIN6,DIO_u8PIN_HIGH);
		//		_delay_ms(500);

	}
}
