/***********************************************************************/
/***********************************************************************/
/************************ AUTHER : Hanin Anwar  ************************/
/************************ LAYER  : HAL          ************************/
/************************ SWC    : KEYPAD          ************************/
/************************ VERSION : 1.00         ************************/
/***********************************************************************/
/***********************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "KEYPAD_private.h"
#include "KEYPAD_config.h"
#include "KEYPAD_interface.h"

u8 KPD_GetPressedKey(void)
{
	u8 Local_u8ColumnIdx , Local_u8RowIdx,Local_u8PinSate;
	u8 Local_u8PressedKey = KPD_NO_PRESSED_KEY;
	static u8 Local_u8KPDArr[ROW_NUM][COLUMN_NUM] = KPD_ARR_VAL;
	static u8 Local_u8ColumnArr[COLUMN_NUM] = {KPD_COLUMN0_PIN,KPD_COLUMN1_PIN,KPD_COLUMN2_PIN,KPD_COLUMN3_PIN};
	static u8 Local_u8RowArr[ROW_NUM] = {KPD_ROW0_PIN,KPD_ROW1_PIN,KPD_ROW2_PIN,KPD_ROW3_PIN};

	for(Local_u8ColumnIdx = 0 ; Local_u8ColumnIdx < COLUMN_NUM ; Local_u8ColumnIdx++)
	{
		/*Activate Current Column*/
		DIO_u8SetPinValue(KPD_PORT,Local_u8ColumnArr[Local_u8ColumnIdx],DIO_u8PIN_LOW);

		for(Local_u8RowIdx = 0 ; Local_u8RowIdx < ROW_NUM ; Local_u8RowIdx++)
		{
			/*Read The Current Row*/
			DIO_u8GetPinValue(KPD_PORT,Local_u8RowArr[Local_u8RowIdx],&Local_u8PinSate);

			/*Check it the Switch is pressed*/
			if (DIO_u8PIN_LOW == Local_u8PinSate)
			{
				Local_u8PressedKey = Local_u8KPDArr[Local_u8RowIdx][Local_u8ColumnIdx];

				/*Polling(busy waiting) until the key is released*/
				while(DIO_u8PIN_LOW == Local_u8PinSate)
				{
					DIO_u8GetPinValue(KPD_PORT,Local_u8RowArr[Local_u8RowIdx],&Local_u8PinSate);
				}
				return Local_u8PressedKey;
			}

		}

		/*Deactivate Current Column*/
		DIO_u8SetPinValue(KPD_PORT,Local_u8ColumnArr[Local_u8ColumnIdx],DIO_u8PIN_HIGH);
	}


	return Local_u8PressedKey;
}
