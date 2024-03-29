#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <util/delay.h>
#include "MAPPING.h"

#include "DIO_interface.h"
#include "PORT_interface.h"
#include "GIE_interface.h"
#include "TIMER_interface.h"
#include "ADC_interface.h"

#include "CLCD_interface.h"

static u16 PeriodTicks = 0;
static u16 ON_Ticks = 0;



void PWM(void);

void ICU(void);

void ICU_HW(void);

void main(void)
{
		u16 Local_u16Counter;
		u16 Local_u16Reading;
		u32 Local_u32Temp;
		u32 Local_u32Mapped;


		PORT_voidInit();
		ADC_voidInit();
		TIMER0_u8Init(NORMAL,DISCONNECT,DIV_BY_8);
//		TIMER1_voidInit();
	//	TIMER1_u8SetICR(20000);

		GIE_voidEnable();
		while(1)
		{
			ADC_u8StartConversionSynch(CHANNEL_ADC0,&Local_u16Reading);
			Local_u32Temp = Local_u16Reading;
			Local_u32Mapped = Mapping(0,255,150,1300,Local_u16Reading);
			DIO_u8SetPortValue(DIO_u8PORTB,Local_u32Mapped);
			TIMER1_u8SetChannelACompMatchVal(Local_u32Mapped);

		}


	PORT_voidInit();
	CLCD_voidInit();

//	TIMER0_voidInit();
	TIMER1_voidInit();
	ICU_voidInit();
	TIMER_u8SetCallBack(TIMER1_ICU_INT,&ICU_HW);


	GIE_voidEnable();

	while(1)
	{


		while((PeriodTicks == 0) && (ON_Ticks == 0));
		CLCD_voidGoToXY(0,0);
		CLCD_voidSendString("Period: ");
		CLCD_voidWriteNumber(PeriodTicks,0,8);
		CLCD_voidGoToXY(1,0);
		CLCD_voidSendString("ON Ticks: ");
		CLCD_voidWriteNumber(ON_Ticks,1,9);
	}

}

void ICU_HW(void)
{

	static u8 Local_u8Counter = 0;
	static u16 Reading_1 ,Reading_2,Reading_3;
	Local_u8Counter++;

	/*The first rising edge*/
	if(Local_u8Counter == 1)
	{
		Reading_1 = ICU_u16ReadingICU();
	}

	/*The second Rising edge*/
	else if (Local_u8Counter == 2)
	{
		Reading_2 = ICU_u16ReadingICU();

		PeriodTicks = Reading_2 - Reading_1;

		/*Change ICU trigger edge: Falling edge*/
		ICU_voidSetTiggerEdge(ICU_FALLING_EDGE);
	}

	/*Read timer0 to get ON time*/
	else if (Local_u8Counter == 3)
	{
		Reading_3 = ICU_u16ReadingICU();

		ON_Ticks = Reading_3 - Reading_2;

		ICU_voidEnableControl(ICU_INT_DISABLE);
	}

}
void ICU(void)
{
	static u8 Local_u8Counter = 0;

	Local_u8Counter++;

	/*The first rising edge*/
	if(Local_u8Counter == 1)
	{
		/*Reset Timer0*/
		TIMER1_voidSetTimerValue(0);
	}

	/*The second Rising edge*/
	else if (Local_u8Counter == 2)
	{
		/*Read Timer0 to get period time*/
		PeriodTicks = TIMER1_u16ReadTimerValue();

		/*Change INT0 to Falling edge*/
		//		EXTI_u8IntSetSenseControl(EXTI_INT0,FALLING_EDGE);
	}

	/*Read timer0 to get ON time*/
	else if (Local_u8Counter == 3)
	{
		/*Read timer0 to get ON time*/
		ON_Ticks = TIMER1_u16ReadTimerValue();
		ON_Ticks -= PeriodTicks ;

		/*Disable INT0*/
		//		EXTI_u8IntEnableControl(EXTI_INT0,DISABLED);
	}
}
void PWM(void)
{
	static u8 Local_u8Counter = 0;
	Local_u8Counter++;

	if(Local_u8Counter == 1)
	{
		DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN7,DIO_u8PIN_LOW);
	}
	else if(Local_u8Counter == 5)
	{
		DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN6,DIO_u8PIN_LOW);

	}
	else if(Local_u8Counter == 15)
	{
		DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN5,DIO_u8PIN_LOW);
	}
	else if(Local_u8Counter == 20)
	{
		Local_u8Counter = 0;
		DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN7,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN6,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN5,DIO_u8PIN_HIGH);

	}
}
