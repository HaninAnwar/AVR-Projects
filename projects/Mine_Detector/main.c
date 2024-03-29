#include "STD_TYPES.h"
#include <util/delay.h>

#include "DIO_interface.h"
#include "PORT_interface.h"
#include "EXTI_interface.h"
#include "GIE_interface.h"
#include "TIMER_interface.h"

#include "CLCD_interface.h"
#include "MOTOR_interface.h"
#include "MAPPING.h"


void Ultrasonic_Func(void);
void OverFlow_Func(void);


static u16 Ultrasonic_Time = 0;
static u16 OverTime = 0;

void main (void)
{
	DC_Motor Motor1 ,Motor2 ,Motor3 ,Motor4;

	Motor1.Port = DIO_u8PORTA;
	Motor1.Pin1 = DIO_u8PIN0;
	Motor1.Pin2 = DIO_u8PIN1;

	Motor2.Port = DIO_u8PORTA;
	Motor2.Pin1 = DIO_u8PIN2;
	Motor2.Pin2 = DIO_u8PIN3;


	Motor3.Port = DIO_u8PORTA;
	Motor3.Pin1 = DIO_u8PIN3;
	Motor3.Pin2 = DIO_u8PIN4;

	Motor4.Port = DIO_u8PORTA;
	Motor4.Pin1 = DIO_u8PIN5;
	Motor4.Pin2 = DIO_u8PIN6;

	u16 Local_u16Value,Local_u16Temp;


	PORT_voidInit();
	CLCD_voidInit();


	CLCD_voidSendCommand(1);
	TIMER1_u8Init(TIMER1_CHANNEL_A,NORMAL,DISCONNECT,TIMER_DIV_BY_1);
	ICU_voidInit();

	TIMER_u8SetCallBack(TIMER1_ICU_INT,&Ultrasonic_Func);
//	TIMER_u8SetCallBack(TIMER1_OVERFLOW_INT,&OverFlow_Func);

	GIE_voidEnable();

	DIO_u8SetPinValue(DIO_u8PORTD,DIO_u8PIN7,DIO_u8PIN_LOW);
	DIO_u8SetPinValue(DIO_u8PORTD,DIO_u8PIN7,DIO_u8PIN_HIGH);
	_delay_us(10);
	DIO_u8SetPinValue(DIO_u8PORTD,DIO_u8PIN7,DIO_u8PIN_LOW);

	while(Ultrasonic_Time == 0);

	/*distance = ultrasonic_time*34300*8000000/2 */
	Local_u16Temp = Ultrasonic_Time + 65535*OverTime;

	Local_u16Value = Ultrasonic_Time/466;
	CLCD_voidSendCommand(1);

	CLCD_voidWriteNumber(Ultrasonic_Time,0,0);

	_delay_ms(200);
	while(1)
	{


	}
}

void OverFlow_Func(void)
{
	OverTime++;
}
void Ultrasonic_Func(void)
{
	static u8 Local_u8Counter = 0;

	static u16 Local_u8PulseStart , Local_u8PulseEnd;

	Local_u8Counter++;


	/*Pulse is started*/
	if(Local_u8Counter  == 1)
	{
		Local_u8PulseStart = ICU_u16ReadingICU();
//		OverTime = 0;
//		TIMER1_voidSetTimerValue(0);
		ICU_voidSetTiggerEdge(FALLING_EDGE);

	}

	/*Pulse is ended*/
	else if(Local_u8Counter == 2)
	{
		Local_u8PulseEnd = ICU_u16ReadingICU();
		Ultrasonic_Time =  Local_u8PulseEnd - Local_u8PulseStart;

		ICU_voidEnableControl(ICU_INT_DISABLE);
		ICU_voidSetTiggerEdge(RISING_EDGE);


	}



}
