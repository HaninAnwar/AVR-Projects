#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <util/delay.h>

#include "PORT_interface.h"
#include "DIO_interface.h"

#define WDTCR			*((volatile u8 *)0x41)
#define WDTCR_WDTOE		4
#define WDTCR_WDE		3
#define WDTCR_WDP2		2
#define WDTCR_WDP1		1
#define WDTCR_WDP0		0

void WDT_voidSleep(u8 Copy_u8SleepTime);
void WDT_voidEnable(void);
void WDT_voidDisable(void);

void main(void)
{
	PORT_voidInit();
	DIO_u8SetPinValue(DIO_u8PORTB,DIO_u8PIN0,DIO_u8PIN_HIGH);
	_delay_ms(1000);
	DIO_u8SetPinValue(DIO_u8PORTB,DIO_u8PIN0,DIO_u8PIN_LOW);

	WDT_voidEnable();
	WDT_voidSleep(6);
	WDT_voidDisable();
	while(1)
	{

	}
}

void WDT_voidSleep(u8 Copy_u8SleepTime)
{
	/*Clear prescaler bits*/
	WDTCR &= 0b11111000;

	/*Set required prescaler */
	WDTCR |=  Copy_u8SleepTime;
}
void WDT_voidEnable(void)
{
	/*Enable WDT*/
	SET_BIT(WDTCR,WDTCR_WDE);
}
void WDT_voidDisable(void)
{
	/*Set WDE and WDTOE*/
	WDTCR |= 0b00011000;

	/*Clear WDE bit*/
	WDTCR = 0;

}
