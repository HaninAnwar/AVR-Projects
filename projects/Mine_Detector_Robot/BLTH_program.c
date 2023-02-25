#include "STD_TYPES.h"

#include "BLTH_config.h"
#include "BLTH_interface.h"
#include "BLTH_private.h"

#include "USART_interface.h"

void Bluetooth(void);

static u8 BLTH_MotionFlag = BLTH_STOP;

void BLTH_voidInitBluetooth(void)
{
	USART_u8ReceiverInterruptControl(RX_INT_ENABLE);
	USART_voidSetRxCallBackFunc(&Bluetooth);
}

u8 BLTH_u8GetBluetoothReading(void)
{
	return BLTH_MotionFlag;
}

void Bluetooth(void)
{
	u8 Local_u8Reading;
	Local_u8Reading = USART_u8Receive_Int();

	if(Local_u8Reading == '2')
	{
		BLTH_MotionFlag = BLTH_STOP;
	}

	else if(Local_u8Reading == '1')
	{
		BLTH_MotionFlag = BLTH_MOVE;

	}
}
