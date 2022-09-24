#include "STD_TYPES.h"
#include "MAPPING.h"

#include <util/delay.h>
#include "PORT_interface.h"
#include "DIO_interface.h"
#include "ADC_interface.h"
#include "CLCD_interface.h"
#include "GIE_interface.h"

void NotificationFunc(void);

u16 App_u16ADCReading;
void main(void)
{

	u8 Local_u8MilliVolt,Local_u8Temp;

	PORT_voidInit();
	ADC_voidInit();
	CLCD_voidInit();

	GIE_voidEnable();

	while(1)
	{
		ADC_u8StartConversionAsynch(CHANNEL_ADC0,&App_u16ADCReading,&NotificationFunc);
//		CLCD_voidSendCommand(1);
//
//		Local_u8Reading = ADC_u8GetChannelReading(CHANNEL_ADC0);
//		//		Local_u8MilliVolt = ((u32)Local_u8Reading*5000UL)/256UL;
//		//		Local_u8Temp = Local_u8MilliVolt / 10;
//
//		if(Local_u8Reading <= 30)
//		{
//
//			DIO_u8SetPortValue(DIO_u8PORTB,0b11111111);
//		}
//		else if(Local_u8Reading <= 60)
//		{
//			DIO_u8SetPortValue(DIO_u8PORTB,0b11111110);
//		}
//
//		else if(Local_u8Reading <= 90)
//		{
//			DIO_u8SetPortValue(DIO_u8PORTB,0b11111100);
//		}
//		else if(Local_u8Reading <= 120)
//		{
//			DIO_u8SetPortValue(DIO_u8PORTB,0b11111000);
//		}
//		else if(Local_u8Reading <= 150)
//		{
//			DIO_u8SetPortValue(DIO_u8PORTB,0b11110000);
//		}
//		else if(Local_u8Reading <= 180)
//		{
//			DIO_u8SetPortValue(DIO_u8PORTB,0b11100000);
//		}
//		else if(Local_u8Reading <= 210)
//		{
//			DIO_u8SetPortValue(DIO_u8PORTB,0b11000000);
//		}
//		else if(Local_u8Reading <= 240)
//		{
//			DIO_u8SetPortValue(DIO_u8PORTB,0b10000000);
//		}
//		else
//		{
//			DIO_u8SetPortValue(DIO_u8PORTB,0b00000000);
//		}
//
//		Local_u8Temp = Mapping(0,245,0,8,Local_u8Reading);
//
//		CLCD_voidWriteNumber(Local_u8Temp,0,0);
//
//		_delay_ms(500);

	}
}

void NotificationFunc(void)
{
	DIO_u8SetPortValue(DIO_u8PORTB,App_u16ADCReading);
}
