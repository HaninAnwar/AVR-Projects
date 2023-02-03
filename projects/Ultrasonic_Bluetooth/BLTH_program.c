#include "STD_TYPES.h"

#include "BLTH_config.h"
#include "BLTH_interface.h"
#include "BLTH_private.h"

#include "USART_interface.h"

void Bluetooth(void);

u8 BLTH_MotionFlag = 0;

u8 BLTH_u8MotionControl(void)
{
	USART_u8ReceiverInterruptControl(RX_INT_ENABLE);
	USART_voidSetRxCallBackFunc(&Bluetooth);

	return BLTH_MotionFlag;
}

void Bluetooth(void)
{
	u8 Local_u8Reading;
	Local_u8Reading = USART_u8Receive_Int();

	if(Local_u8Reading == '2')
	{
		BLTH_MotionFlag = 0;
	}

	else if(Local_u8Reading == '1')
	{
		BLTH_MotionFlag = 1;

	}
}
