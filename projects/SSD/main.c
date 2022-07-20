#include "STD_TYPES.h"

#include "SSD_interface.h"
#include "DIO_interface.h"

void main()
{
	SSD_T* SSD1;
	SSD1->ComType = SSD_u8COM_CATHODE;
	SSD1->Port = DIO_u8PORTA;
	SSD1->EnablePort = DIO_u8PORTC;
	SSD1->EnablePin = DIO_u8PIN0;

	/*SET PORTA AS OUTPUT FOR SSD*/
	DIO_u8SetPortDirection(SSD1->Port , DIO_u8PORT_OUTPUT);

	/*SET ENABLE PIN FOR SSD AS OUTPUT*/
	DIO_u8SetPinDirection(SSD1->EnablePort ,SSD1->EnablePin, DIO_u8PIN_OUTPUT);

	SSD_u8SetNumber(SSD_u8NUM9, SSD1);
	while(1)
	{

	}
}
