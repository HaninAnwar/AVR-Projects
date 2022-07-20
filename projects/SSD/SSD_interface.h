/********************* *************************************************/
/***********************************************************************/
/************************ AUTHER : Hanin Anwar  ************************/
/************************ LAYER  : HAL          ************************/
/************************ SWC    : SSD          ************************/
/************************ VERSIO : 1.00         ************************/
/***********************************************************************/
/***********************************************************************/


#ifndef  SSD_INTERFACE_H_
#define  SSD_INTERFACE_H_


#define SSD_u8COM_ANODE		1
#define SSD_u8COM_CATHODE	0

#define SSD_u8NUM0			0
#define SSD_u8NUM1			1
#define SSD_u8NUM2			2
#define SSD_u8NUM3			3
#define SSD_u8NUM4			4
#define SSD_u8NUM5			5
#define SSD_u8NUM6			6
#define SSD_u8NUM7			7
#define SSD_u8NUM8			8
#define SSD_u8NUM9			9

typedef struct
{
	u8 Port;
	u8 EnablePort;
	u8 EnablePin;
	u8 ComType;

}SSD_T;


u8 SSD_u8SetNumber(u8 Copy_u8Number , SSD_T *SSD);
u8 SSD_u8Enable(SSD_T *SSD);
u8 SSD_u8Disable(SSD_T *SSD);

#endif
