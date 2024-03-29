#include "STD_TYPES.h"
#include <util/delay.h>

#include "PORT_interface.h"
#include "DIO_interface.h"
#include "CLCD_interface.h"
#include "MOTOR_interface.h"

void HamokshaRun(void);

void main(void)
{

	u8 Local_u8PressedKey,Local_u8RotationDir,Local_u8Counter,Local_u8EnterFlag;
	u8 Local_u8PressedArr[3] = {0,0,0};
	u16 Local_u16Angle;
	PORT_voidInit();
	CLCD_voidInit();

	/*Welcoming*/
	HamokshaRun();

	CLCD_voidSendCommand(1);
	CLCD_voidSendString("Welcome To Motor");
	CLCD_voidGoToXY(1,0);
	CLCD_voidSendString("Dashboard App");
	_delay_ms(3000);

	while(1)
	{

		Local_u8Counter = 0;
		Local_u8EnterFlag = 0;

		/*Start Menu*/
		CLCD_voidSendCommand(1);
		CLCD_voidSendString(" 1.DC 2.Stepper");
		CLCD_voidGoToXY(1,5);
		CLCD_voidSendString("3.Exit");
		do
		{
			Local_u8PressedKey = KPD_GetPressedKey();
		}
		while(Local_u8PressedKey > 4);

		/*DC motor*/
		if(Local_u8PressedKey == 1)
		{
			/*choose rotation direction*/
			CLCD_voidSendCommand(1);
			CLCD_voidSendString("1.Rotate C.W");
			CLCD_voidGoToXY(1,0);
			CLCD_voidSendString("2.Rotate C.C.W");

			do
			{
				Local_u8PressedKey = KPD_GetPressedKey();
			}
			while(Local_u8PressedKey > 3);

			/*C.W Rotation*/
			if(Local_u8PressedKey == 1)
			{
				Local_u8RotationDir = MOTOR_CLK_WISE;
			}

			/*C.C.W Rotation*/
			else if(Local_u8PressedKey == 2)
			{
				Local_u8RotationDir = MOTOR_UNTI_CLK_WISE;
			}

			/*Start Rotation until any key is pressed*/
			CLCD_voidSendCommand(1);
			CLCD_voidSendString("To stop press");
			CLCD_voidGoToXY(1,0);
			CLCD_voidSendString("any key");

			/*wait for pressing a key*/
			do
			{
				MOTOR_u8DCRotate(Local_u8RotationDir);
				Local_u8PressedKey = KPD_GetPressedKey();
			}
			while(Local_u8PressedKey == 0xff);

			/*Stop the motor*/
			MOTOR_voidDCStop();

		}

		/*Stepper motor*/
		else if(Local_u8PressedKey == 2)
		{

			/*choose rotation direction*/
			CLCD_voidSendCommand(1);
			CLCD_voidSendString("1.Rotate C.W");
			CLCD_voidGoToXY(1,0);
			CLCD_voidSendString("2.Rotate C.C.W");

			do
			{
				Local_u8PressedKey = KPD_GetPressedKey();
			}
			while(Local_u8PressedKey > 3);

			/*C.W Rotation*/
			if(Local_u8PressedKey == 1)
			{
				Local_u8RotationDir = MOTOR_CLK_WISE;
			}

			/*C.C.W Rotation*/
			else if(Local_u8PressedKey == 2)
			{
				Local_u8RotationDir = MOTOR_UNTI_CLK_WISE;
			}

			/*Set desired angle*/
			CLCD_voidSendCommand(1);
			CLCD_voidSendString("Enter Angle :");

			/*User did not press : enter*/
			while(Local_u8EnterFlag != 1)
			{
				/*Wait for press angle*/
				do
				{
					Local_u8PressedKey = KPD_GetPressedKey();
				}
				while(Local_u8PressedKey == 0xff);

				/*Store angle digits*/
				if(Local_u8PressedKey < 10)
				{
					Local_u8Counter++;
					Local_u8PressedArr[Local_u8Counter-1] = Local_u8PressedKey;
					CLCD_voidWriteNumber(Local_u8PressedKey,1,Local_u8Counter-1);

				}

				else if(Local_u8PressedKey == 'e')
				{
					/*Raise flag : user entered the desired angle*/
					Local_u8EnterFlag = 1;

					/*Check the angle digits : 2 or 3*/
					if(Local_u8Counter == 2)
					{
						Local_u16Angle = Local_u8PressedArr[0]*10+Local_u8PressedArr[1]*1+Local_u8PressedArr[2];

					}
					else if(Local_u8Counter == 3)
					{
						Local_u16Angle = Local_u8PressedArr[0]*100+Local_u8PressedArr[1]*10+Local_u8PressedArr[2];

					}

					MOTOR_u8StepperRotateAngle(Local_u16Angle,Local_u8RotationDir);

					/*Stop the motor*/
					MOTOR_voidStepperStop();

					CLCD_voidSendCommand(1);
					CLCD_voidSendString("Angle is reached");
					_delay_ms(3000);
				}
			}
		}

		/*Exit*/
		else if(Local_u8PressedKey == 3)
		{
			CLCD_voidSendCommand(1);
			break;
		}
	}

}

void HamokshaRun(void)
{
	u8 Local_u8Counter;
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
	u8 Local_pu8uRun1[8] =	{
			0b00011100,
			0b00000110,
			0b00000101,
			0b00000100,
			0b00000100,
			0b00001100,
			0b00010100,
			0b00000000,
	};

	u8 Local_pu8uRun2[8] =	{
			0b00000111,
			0b00001100,
			0b00010100,
			0b00000100,
			0b00000100,
			0b00000110,
			0b00000101,
			0b00000000,
	};

	for(Local_u8Counter = 0; Local_u8Counter < 15 ;Local_u8Counter++)
	{
		CLCD_voidSendCommand(1);
		/*Hamoksha's Head*/
		CLCD_voidWriteSpcialCharacter(Local_pu8uHead,1,0,Local_u8Counter);

		if (Local_u8Counter %2 == 0)
		{
			CLCD_voidWriteSpcialCharacter(Local_pu8uRun1,2,1,Local_u8Counter);

		}
		else
		{
			CLCD_voidWriteSpcialCharacter(Local_pu8uRun2,2,1,Local_u8Counter);

		}
		_delay_ms(250);


	}
}
