#include "STD_TYPES.h"

#include "PORT_interface.h"
#include "CLCD_interface.h"
#include "KEYPAD_interface.h"

void main(void)
{
	u8 Local_u8KeyValue;

	PORT_voidInit();
	CLCD_voidInit();
	while(1)
	{
		do
		{
			Local_u8KeyValue = KPD_GetPressedKey();
		}
		while(Local_u8KeyValue == 0xff);
		CLCD_voidSendCommand(1);
		CLCD_voidWriteNumber(Local_u8KeyValue);

	}
}
