#include "STD_TYPES.h"

#include "PORT_interface.h"
#include "DIO_interface.h"
#include "GIE_interface.h"
#include "EXTI_interface.h"

#include "LED_interface.h"

void INT1_ISR(void);

void main(void)
{
	PORT_voidInit();

	EXTI_u8IntSetSenseControl(EXTI_INT2,RISING_EDGE);
	EXTI_u8IntEnableControl(EXTI_INT2,ENABLED);
//	EXTI_voidInt1Init();
	GIE_voidEnable();

	EXTI_u8Int2SetCallback(&INT1_ISR);
	while(1)
	{

	}
}


void INT1_ISR(void)
{
	LED_T *LED1;
	LED1->ConnectionType = LED_u8SOURCE;
	LED1->Port = DIO_u8PORTB;
	LED1->Pin = DIO_u8PIN0;

	LED_voidTurnOn(LED1);

}
