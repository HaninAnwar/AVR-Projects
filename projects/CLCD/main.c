#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <util/delay.h>

#include "DIO_interface.h"
#include  "SW_interface.h"
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



	Local_u8DN = 0;
	Local_u8Up = 0;
	Local_u8Right = 6;
	Local_u8Left = 6;
	u8 up,dn,lf,rt;
	while(1)
	{



/**************************	Control Hamoksha *************************/
		u8 Local_pu8uSmall[8] =	{
								0b00001110,
								0b00010001,
								0b00001110,
								0b00000100,
								0b00011111,
								0b00000100,
								0b00001010,
								0b00010001,
								};

		Local_u8Counter = 0;
		CLCD_voidSendCommand(1);
		CLCD_voidWriteSpcialCharacter(Local_pu8uSmall,1,0,Local_u8Right);

		DIO_u8GetPinValue(DIO_u8PORTD,DIO_u8PIN0,&up);
		DIO_u8GetPinValue(DIO_u8PORTD,DIO_u8PIN1,&rt);
		DIO_u8GetPinValue(DIO_u8PORTD,DIO_u8PIN2,&lf);
		DIO_u8GetPinValue(DIO_u8PORTD,DIO_u8PIN3,&dn);
		//UP
		if(up == 0)
		{
			_delay_ms(50);
//			TOGGLE_BIT(Local_u8Up,0);
			CLCD_voidSendCommand(1);
			CLCD_voidWriteSpcialCharacter(Local_pu8uSmall,1,0,Local_u8Right);


		}
		//Right
		if(rt == 0)
		{
			_delay_ms(50);
//			TOGGLE_BIT(Local_u8Up,0);
			Local_u8Right++;
			CLCD_voidSendCommand(1);
			CLCD_voidWriteSpcialCharacter(Local_pu8uSmall,1,0,Local_u8Right);
		}
		//Left
		if(lf == 0)
		{
			_delay_ms(50);
//			TOGGLE_BIT(Local_u8Up,0);
			CLCD_voidSendCommand(1);
			_delay_ms(500);

			Local_u8Right--;
			CLCD_voidWriteSpcialCharacter(Local_pu8uSmall,1,0,Local_u8Right);
		}

		//Down
		if(dn == 0)
		{
			_delay_ms(50);
//			TOGGLE_BIT(Local_u8Up,0);
			CLCD_voidSendCommand(1);
			CLCD_voidWriteSpcialCharacter(Local_pu8uSmall,1,1,Local_u8Right);

		}


		_delay_ms(500);



	}

}
