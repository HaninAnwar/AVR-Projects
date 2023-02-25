/***********************************************************************/
/***********************************************************************/
/************************ AUTHER : Hanin Anwar  ************************/
/************************ LAYER  : MCAL         ************************/
/************************ SWC    : USART         ************************/
/************************ VERSION : 1.00         ************************/
/***********************************************************************/
/***********************************************************************/

#ifndef  USART_INTERFACE_H_
#define  USART_INTERFACE_H_


/*Rx interrupt control
 * 1. RX_INT_ENABLE
 * 2. RX_INT_DISABLE
 * */

#define RX_INT_ENABLE	1
#define RX_INT_DISABLE	2


void USRAT_voidInit(void);

void USART_voidSend(u8 Copy_u8Data);

u8 USART_u8Receive(void);

void USART_voidSendString(const char* Copy_pcString);

u8 USART_u8ReceiverInterruptControl(u8 Copy_u8Control);

u8 USART_u8Receive_Int(void);

void USART_voidSetRxCallBackFunc(void (*Copy_pvCallBackFunc)(void));

#endif
