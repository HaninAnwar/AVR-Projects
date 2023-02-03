/***********************************************************************/
/***********************************************************************/
/************************ AUTHER : Hanin Anwar  ************************/
/************************ LAYER  : MCAL         ************************/
/************************ SWC    : TWI          ************************/
/************************ VERSION : 1.00         ************************/
/***********************************************************************/
/***********************************************************************/


#ifndef  TWI_INTERFACE_H_
#define  TWI_INTERFACE_H_

typedef enum
{
	NoError,
	SartConditionErr,
	ReaptedStartErr,
	SlaveAddWithWriteErr,
	SlaveAddWithReadErr,
	MasterWriteByteErr,
	MasterReadByteErr,
}TWI_ErrStatus;

/*Function : Master initialization
 *Input : Master Address
 *Pass 0 if the master don't have address
 */
void TWI_voidMasterInit(u8 Copy_u8MasterAdd);

void TWI_voidSlaveInit(u8 Copy_u8SalveAdd);

TWI_ErrStatus TWI_SendStartCondition(void);

TWI_ErrStatus TWI_SendReaptedStart(void);

TWI_ErrStatus TWI_SendSlaveAddWithWrite(u8 Copy_u8SlaveAdd);

TWI_ErrStatus TWI_SendSlaveAddWithRead(u8 Copy_u8SlaveAdd);

TWI_ErrStatus TWI_MasterWriteDataByte(u8 Copy_u8DataByte);

TWI_ErrStatus TWI_MasterReadDataByte(u8 *Copy_pu8DataByte);

void TWI_SendStopCondition(void);

#endif
