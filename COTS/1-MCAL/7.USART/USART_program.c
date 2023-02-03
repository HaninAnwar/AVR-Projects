#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "USART_register.h"
#include "USART_config.h"
#include "USART_private.h"
#include "USART_interface.h"


static void (* USART_pvRxCallBackFunc)(void) = NULL;
void USRAT_voidInit(void)
{
	u8 Local_u8UCSRC = 0;

	/*Character size selection : 8 bits
	 *Clock polarity : no clk
	 *Stop bit : 1 bit : 0
	 *Parity Selection : no parity : 00
	 *Mode selection : Asynch : 0 */

	/*Access USCRC*/
	SET_BIT(Local_u8UCSRC,UCSRC_UBRRH_URSEL);

	/*Mode selection*/
#if	USART_MODE == ASYNCH
	CLR_BIT(Local_u8UCSRC,UCSRC_UMSEL);

#elif USART_MODE == SYNCH
	SET_BIT(Local_u8UCSRC,UCSRC_UMSEL);

#else
#error "Undefined USART Mode"
#endif

	/*Parity mode*/
#if PARITY_MODE == DISABLED
	CLR_BIT(Local_u8UCSRC,UCSRC_UPM0);
	CLR_BIT(Local_u8UCSRC,UCSRC_UPM1);

#elif PARITY_MODE == EVEN
	CLR_BIT(Local_u8UCSRC,UCSRC_UPM0);
	SET_BIT(Local_u8UCSRC,UCSRC_UPM1);

#elif PARITY_MODE == ODD
	SET_BIT(Local_u8UCSRC,UCSRC_UPM0);
	SET_BIT(Local_u8UCSRC,UCSRC_UPM1);

#else
#error "Undefined Parity Mode"
#endif

	/*Stop bit*/
#if STOP_BIT == ONE_BIT
	CLR_BIT(Local_u8UCSRC,UCSRC_USBS);

#elif STOP_BIT == TWO_BIT
	SET_BIT(Local_u8UCSRC,UCSRC_USBS);

#else
#error "Undefined Stop Bit"

#endif

	/*Character Size*/
#if CHAR_SIZE == FIVE_BIT
	CLR_BIT(Local_u8UCSRC,UCSRC_UCSZ0);
	CLR_BIT(Local_u8UCSRC,UCSRC_UCSZ1);
	CLR_BIT(UCSRB,UCSRB_UCSZ2);

#elif CHAR_SIZE == SIX_BIT
	SET_BIT(Local_u8UCSRC,UCSRC_UCSZ0);
	CLR_BIT(Local_u8UCSRC,UCSRC_UCSZ1);
	CLR_BIT(UCSRB,UCSRB_UCSZ2);

#elif CHAR_SIZE == SEVEN_BIT
	CLR_BIT(Local_u8UCSRC,UCSRC_UCSZ0);
	SET_BIT(Local_u8UCSRC,UCSRC_UCSZ1);
	CLR_BIT(UCSRB,UCSRB_UCSZ2);

#elif CHAR_SIZE == EIGHT_BIT
	SET_BIT(Local_u8UCSRC,UCSRC_UCSZ0);
	SET_BIT(Local_u8UCSRC,UCSRC_UCSZ1);
	CLR_BIT(UCSRB,UCSRB_UCSZ2);

#elif CHAR_SIZE == NINE_BIT
	SET_BIT(Local_u8UCSRC,UCSRC_UCSZ0);
	SET_BIT(Local_u8UCSRC,UCSRC_UCSZ1);
	SET_BIT(UCSRB,UCSRB_UCSZ2);

#else
#error "Undefined Character Size"

#endif


	/*Clock Polarity*/
#if CLK_POL == RISING
	CLR_BIT(Local_u8UCSRC,UCSRC_UCPOL);

#elif CLK_POL == FALLING
	SET_BIT(Local_u8UCSRC,UCSRC_UCPOL);

#else
#error "Undefined Clock Polarity"
#endif

	/*Set all configuration in UBRRH register*/
	UCSRC_UBRRH = Local_u8UCSRC;

	/*Baud rate setting*/
	UBRRL = BOUAD_RATE;


	/*Enable Tx*/
	SET_BIT(UCSRB,UCSRB_TXEN);

	/*Enable Rx */
	SET_BIT(UCSRB,UCSRB_RXEN);

}

void USART_voidSend(u8 Copy_u8Data)
{
	u8 Local_u8Ready;

	do
	{
		/*Check Tx buffer is ready to transmit*/
		Local_u8Ready = GET_BIT(UCSRA,UCSRA_UDRE);
	}
	while (Local_u8Ready == 0);

	UDR = Copy_u8Data;
}

u8 USART_u8Receive(void)
{
	u8 Local_u8Recieved;
	static u16 Local_u8Count = 0;

	do
	{
		Local_u8Recieved = GET_BIT(UCSRA,UCSRA_RXC);
		Local_u8Count++;
	}
	while(Local_u8Recieved == 0 && Local_u8Count <= USART_TIME_OUT);

	Local_u8Count = 0;
	return UDR;
}

void USART_voidSendString(const char* Copy_pcString)
{
	u8 Local_u8Counter = 0;

	while((Copy_pcString[Local_u8Counter] != '\n') && (Copy_pcString[Local_u8Counter] > '0'))
	{
		USART_voidSend(Copy_pcString[Local_u8Counter]);
		Local_u8Counter++;
	}
}

u8 USART_u8Receive_Int(void)
{
	return UDR;
}

u8 USART_u8ReceiverInterruptControl(u8 Copy_u8Control)
{
	u8 Local_u8StateError = OK;

	if(Copy_u8Control == RX_INT_ENABLE)
	{
		SET_BIT(UCSRB,UCSRB_RXCIE);
	}
	else if (Copy_u8Control == RX_INT_DISABLE)
	{
		CLR_BIT(UCSRB,UCSRB_RXCIE);
	}

	else
	{
		Local_u8StateError = NOK;
	}

	return Local_u8StateError;
}

void USART_voidSetRxCallBackFunc(void (*Copy_pvCallBackFunc)(void))
{
	if (Copy_pvCallBackFunc != NULL)
	{
		USART_pvRxCallBackFunc = Copy_pvCallBackFunc;
	}
}

void __vector_13 (void) __attribute__ ((signal));
void __vector_13 (void)
{
	if (USART_pvRxCallBackFunc != NULL)
	{
		USART_pvRxCallBackFunc();
	}
}
