#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <util/delay.h>

#include "DIO_interface.h"
#include "CLCD_interface.h"

void main1(void)
{
	u8 Local_u8X,Local_u8Y,Local_u8Counter;

	/*4 pattern arrays for my Name*/

	u8 Local_pu8Arr1[8] =	{
							0b00001111,
							0b00000001,
							0b00000001,
							0b00000001,
							0b00000001,
							0b00011111,
							0b00000000,
							0b00000000
							};

	u8 Local_pu8Arr2[8] =  	{
							0b00000100,
							0b00000001,
							0b00000001,
							0b00000001,
							0b00000001,
							0b00011111,
							0b00000000,
							0b00000000
							};

    u8 Local_pu8Arr3[8] = 	{
    						0b00000000,
							0b00000001,
							0b00000001,
							0b00000001,
							0b00000001,
							0b00011111,
							0b00000110,
							0b00000000
    						};

    u8 Local_pu8Arr4[8] =  	{
    						0b00000100,
							0b00010001,
							0b00010001,
							0b00010001,
							0b00010001,
							0b00010001,
							0b00011111,
							0b00000000
							 };

	/*Initialize LCD Direction */
	DIO_u8SetPortDirection(DIO_u8PORTA,DIO_u8PORT_OUTPUT);
	DIO_u8SetPinDirection(DIO_u8PORTC,DIO_u8PIN0,DIO_u8PIN_OUTPUT);
	DIO_u8SetPinDirection(DIO_u8PORTC,DIO_u8PIN1,DIO_u8PIN_OUTPUT);
	DIO_u8SetPinDirection(DIO_u8PORTC,DIO_u8PIN2,DIO_u8PIN_OUTPUT);

	CLCD_voidInit();



	while(1)
	{
		for(Local_u8Counter = 0 ,Local_u8X = 0 ,Local_u8Y = 15 ;Local_u8Counter < 4 ; Local_u8Counter++)
		{
			/*Display each pattern*/
			CLCD_voidWriteSpcialCharacter(Local_pu8Arr1,1,Local_u8X,Local_u8Y--);
			CLCD_voidWriteSpcialCharacter(Local_pu8Arr2,2,Local_u8X,Local_u8Y--);
			CLCD_voidWriteSpcialCharacter(Local_pu8Arr3,3,Local_u8X,Local_u8Y--);
			CLCD_voidWriteSpcialCharacter(Local_pu8Arr4,4,Local_u8X,Local_u8Y--);

			/*250 Delay */
			_delay_ms(250);

			/*Toggle the row for each name display*/
			TOGGLE_BIT(Local_u8X,0);

			/*Clear the LCD to make name disappear and write it again in different Pose*/
			CLCD_voidSendCommand(1);
		}
	}
}
