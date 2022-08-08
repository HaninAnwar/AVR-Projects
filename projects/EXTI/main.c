#include "STD_TYPES.h"

#include "PORT_interface.h"
#include "DIO_interface.h"
#include "GIE_interface.h"
#include "EXTI_interface.h"

#include "LED_interface.h"

void main(void)
{
	PORT_voidInit();

	EXTI_voidInt0Init();
	GIE_voidEnable();

	while(1)
	{

	}
}

void __vector_1(void) __attribute__((signal));
void __vector_1(void)
{
	LED_T *LED1;
	LED1->ConnectionType = LED_u8SOURCE;
	LED1->Port = DIO_u8PORTA;
	LED1->Pin = DIO_u8PIN0;

	LED_voidTurnOn(LED1);

}
