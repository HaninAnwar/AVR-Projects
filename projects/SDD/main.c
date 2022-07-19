#include "STD_TYPES.h"

#include "SDD_interface.h"
#include "DIO_interface.h"

void main()
{
	SDD_T* SDD1;
	SDD1->ComType = SDD_u8COM_CATHODE;
	SDD1->Port = DIO_u8PORTA;
	SDD1->EnablePort = DIO_u8PORTC;
	SDD1->EnablePin = DIO_u8PIN0;

	/*SET PORTA AS OUTPUT FOR SSD*/
	DIO_u8SetPortDirection(SDD1->Port , DIO_u8PORT_OUTPUT);

	/*SET ENABLE PIN FOR SSD AS OUTPUT*/
	DIO_u8SetPinDirection(SDD1->EnablePort ,SDD1->EnablePin, DIO_u8PIN_OUTPUT);

	SDD_u8SetNumber(SDD_u8NUM9, SDD1);
	while(1)
	{

	}
}
