#include "STD_TYPES.h"
#include "util/delay.h"

#include "DIO_interface.h"
#include "PORT_interface.h"
#include "CLCD_interface.h"
#include "KEYPAD_interface.h"


void main(void)
{
	u8 Local_u8CurrentSlot,Local_u8CurrentDigit,Local_u8CurrentY;
	u8 Local_u8Counter,Local_u8HourCount,Local_u8MinCount,Local_u8SecCount;
	u8 Local_pu8HoursArrArr[2] = {0} ,Local_pu8MinsArr[2] = {0} ,Local_pu8SecsArr[2] = {0};

	u8 Local_pu8ArrowPoseArr[6] = {2,3,7,8,12,13};

	u8 Local_u8StartFlag;

	u8 Local_u8PressedKey,Local_u8Hours,Local_u8Mins,Local_u8Secs;

	u8 Local_pu8Arrow[8] = {
			0b00000100,
			0b00001110,
			0b00011111,
			0b00000100,
			0b00000100,
			0b00000100,
			0b00000100,
			0b00000100,

	};

	PORT_voidInit();
	CLCD_voidInit();

	/*CurrentSlot :
	 * Hours  : Minutes : Seconds
	 * 	3			2		1	*/
	Local_u8CurrentSlot = 3;

	/*CurrentDigit :
	 * Second Digit / First Digit
	 * 		1		/	0		*/
	Local_u8CurrentDigit = 1;

	Local_u8Counter = 0;
	Local_u8CurrentY = 2;
	Local_u8StartFlag = 0;

	CLCD_voidSendString("  00 : 00 : 00  ");
	CLCD_voidWriteSpcialCharacter(Local_pu8Arrow,0,1,Local_pu8ArrowPoseArr[Local_u8Counter]);

	while(1)
	{
		/*Wait for pressing a key*/
		do
		{
			Local_u8PressedKey = KPD_GetPressedKey();
		}

		while(Local_u8PressedKey == 0xff);

		/*Get the pressed key and decide where I put it*/
		if(Local_u8PressedKey <= 9)
		{
			CLCD_voidWriteNumber(Local_u8PressedKey,0,Local_pu8ArrowPoseArr[Local_u8Counter]);

			switch(Local_u8CurrentSlot)
			{
			case 1 :Local_pu8SecsArr[Local_u8CurrentDigit] = Local_u8PressedKey;break;
			case 2 : Local_pu8MinsArr[Local_u8CurrentDigit] = Local_u8PressedKey;break;
			case 3 : Local_pu8HoursArrArr[Local_u8CurrentDigit] = Local_u8PressedKey;break;
			}

		}

		/*switch between digits*/
		if((Local_u8PressedKey == 'r'))
		{
			Local_u8CurrentDigit = 0;

			/*Clear second line only*/
			CLCD_voidGoToXY(1,0);
			CLCD_voidSendString("                ");
			CLCD_voidWriteSpcialCharacter(Local_pu8Arrow,0,1,Local_pu8ArrowPoseArr[++Local_u8Counter]);

		}
		if (Local_u8PressedKey == 'l')
		{
			Local_u8CurrentDigit = 1;
			/*Clear second line only*/
			CLCD_voidGoToXY(1,0);
			CLCD_voidSendString("                ");
			CLCD_voidWriteSpcialCharacter(Local_pu8Arrow,0,1,Local_pu8ArrowPoseArr[--Local_u8Counter]);

		}
		/*move to the next time slot*/
		if(Local_u8PressedKey == 'e')
		{

			/*move to next time slot*/
			Local_u8CurrentSlot--;
			Local_u8CurrentDigit = 1;

			/*Clear second line only*/
			CLCD_voidGoToXY(1,0);
			CLCD_voidSendString("                ");
			CLCD_voidWriteSpcialCharacter(Local_pu8Arrow,0,1,Local_pu8ArrowPoseArr[++Local_u8Counter]);

		}
		/*Clear second line only*/
		CLCD_voidGoToXY(1,0);
		CLCD_voidSendString("                ");
		CLCD_voidWriteSpcialCharacter(Local_pu8Arrow,0,1,Local_pu8ArrowPoseArr[++Local_u8Counter]);

		/*Start the timer*/
		if(Local_u8PressedKey == 's')
		{
			Local_u8Hours = Local_pu8HoursArrArr[1]*10 + Local_pu8HoursArrArr[0];
			Local_u8Mins  = Local_pu8MinsArr[1]*10 + Local_pu8MinsArr[0];
			Local_u8Secs  = Local_pu8SecsArr[1]*10 + Local_pu8SecsArr[0];
			//			CLCD_voidWriteNumber(Local_u8Secs,1,1);

//			/*Count seconds*/
//			for(Local_u8SecCount = 0 ; Local_u8SecCount <= Local_u8Secs ; Local_u8SecCount++)
//			{
//				CLCD_voidWriteNumber(Local_u8Secs-Local_u8SecCount,0,12);
//				_delay_ms(1000);
//			}
		}



	}
}
