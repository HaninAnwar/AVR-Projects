/***********************************************************************/
/***********************************************************************/
/************************ AUTHER : Hanin Anwar  ************************/
/************************ LAYER  : HAL       	***********************/
/************************ SWC    : ULTRASNOIC   ************************/
/************************ VERSION : 1.00        ************************/
/***********************************************************************/
/***********************************************************************/

#include "STD_TYPES.h"
#include <util/delay.h>

#include "TIMER_interface.h"
#include "DIO_interface.h"

#include "ULTSONC_config.h"
#include "ULTSONC_interface.h"
#include "ULTSONC_private.h"


static u16 ULTSONC_u16PulseWedth = 0;
static u16 ULTSONC_u16Distance = 0;
static u8  ULTSONC_u8ObstecalFlag = ULTSONC_NO_OBSTACLE;


void Ultrasonic_Echo(void);
void Ultrasonic_Trigger(void);


void ULTSONC_voidInitUltrasnoic(void)
{


	TIMER_u8SetCallBack(TIMER1_OVERFLOW_INT,&Ultrasonic_Trigger);

	TIMER_u8SetCallBack(TIMER1_ICU_INT,&Ultrasonic_Echo);


}

u8 ULTSONC_u8GetUltrasnoic(void)
{
	return ULTSONC_u8ObstecalFlag;
}

void Ultrasonic_Trigger(void)
{
	static u8 Local_u8Counter = 0;
	Local_u8Counter++;

	/*generate trigger pulse*/
	if(Local_u8Counter == ULTSONC_CheckingTime)
	{
		DIO_u8SetPinValue(ULTSONC_TRIGGER_PORT,ULTSONC_TRIGGER_PIN,DIO_u8PIN_HIGH);
		_delay_us(10);
		DIO_u8SetPinValue(ULTSONC_TRIGGER_PORT,ULTSONC_TRIGGER_PIN,DIO_u8PIN_LOW);
		ICU_voidInit();

	}
}
void Ultrasonic_Echo(void)
{
	static u8 Local_u8Counter = 0;
	static u16 Local_u16PulseStart , Local_u16PulseEnd;
	Local_u8Counter++;

	/*Pulse is started*/
	if(Local_u8Counter % 2 == 1)
	{
		Local_u16PulseStart = ICU_u16ReadingICU();

		ICU_u8SetTiggerEdge(ICU_FALLING_EDGE);
	}
	/*Pulse is ended*/
	else
	{
		Local_u16PulseEnd = ICU_u16ReadingICU();

		ULTSONC_u16Distance = (Local_u16PulseEnd - Local_u16PulseStart)/466;

		if(ULTSONC_u16Distance <= ULTSONC_MinObstacle)
		{
			ULTSONC_u8ObstecalFlag = ULTSONC_OBSTACLE;
		}
		else
		{
			ULTSONC_u8ObstecalFlag = ULTSONC_NO_OBSTACLE;

		}
		ICU_u8EnableControl(ICU_INT_DISABLE);

	}
}
