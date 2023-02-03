#include "STD_TYPES.h"
#include <util/delay.h>

#include "DIO_interface.h"
#include "PORT_interface.h"
#include "TIMER_interface.h"

#include "MOTOR_interface.h"

#include "MAPPING.h"

void main(void)
{
	PORT_voidInit();

//	MOTOR_voidServoRotate(TIMER1_CHANNEL_A,90);

	TIMER1_u8Init(TIMER1_CHANNEL_A,FAST_PWM,DISCONNECT,TIMER_DIV_BY_8);

	TIMER1_u8SetICR(20000);
	TIMER1_u8SetChannelACompMatchVal(1000);
	while(1)
	{

	}
}
