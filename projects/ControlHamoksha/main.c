#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <util/delay.h>

#include "DIO_interface.h"
#include "SW_interface.h"
#include "CLCD_interface.h"

void main(void)
{
	u8 Local_u8CountUpDn,Local_u8CountRightLeft;
	u8 Local_u8Up,Local_u8Right,Local_u8Left;
	SW_T *SW_UP_DN, *SW_DN, *SW_RT, *SW_LF;

	u8 Local_pu8uSmallHamoksha[8] =	{
			0b00001110,
			0b00010001,
			0b00001110,
			0b00000100,
			0b00011111,
			0b00000100,
			0b00001010,
			0b00010001,
	};

	/*Set Up Switches*/

	SW_UP_DN->Pin = DIO_u8PIN0;
	SW_UP_DN->Port = DIO_u8PORTB;
	SW_UP_DN->PullType = SW_u8PULL_UP;
	SW_UP_DN->SelfLockType = SW_u8NOT_SELF_LOCK;


	SW_RT->Pin = DIO_u8PIN2;
	SW_RT->Port = DIO_u8PORTB;
	SW_RT->PullType = SW_u8PULL_UP;
	SW_RT->SelfLockType = SW_u8NOT_SELF_LOCK;

	SW_LF->Pin = DIO_u8PIN3;
	SW_LF->Port = DIO_u8PORTB;
	SW_LF->PullType = SW_u8PULL_UP;
	SW_LF->SelfLockType = SW_u8NOT_SELF_LOCK;

	DIO_u8SetPortDirection(SW_UP_DN->Port,DIO_u8PORT_INPUT);
	DIO_u8SetPortValue(SW_UP_DN->Port,DIO_u8PORT_HIGH);


	/*Initialize LCD Direction */

	DIO_u8SetPortDirection(DIO_u8PORTA,DIO_u8PORT_OUTPUT);
	DIO_u8SetPinDirection(DIO_u8PORTC,DIO_u8PIN0,DIO_u8PIN_OUTPUT);
	DIO_u8SetPinDirection(DIO_u8PORTC,DIO_u8PIN1,DIO_u8PIN_OUTPUT);
	DIO_u8SetPinDirection(DIO_u8PORTC,DIO_u8PIN2,DIO_u8PIN_OUTPUT);

	CLCD_voidInit();

	/*Start Pose*/
	Local_u8CountUpDn = 0;
	Local_u8CountRightLeft = 6;

	while(1)
	{
		CLCD_voidSendCommand(1);
		CLCD_voidWriteSpcialCharacter(Local_pu8uSmallHamoksha,0,Local_u8CountUpDn,Local_u8CountRightLeft);

		SW_u8GetState(SW_UP_DN,&Local_u8Up);
		SW_u8GetState(SW_RT,&Local_u8Right);
		SW_u8GetState(SW_LF,&Local_u8Left);

		_delay_ms(100);
		if (Local_u8Up == SW_u8PRESSED)
		{
			TOGGLE_BIT(Local_u8CountUpDn,0);
			CLCD_voidSendCommand(1);
			CLCD_voidWriteSpcialCharacter(Local_pu8uSmallHamoksha,0,Local_u8CountUpDn,Local_u8CountRightLeft);

		}

		if (Local_u8Right == SW_u8PRESSED)
		{
			CLCD_voidSendCommand(1);
			CLCD_voidWriteSpcialCharacter(Local_pu8uSmallHamoksha,0,Local_u8CountUpDn,++Local_u8CountRightLeft);
		}
		if (Local_u8Left == SW_u8PRESSED)
		{
			CLCD_voidSendCommand(1);
			CLCD_voidWriteSpcialCharacter(Local_pu8uSmallHamoksha,0,Local_u8CountUpDn,--Local_u8CountRightLeft);

		}
	}

}
