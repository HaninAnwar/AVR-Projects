/***********************************************************************/
/***********************************************************************/
/************************ AUTHER : Hanin Anwar  ************************/
/************************ LAYER  : HAL          ************************/
/************************ SWC    : CLCD          ************************/
/************************ VERSION: 1.00         ************************/
/***********************************************************************/
/***********************************************************************/


/*Preprocessor file guard*/
#ifndef  CLCD_INTERFACE_H_
#define  CLCD_INTERFACE_H_


void CLCD_voidInit(void);

void CLCD_voidSendCommand(u8 Copy_u8Command);

void CLCD_voidSendData(u8 Copy_u8Data);

void CLCD_voidSendString(const char* Copy_pcString );

void CLCD_voidGoToXY(u8 Copy_u8XPose ,u8 Copy_u8YPose);

void CLCD_voidWriteSpcialCharacter(u8* Copy_pu8Pattern , u8 Copy_u8PatternNum , u8 Copy_u8XPose ,u8 Copy_u8YPose);

void CLCD_voidWriteNumber(u32 Copy_u32Number,u8 Copy_u8XPose , u8 Copy_u8YPose);

#endif

