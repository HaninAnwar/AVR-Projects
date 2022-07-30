#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <util/delay.h>

#include "DIO_interface.h"
#include "PORT_interface.h"
#include "CLCD_interface.h"

void main(void)
{
	u8 Local_u8Counter, Local_u8Up,Local_u8DN,Local_u8Right,Local_u8Left;

	PORT_voidInit();

	/*Initialize LCD Direction */
	CLCD_voidInit();

	CLCD_voidSendString("Hanin");

	while(1)
	{

	}

}
