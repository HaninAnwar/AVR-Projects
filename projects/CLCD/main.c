#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <util/delay.h>

#include "DIO_interface.h"
#include "CLCD_interface.h"

void main(void)
{
	u8 Local_u8Counter, Local_u8Up,Local_u8DN,Local_u8Right,Local_u8Left;

	/*Set Port A for 4 control switches */
	DIO_u8SetPortDirection(DIO_u8PORTD,DIO_u8PORT_INPUT);
	DIO_u8SetPortValue(DIO_u8PORTD,DIO_u8PORT_HIGH);

	/*Initialize LCD Direction */

	DIO_u8SetPortDirection(DIO_u8PORTA,DIO_u8PORT_OUTPUT);
	DIO_u8SetPinDirection(DIO_u8PORTC,DIO_u8PIN0,DIO_u8PIN_OUTPUT);
	DIO_u8SetPinDirection(DIO_u8PORTC,DIO_u8PIN1,DIO_u8PIN_OUTPUT);
	DIO_u8SetPinDirection(DIO_u8PORTC,DIO_u8PIN2,DIO_u8PIN_OUTPUT);

	CLCD_voidInit();
	CLCD_voidSendString("Hanin Mohammed Anwar Mohammed Hassan");

	while(1)
	{



	}

}
