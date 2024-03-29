#include "STD_TYPES.h"
#include "util/delay.h"

#include "DIO_interface.h"
#include "PORT_interface.h"
#include "CLCD_interface.h"
#include "KEYPAD_interface.h"

void main(void)
{
	u8 Local_u8CurrentSlot,Local_u8CurrentDigit,Local_u8CurrentY;
	u8 Local_u8Indx,Local_u8HourCount,Local_u8MinCount,Local_u8SecCount;
	u8 Local_pu8HoursArr[2] = {0,0} ,Local_pu8MinsArr[2] = {0,0} ,Local_pu8SecsArr[2] = {0,0};

	u8 Local_pu8ArrowPoseArr[6] = {2,3,7,8,12,13};

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

	/*Hamoksha*/
	u8 Local_pu8uHead[8] =	{
			0b00001110,
			0b00010001,
			0b00010001,
			0b00010001,
			0b00001110,
			0b00000100,
			0b00000100,
			0b00000100,
	};
	u8 Local_pu8uStand[8] =	{
			0b00011111,
			0b00000100,
			0b00000100,
			0b00000100,
			0b00000100,
			0b00001010,
			0b00010001,
			0b00000000,
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

	 Local_u8Indx = 0;
	 Local_u8CurrentY = 2;

	 CLCD_voidSendString("  00 : 00 : 00  ");
	 CLCD_voidWriteSpcialCharacter(Local_pu8Arrow,0,1,Local_pu8ArrowPoseArr[Local_u8Indx]);

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
			 CLCD_voidWriteNumber(Local_u8PressedKey,0,Local_pu8ArrowPoseArr[Local_u8Indx]);

			 switch(Local_u8CurrentSlot)
			 {
			 case 1 :Local_pu8SecsArr[Local_u8CurrentDigit] = Local_u8PressedKey;break;
			 case 2 : Local_pu8MinsArr[Local_u8CurrentDigit] = Local_u8PressedKey;break;
			 case 3 : Local_pu8HoursArr[Local_u8CurrentDigit] = Local_u8PressedKey;break;
			 }

		 }

		 /*switch between digits*/
		 if((Local_u8PressedKey == 'r'))
		 {
			 /*move to first digit*/
			 Local_u8CurrentDigit = 0;

			 /*make sure counter does not exceed size of Arrow Pose array*/
			 if (Local_u8Indx != 5)
			 {
				 Local_u8Indx++;
			 }

			 /*Clear second line only*/
			 CLCD_voidGoToXY(1,0);
			 CLCD_voidSendString("                ");
			 CLCD_voidWriteSpcialCharacter(Local_pu8Arrow,0,1,Local_pu8ArrowPoseArr[Local_u8Indx]);

		 }
		 if (Local_u8PressedKey == 'l')
		 {
			 /*move to second digit*/
			 Local_u8CurrentDigit = 1;

			 /*make sure counter does not exceed size of Arrow Pose array*/
			 if (Local_u8Indx > 0)
			 {
				 Local_u8Indx--;
			 }
			 /*Clear second line only*/
			 CLCD_voidGoToXY(1,0);
			 CLCD_voidSendString("                ");
			 CLCD_voidWriteSpcialCharacter(Local_pu8Arrow,0,1,Local_pu8ArrowPoseArr[Local_u8Indx]);
		 }
		 /*move to the next time slot*/
		 if(Local_u8PressedKey == 'e')
		 {

			 /*move to next time slot*/
			 Local_u8CurrentSlot--;
			 Local_u8CurrentDigit = 1;

			 /*make sure counter does not exceed size of Arrow Pose array*/
			 if (Local_u8Indx != 5)
			 {
				 Local_u8Indx++;
			 }
			 /*Clear second line only*/
			 CLCD_voidGoToXY(1,0);
			 CLCD_voidSendString("                ");
			 CLCD_voidWriteSpcialCharacter(Local_pu8Arrow,0,1,Local_pu8ArrowPoseArr[Local_u8Indx]);

		 }

		 /*Start the timer*/
		 if(Local_u8PressedKey == 's')
		 {

			 Local_u8Hours = Local_pu8HoursArr[1]*10 + Local_pu8HoursArr[0];
			 Local_u8Mins  = Local_pu8MinsArr[1]*10 + Local_pu8MinsArr[0];
			 Local_u8Secs  = Local_pu8SecsArr[1]*10 + Local_pu8SecsArr[0];



			 /*Count seconds*/
			 for(Local_u8SecCount = 1 ; Local_u8SecCount <= Local_u8Secs ; Local_u8SecCount++)
			 {
				 /*check if secs need 1 digit or 2 digits*/
				 if(Local_u8Secs-Local_u8SecCount < 10)
				 {
					 /*clear second digit*/
					 CLCD_voidWriteNumber(0,0,Local_pu8ArrowPoseArr[4]);

					 /*write on first digit*/
					 CLCD_voidWriteNumber(Local_u8Secs-Local_u8SecCount,0,Local_pu8ArrowPoseArr[5]);
				 }
				 else
				 {
					 /*write on 2 digits*/
					 CLCD_voidWriteNumber(Local_u8Secs-Local_u8SecCount,0,Local_pu8ArrowPoseArr[4]);

				 }
				 _delay_ms(1000);
			 }

			 /*Count Mins*/
			 for(Local_u8MinCount = 1 ; Local_u8MinCount <= Local_u8Mins;Local_u8MinCount++)
			 {
				 /*count down the mins*/
				 if(Local_u8Mins-Local_u8MinCount < 10)
				 {
					 /*clear second digit*/
					 CLCD_voidWriteNumber(0,0,Local_pu8ArrowPoseArr[2]);

					 CLCD_voidWriteNumber(Local_u8Mins-Local_u8MinCount,0,Local_pu8ArrowPoseArr[3]);

				 }
				 else
				 {
					 CLCD_voidWriteNumber(Local_u8Mins-Local_u8MinCount,0,Local_pu8ArrowPoseArr[2]);
				 }

				 /*count down 60 secs*/
				 for(Local_u8SecCount = 1 ; Local_u8SecCount <= 60 ; Local_u8SecCount++)
				 {
					 if(60-Local_u8SecCount < 10)
					 {
						 /*clear second digit*/
						 CLCD_voidWriteNumber(0,0,Local_pu8ArrowPoseArr[4]);

						 CLCD_voidWriteNumber(60-Local_u8SecCount,0,Local_pu8ArrowPoseArr[5]);
					 }
					 else
					 {
						 CLCD_voidWriteNumber(60-Local_u8SecCount,0,Local_pu8ArrowPoseArr[4]);

					 }
					 _delay_ms(1000);
				 }

			 }

			 /*Count Hours*/
			 for(Local_u8HourCount = 1 ; Local_u8HourCount <= Local_u8Hours ; Local_u8HourCount++)
			 {
				 /*count down hours*/
				 if(Local_u8Hours-Local_u8HourCount < 10)
				 {
					 /*clear second digit*/
					 CLCD_voidWriteNumber(0,0,Local_pu8ArrowPoseArr[0]);

					 CLCD_voidWriteNumber(Local_u8Hours-Local_u8HourCount,0,Local_pu8ArrowPoseArr[1]);

				 }
				 else
				 {
					 CLCD_voidWriteNumber(Local_u8Hours-Local_u8HourCount,0,Local_pu8ArrowPoseArr[0]);
				 }

				 /*count down 60 mins*/
				 for(Local_u8MinCount = 1 ; Local_u8MinCount <= 60;Local_u8MinCount++)
				 {
					 if(60-Local_u8MinCount < 10)
					 {
						 /*clear second digit*/
						 CLCD_voidWriteNumber(0,0,Local_pu8ArrowPoseArr[2]);
						 CLCD_voidWriteNumber(60-Local_u8MinCount,0,Local_pu8ArrowPoseArr[3]);

					 }
					 else
					 {
						 CLCD_voidWriteNumber(60-Local_u8MinCount,0,Local_pu8ArrowPoseArr[2]);
					 }

					 /*count down 60 secs*/
					 for(Local_u8SecCount = 1 ; Local_u8SecCount <= 60 ; Local_u8SecCount++)
					 {
						 if(60-Local_u8SecCount < 10)
						 {
							 /*clear second digit*/
							 CLCD_voidWriteNumber(0,0,Local_pu8ArrowPoseArr[4]);

							 CLCD_voidWriteNumber(60-Local_u8SecCount,0,Local_pu8ArrowPoseArr[5]);
						 }
						 else
						 {
							 CLCD_voidWriteNumber(60-Local_u8SecCount,0,Local_pu8ArrowPoseArr[4]);

						 }
						 _delay_ms(1000);
					 }

				 }
			 }

			 CLCD_voidSendCommand(1);
			 CLCD_voidSendString("Time is");
			 CLCD_voidGoToXY(1,0);
			 CLCD_voidSendString("finished");
			 CLCD_voidWriteSpcialCharacter(Local_pu8uHead,0,0,14);
			 CLCD_voidWriteSpcialCharacter(Local_pu8uStand,1,1,14);

			 DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN0,DIO_u8PIN_HIGH);
			 DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN1,DIO_u8PIN_HIGH);


		 }
	 }
}
