#include "STD_TYPES.h"
#include "util/delay.h"

#include "PORT_interface.h"
#include "DIO_interface.h"

#include "KEYPAD_interface.h"
#include "CLCD_interface.h"

void main(void)
{
	u8 Local_u8PressedValue,Local_u8FirstCounter,Local_u8SecondCounter,Local_u8CurrentX,Local_u8CurrentY,Local_u8Operator;
	u8 Local_u8CountOut,Local_u8CountIn;
	u8 Local_u8FirstOperandFlag,Local_u8SignFlag,Local_u8FloatFlag;

	u32 Local_u32CurrentDigit,Local_u32FirstOperand,Local_u32SecondOperand;
	u32 Local_u32Temp,Local_u32Result;
	u32 Local_u32FirstOperArr[28],Local_u32SecondOperArr[28];

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
	/*Initialize the PORTs and LCD*/
	PORT_voidInit();
	CLCD_voidInit();

	/*Initialize all flags*/
	Local_u8FirstCounter = 0;
	Local_u8CurrentX = 0;
	Local_u8CurrentY = 0;

	Local_u32CurrentDigit = 0;
	Local_u8SecondCounter = 0;

	Local_u32FirstOperand = 0;
	Local_u32SecondOperand = 0;

	Local_u8FirstOperandFlag = 0;
	Local_u8SignFlag = 0;
	Local_u8FloatFlag = 0;

	Local_u32Result = 0;


	for(u8 Local_u8Count = 0 ; Local_u8Count < 16 ;Local_u8Count++)
	{
		/*Clear LCD*/
		CLCD_voidSendCommand(1);
		/*Display Hamoksha*/
		CLCD_voidWriteSpcialCharacter(Local_pu8uHead,1,0,15-Local_u8Count);
		CLCD_voidWriteSpcialCharacter(Local_pu8uStand,2,1,15-Local_u8Count);

		/*Welcome To My Calculator*/
		CLCD_voidGoToXY(0,15-Local_u8Count+1);
		CLCD_voidSendString(" Welcome To");
		CLCD_voidGoToXY(1,15-Local_u8Count+1);
		CLCD_voidSendString(" My Calculator");
		_delay_ms(500);



	}
	_delay_ms(500);

	/*Clear LCD*/
	CLCD_voidSendCommand(1);

	/*Display Hamoksha*/
	CLCD_voidWriteSpcialCharacter(Local_pu8uHead,1,0,0);
	CLCD_voidWriteSpcialCharacter(Local_pu8uStand,2,1,0);

	/*To start press Enter*/
	CLCD_voidGoToXY(0,1);
	CLCD_voidSendString(" To Start");
	CLCD_voidGoToXY(1,1);
	CLCD_voidSendString(" Press Enter");


		while(1)
	{
		/*Wait for pressing a key */
		do
		{
			Local_u8PressedValue = KPD_GetPressedKey();

		}
		while(Local_u8PressedValue == 0xff);

		/*Clear the intro*/
		if (Local_u8CurrentY == 0)
		{
			/*Clear LCD*/
			CLCD_voidSendCommand(1);
		}


		/*Save each entered digit into an array*/
		if (Local_u8PressedValue <= 9)
		{
			/*Check which operand is entered the first or the second*/

			if(Local_u8FirstOperandFlag == 0)
			{
				Local_u32FirstOperArr[Local_u8FirstCounter++] = Local_u8PressedValue;
				CLCD_voidWriteNumber(Local_u8PressedValue,Local_u8CurrentX,Local_u8CurrentY++);

			}

			else
			{
				Local_u32SecondOperArr[Local_u8SecondCounter++] = Local_u8PressedValue;
				CLCD_voidWriteNumber(Local_u8PressedValue,Local_u8CurrentX,Local_u8CurrentY++);

			}

		}
		/*If any operator is entered that means the operand is fully entered*/
		if ((Local_u8PressedValue == '+' )|
				(Local_u8PressedValue == '-' )|
				(Local_u8PressedValue == '*' )|
				(Local_u8PressedValue == '/' )|
				(Local_u8PressedValue == '='))
		{

			/*If the operator not '=' that means the first operand is entered*/
			if(Local_u8PressedValue != '=')
			{
				/*Display the pressed key*/
				Local_u8Operator = Local_u8PressedValue;
				CLCD_voidGoToXY(Local_u8CurrentX,Local_u8CurrentY++);
				CLCD_voidSendData(Local_u8Operator);


				if(Local_u8FirstOperandFlag == 0)
				{
					/*Save The first operand*/
					for (Local_u8CountOut = 0; Local_u8CountOut < Local_u8FirstCounter ; Local_u8CountOut++)
					{
						Local_u32CurrentDigit = Local_u32FirstOperArr[Local_u8CountOut];

						for(Local_u8CountIn = 0 ; Local_u8CountIn < Local_u8FirstCounter-Local_u8CountOut-1 ;Local_u8CountIn++)
						{
							Local_u32CurrentDigit *=  10;
						}
						Local_u32FirstOperand += Local_u32CurrentDigit;
					}

				}
				/*Raise first operand flag to indicate that the first operand is fully entered*/
				Local_u8FirstOperandFlag = 1;
			}

			/*If the operator '=' that means the second operand is entered*/
			else if (Local_u8PressedValue == '=')
			{
				/*Display the pressed key*/
				CLCD_voidGoToXY(Local_u8CurrentX,Local_u8CurrentY++);
				CLCD_voidSendData(Local_u8PressedValue);

				/*Save The second operand*/
				for (Local_u8CountOut = 0; Local_u8CountOut < Local_u8SecondCounter ; Local_u8CountOut++)
				{
					Local_u32CurrentDigit = Local_u32SecondOperArr[Local_u8CountOut];

					for(Local_u8CountIn = 0 ; Local_u8CountIn < Local_u8SecondCounter-Local_u8CountOut-1 ;Local_u8CountIn++)
					{
						Local_u32CurrentDigit *=  10;
					}

					Local_u32SecondOperand += Local_u32CurrentDigit;
				}

				/* find the operator */
				switch(Local_u8Operator)
				{
				case '+':
					Local_u32Result = Local_u32FirstOperand + Local_u32SecondOperand;
					break;

				case '-':

					/*check if there is negative result ot not*/
					if (Local_u32FirstOperand >= Local_u32SecondOperand)
						Local_u32Result = Local_u32FirstOperand - Local_u32SecondOperand;

					else
					{
						Local_u32Result =  Local_u32SecondOperand - Local_u32FirstOperand;
						Local_u8SignFlag = 1;
					}
					break;

				case '*':
					Local_u32Result = Local_u32FirstOperand * Local_u32SecondOperand;
					break;

				case '/':

					/*Check if the result is float or not*/
					if (Local_u32FirstOperand % Local_u32SecondOperand != 0)
					{
						/*Just get the float number without using float datatype*/
						Local_u8FloatFlag = 1;
						Local_u32Temp = Local_u32FirstOperand*100;
						Local_u32Result = Local_u32Temp / Local_u32SecondOperand;
					}
					else
					{
						Local_u8FloatFlag = 0;
						Local_u32Result = Local_u32FirstOperand / Local_u32SecondOperand;
					}
					break;
				}

				if(Local_u8SignFlag == 1)
				{
					CLCD_voidSendData('-');
					Local_u8CurrentY++;

				}

				if (Local_u8FloatFlag == 1)
				{
					Local_u32Temp = Local_u32Result / 100;
					CLCD_voidWriteNumber(Local_u32Temp,Local_u8CurrentX,Local_u8CurrentY++);

					/*increase the Y pose based on number of Temp digits*/
					while(Local_u32Temp != 0)
					{
						Local_u8CurrentY++;
						Local_u32Temp /= 10;
					}

					CLCD_voidSendData('.');
					Local_u32Result = Local_u32Result % 100;

				}

				CLCD_voidWriteNumber(Local_u32Result,Local_u8CurrentX,Local_u8CurrentY++);

			}
		}
	}
}
