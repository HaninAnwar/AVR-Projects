#include "STD_TYPES.h"
#include "util/delay.h"

#include "DIO_interface.h"
#include "PORT_interface.h"
#include "SPI_interface.h"


void main(void)
{
	u8 Local_u8Reading;
	PORT_voidInit();
	SPI_voidSlaveInit();


	while(1)
	{
		Local_u8Reading = SPI_Transceive(10);
		_delay_ms(10);
		if(Local_u8Reading == 1)
		{
			DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN0,DIO_u8PIN_HIGH);
		}

//		else if(Local_u8Reading == 0)
//		{
//			DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN0,DIO_u8PIN_LOW);
//
//		}
	}
}
