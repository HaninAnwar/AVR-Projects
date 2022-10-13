/********************* *************************************************/
/***********************************************************************/
/************************ AUTHER : Hanin Anwar  ************************/
/************************ LAYER  : HAL          ************************/
/************************ SWC    : SSD          ************************/
/************************ VERSIO : 1.00         ************************/
/***********************************************************************/
/***********************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_register.h"
#include "DIO_interface.h"

#include "SSD_interface.h"
#include "SSD_config.h"
#include "SSD_private.h"


u8 SSD_u8SetNumber(u8 Copy_u8Number , SSD_T *SSD)
{
    u8 Local_Errorstate = 0;
    u8 Local_NumArr[10] = {	0b00111111 ,
							0b00000110 ,
							0b01011011 ,
							0b01001111 ,
							0b01100110 ,
							0b01101101 ,
							0b01111101 ,
							0b00000111 ,
							0b01111111 ,
							0b01101111
    						};

    if(SSD->ComType == SSD_u8COM_ANODE)
    {
    	DIO_u8SetPinValue(SSD->EnablePort ,SSD->EnablePin , DIO_u8PIN_HIGH);
    	DIO_u8SetPortValue(SSD->Port,~Local_NumArr[Copy_u8Number]);
    }
    else if (SSD->ComType == SSD_u8COM_CATHODE)
    {
    	DIO_u8SetPinValue(SSD->EnablePort ,SSD->EnablePin , DIO_u8PIN_LOW);
		DIO_u8SetPortValue(SSD->Port,Local_NumArr[Copy_u8Number]);

    }

    else
    {
    	Local_Errorstate = 1;
    }
    return Local_Errorstate;

}
u8 SSD_u8Enable(SSD_T *SSD)
{
	u8 Local_Errorstate = 0;

	if(SSD->ComType == SSD_u8COM_ANODE)
	{
		DIO_u8SetPinValue(SSD->EnablePort ,SSD->EnablePin , DIO_u8PIN_HIGH);
	}
	else if (SSD->ComType == SSD_u8COM_CATHODE)
	{
		DIO_u8SetPinValue(SSD->EnablePort ,SSD->EnablePin , DIO_u8PIN_LOW);

	}

	else
	{
		Local_Errorstate = 1;
	}
	return Local_Errorstate;
}
u8 SSD_u8Disable(SSD_T *SSD)
{

	u8 Local_Errorstate = 0;

	if(SSD->ComType == SSD_u8COM_ANODE)
	{
		DIO_u8SetPinValue(SSD->EnablePort ,SSD->EnablePin , DIO_u8PIN_LOW);
	}
	else if (SSD->ComType == SSD_u8COM_CATHODE)
	{
		DIO_u8SetPinValue(SSD->EnablePort ,SSD->EnablePin , DIO_u8PIN_HIGH);

	}

	else
	{
		Local_Errorstate = 1;
	}
	return Local_Errorstate;
}
