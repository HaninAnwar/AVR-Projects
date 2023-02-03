#include "STD_TYPES.h"
#include "util/delay.h"

#include "DIO_interface.h"
#include "PORT_interface.h"
#include "SPI_interface.h"


void main(void)
{
	PORT_voidInit();
	SPI_voidMasterInit();


	while(1)
	{
		SPI_Transceive(1);
		_delay_ms(10);
//		SPI_Transceive(0);
//		_delay_ms(100);
	}
}
