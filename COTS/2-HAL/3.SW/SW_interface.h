/***********************************************************************/
/***********************************************************************/
/************************ AUTHER : Hanin Anwar  ************************/
/************************ LAYER  : HAL          ************************/
/************************ SWC    : DIO          ************************/
/************************ VERSION : 1.00         ************************/
/***********************************************************************/
/***********************************************************************/


#ifndef  SW_INTERFACE_H_
#define  SW_INTERFACE_H_

#define SW_u8PRESSED				1
#define SW_u8NOT_PRESSED    		0

#define SW_u8SELF_LOCK				1
#define SW_u8NOT_SELF_LOCK			0

#define SW_u8PULL_UP				1
#define SW_u8PULL_DN				0

typedef struct
{
	u8 Port;
	u8 Pin;
	u8 SelfLockType;
	u8 PullType;

}SW_T;

u8 SW_u8GetState(SW_T *SW, u8 *Copy_pu8State);

#endif
