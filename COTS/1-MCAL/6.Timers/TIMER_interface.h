/***********************************************************************/
/***********************************************************************/
/************************ AUTHER : Hanin Anwar  ************************/
/************************ LAYER  : MCAL         ************************/
/************************ SWC    : TIMER          ************************/
/************************ VERSION : 1.00         ************************/
/***********************************************************************/
/***********************************************************************/

#ifndef  TIMER_INTERFACE_H_
#define  TIMER_INTERFACE_H_


void TIMER0_voidInit(void);

void TIMER0_voidSetCompMatchVal(u8 Copy_u8Value);

u8 TIMER0_u8SetCallBack(void (*Copy_pvCallBackFunc)(void));


void TIMER1_voidInit(void);

u8 TIMER1_u8SetICR(u16 Copy_u16Top);

u8 TIMER1_u8SetChannelACompMatchVal(u16 Copy_u16Value);

#endif
