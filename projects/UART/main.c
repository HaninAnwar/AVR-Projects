#include "STD_TYPES.h"

#include "DIO_interface.h"
#include "PORT_interface.h"
#include "USART_interface.h"


void main(void)
{

	u8 Local_u8Data = 0;

	PORT_voidInit();
	USRAT_voidInit();

	while(1)
	{
		Local_u8Data = USART_u8Receive();

		if(Local_u8Data == '1')
		{
			DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN0,DIO_u8PIN_HIGH);
			USART_voidSendString("Start");

		}

		else if(Local_u8Data == '2')
		{
			DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN0,DIO_u8PIN_LOW);
			USART_voidSendString("Stop");

		}


	}
}
