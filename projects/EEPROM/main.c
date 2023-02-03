#include "STD_TYPES.h"
#include <util/delay.h>

#include "DIO_interface.h"
#include "PORT_interface.h"
#include "TWI_interface.h"

#include "EEPROM_interface.h"


void main(void)
{
	u8 Local_u8Reading;
	PORT_voidInit();

	TWI_voidMasterInit(0);

	//	TWI_voidSlaveInit(0b1010000);
	EEPROM_WriteDataByte(0b11110000,0);

	_delay_ms(10);
	Local_u8Reading = EEPROM_ReadDataByte(0);

	DIO_u8SetPortValue(DIO_u8PORTA,Local_u8Reading);
	while(1)
	{


	}
}
