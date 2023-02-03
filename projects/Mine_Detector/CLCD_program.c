/***********************************************************************/
/***********************************************************************/
/************************ AUTHER : Hanin Anwar  ************************/
/************************ LAYER  : HAL          ************************/
/************************ SWC    : CLCD          ************************/
/************************ VERSION : 1.00         ************************/
/***********************************************************************/
/***********************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <util/delay.h>


#include "DIO_interface.h"
#include "CLCD_interface.h"
#include "CLCD_config.h"
#include "CLCD_private.h"


void CLCD_voidSendCommand(u8 Copy_u8Command)
{
	/*Set RS LOW for command*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RS_PIN,DIO_u8PIN_LOW);

	/*Set RW LOW for write*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RW_PIN,DIO_u8PIN_LOW);

	/*Set Command to data port*/
	DIO_u8SetPortValue(CLCD_DATA_PORT,Copy_u8Command);

	/*Send enable pulse*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8PIN_LOW);

}

void CLCD_voidSendData(u8 Copy_u8Data)
{

	/*Set RS HIGH for data*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RS_PIN,DIO_u8PIN_HIGH);

	/*Set RW LOW for write*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RW_PIN,DIO_u8PIN_LOW);

	/*Set Data to data port*/
	DIO_u8SetPortValue(CLCD_DATA_PORT,Copy_u8Data);

	/*Send enable pulse*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8PIN_LOW);

}


void CLCD_voidInit(void)
{
	//Correspond to datasheet//

	/*Wait for more than 30 ms */
	_delay_ms(40);

	/*Function Set :
	 * 	RS	RW	DB7	 DB6	DB5	  DB4	DB3		DB2 	DB1 	DB0
	 * 	0	0	 0	  0      1	   1     N       F       X       X
	 * NoOflines = 2 , FontSize = 5*8
	 * N = 1 , F = 0*/

	CLCD_voidSendCommand(0b00111000);

	/*Display control :
	 * 	RS	RW	DB7	 DB6	DB5	  DB4	DB3		DB2 	DB1 	DB0
	 * 	0	0	 0	  0      0	   0     1       D       C       B
	 * D : Display enable , C : Cursor enable , B : Blink Cursor
	 * D = 1 , C = 0 , B = 0*/

	CLCD_voidSendCommand(0b00001100);

	/*Clear Display*/
	CLCD_voidSendCommand(1);


}

void CLCD_voidSendString(const char* Copy_pcString )
{
	u8 Local_u8Counter = 0;

	while(Copy_pcString[Local_u8Counter] != '\0')
	{
		CLCD_voidSendData(Copy_pcString[Local_u8Counter]);
		Local_u8Counter++;

	}
}

void CLCD_voidGoToXY(u8 Copy_u8XPose ,u8 Copy_u8YPose)
{
	u8 Local_u8Address;
	if (Copy_u8XPose == 0)
	{
		/*Location is at first line */
		Local_u8Address = Copy_u8YPose;
	}

	else if (Copy_u8XPose == 1)
	{
		/*Location is at second line */
		Local_u8Address = Copy_u8YPose + 0x40;
	}

	/*OR to set most bit to 1 to set DDRAM Address*/
	CLCD_voidSendCommand(Local_u8Address | 1<<7);
}


void CLCD_voidWriteSpcialCharacter(u8* Copy_pu8Pattern , u8 Copy_u8PatternNum , u8 Copy_u8XPose ,u8 Copy_u8YPose)
{
	u8 Local_u8CGRAMAddress = 0;
	u8 Local_u8Counter = 0;

	/*Calculate CGRAM Adress */
	Local_u8CGRAMAddress = Copy_u8PatternNum *8;

	/*Send CGRAM Address Command to LCD with setting bit 6 and clearing bit 7 */
	CLCD_voidSendCommand(Local_u8CGRAMAddress | 1 <<6);

	/*Write Pattern Data to GCRAM to Save it*/
	for(Local_u8Counter = 0 ; Local_u8Counter < 8 ; Local_u8Counter++)
	{
		CLCD_voidSendData(Copy_pu8Pattern[Local_u8Counter]);

	}
	/*Go back to DDRAM to display the pattern*/
	CLCD_voidGoToXY(Copy_u8XPose,Copy_u8YPose);

	/*Display the pattern written in CGRAM*/
	CLCD_voidSendData(Copy_u8PatternNum);
}

void CLCD_voidWriteNumber(u32 Copy_u32Number,u8 Copy_u8XPose , u8 Copy_u8YPose)
{
	u8 Local_u8Counter , Local_u8NumberOfDigits , Local_pu8Arr[30] , Local_u8X , Local_u8Y;
	u32 Local_u32Number = Copy_u32Number;

	Local_u8Counter = 0;
	Local_u8NumberOfDigits = 0;
	Local_u8X = Copy_u8XPose;
	Local_u8Y = Copy_u8YPose;

	while(Local_u32Number != 0)
	{
		Local_pu8Arr[Local_u8NumberOfDigits++] = Local_u32Number % 10;
		Local_u32Number /= 10;
	}

	for(Local_u8Counter = Local_u8NumberOfDigits - 1 ; (Local_u8Counter >= 0)&& (Local_u8Y < (Copy_u8YPose + Local_u8NumberOfDigits)); Local_u8Counter--)
	{
//
		switch(Local_pu8Arr[Local_u8Counter])
		{
		case 0 :  CLCD_voidGoToXY(Local_u8X ,  Local_u8Y++); CLCD_voidSendData('0');break;
		case 1 :  CLCD_voidGoToXY(Local_u8X ,  Local_u8Y++); CLCD_voidSendData('1');break;
		case 2 :  CLCD_voidGoToXY(Local_u8X ,  Local_u8Y++); CLCD_voidSendData('2');break;
		case 3 :  CLCD_voidGoToXY(Local_u8X ,  Local_u8Y++); CLCD_voidSendData('3');break;
		case 4 :  CLCD_voidGoToXY(Local_u8X ,  Local_u8Y++); CLCD_voidSendData('4');break;
		case 5 :  CLCD_voidGoToXY(Local_u8X ,  Local_u8Y++); CLCD_voidSendData('5');break;
		case 6 :  CLCD_voidGoToXY(Local_u8X ,  Local_u8Y++); CLCD_voidSendData('6');break;
		case 7 :  CLCD_voidGoToXY(Local_u8X ,  Local_u8Y++); CLCD_voidSendData('7');break;
		case 8 :  CLCD_voidGoToXY(Local_u8X ,  Local_u8Y++); CLCD_voidSendData('8');break;
		case 9 :  CLCD_voidGoToXY(Local_u8X ,  Local_u8Y++); CLCD_voidSendData('9');break;

		}
	}

	if (Copy_u32Number == 0)
	{
		CLCD_voidGoToXY(Local_u8X , Local_u8Y++);
		CLCD_voidSendData('0');
	}

}
