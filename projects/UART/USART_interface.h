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

void USRAT_voidInit(void);

void USART_voidSend(u8 Copy_u8Data);

u8 USART_u8Receive(void);

void USART_voidSendString(const char* Copy_pcString);
#endif
