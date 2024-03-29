#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include <util/delay.h>

#include "DIO_interface.h"
#include "PORT_interface.h"
#include "GIE_interface.h"
#include "EXTI_interface.h"

#include "METDECT_interface.h"

//void Metal(void);

void main(void)
{

	PORT_voidInit();

	/*ON Change*/
	EXTI_voidInt0Init();

	GIE_voidEnable();


//	EXTI_u8Int0SetCallback(&Metal);
	while(1)
	{
		if(METDECT_u8MetalDetected() == 0)
		{
			DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN0,DIO_u8PIN_HIGH);
		}

		else
		{
			DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN0,DIO_u8PIN_LOW);

		}
	}
}

//void Metal(void)
//{
//	static u8 Local_u8Counter = 0;
//
//	TOGGLE_BIT(Local_u8Counter,0);
//	if(Local_u8Counter == 1)
//	{
//
//		DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN0,DIO_u8PIN_LOW);
////		EXTI_u8IntSetSenseControl(EXTI_INT0,FALLING_EDGE);
//
//	}
//	else
//	{
//		DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN0,DIO_u8PIN_HIGH);
////		EXTI_u8IntSetSenseControl(EXTI_INT0,RISING_EDGE);
//
//	}
//	//	if(Local_u8Counter == 1)
//	//	{
//	//		DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN0,DIO_u8PIN_HIGH);
//	//	}
//	//	else
//	//	{
//	//		DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN0,DIO_u8PIN_LOW);
//	//	}
//}
