#include "STD_TYPES.h"
#include <util/delay.h>

#include "DIO_interface.h"
#include "PORT_interface.h"
#include "TIMER_interface.h"
#include "GIE_interface.h"
#include "EXTI_interface.h"
#include "USART_interface.h"

#include "CLCD_interface.h"
#include "ULTSONC_interface.h"
#include "BLTH_interface.h"
#include "METDECT_interface.h"

//#include "ULTSONC_program.c"

extern u8 ULTSONC_u8ObstecalFlag,BLTH_MotionFlag,METDECT_MineFlag;

void main(void)
{
	PORT_voidInit();
	CLCD_voidInit();

	/*Initialize timer0 for generate trigger pulse each 1ms*/
	TIMER0_u8Init(NORMAL,DISCONNECT,TIMER_DIV_BY_1);

	/*Timer1 for echo pulse calculation*/
	TIMER1_u8Init(TIMER1_CHANNEL_A,NORMAL,DISCONNECT,TIMER_DIV_BY_1);

	USRAT_voidInit();

	/*EXT0 On Change for Metal Detector*/
	EXTI_voidInt0Init();

	GIE_voidEnable();


	while(1)
	{

		if((ULTSONC_u16ObstacleDetection() == 0) && (BLTH_u8MotionControl() == 1) && (METDECT_u8MetalDetected() == 0))
		{
			DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN0,DIO_u8PIN_HIGH);
		}
		else
		{
			DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN0,DIO_u8PIN_LOW);

		}
	}
}


