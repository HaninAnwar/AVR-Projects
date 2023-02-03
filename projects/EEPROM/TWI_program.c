#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "TWI_register.h"
#include "TWI_config.h"
#include "TWI_private.h"
#include "TWI_interface.h"

void TWI_voidMasterInit(u8 Copy_u8MasterAdd)
{
	/*Set Clock to : 400 Kbps*/

	/*Set TWPS1 TWPS0 :0*/
	CLR_BIT(TWSR,TWSR_TWPS0);
	CLR_BIT(TWSR,TWSR_TWPS1);

	/*Set TWBR to : 2 */
	TWBR = 2;

	/*Enable TWI*/
	SET_BIT(TWCR,TWCR_TWEN);

	/*Assign master address*/
	if(Copy_u8MasterAdd != 0)
	{
		TWAR = Copy_u8MasterAdd << 1;
	}


}

void TWI_voidSlaveInit(u8 Copy_u8SalveAdd)
{
	/*Initialize Slave address*/
	TWAR = Copy_u8SalveAdd << 1;

	/*Enable TWI*/
	SET_BIT(TWCR,TWCR_TWEN);

}

TWI_ErrStatus TWI_SendStartCondition(void)
{
	TWI_ErrStatus Local_ErrStatus = NoError;

	/*Send start condition on bus*/
	SET_BIT(TWCR,TWCR_TWSTA);

	/*Clear interrupt flag to start previous command*/
	SET_BIT(TWCR,TWCR_TWINT);

	/*Wait until the command is complete : interrupt flag is risen*/
	while(GET_BIT(TWCR,TWCR_TWINT)==0);

	/*Check the status */
	if((TWSR & STATUS_BIT_MASK) != START_ACK)
	{
		Local_ErrStatus = SartConditionErr;
	}

	return Local_ErrStatus;
}
TWI_ErrStatus TWI_SendReaptedStart(void)
{
	TWI_ErrStatus Local_ErrStatus = NoError;

	/*Send start condition on bus*/
	SET_BIT(TWCR,TWCR_TWSTA);

	/*Clear interrupt flag to start previous command*/
	SET_BIT(TWCR,TWCR_TWINT);

	/*Wait until the command is complete : interrupt flag is risen*/
	while(GET_BIT(TWCR,TWCR_TWINT)==0);

	/*Check the status */
	if((TWSR & STATUS_BIT_MASK) != REP_START_ACK)
	{
		Local_ErrStatus = ReaptedStartErr;
	}

	return Local_ErrStatus;
}

TWI_ErrStatus TWI_SendSlaveAddWithWrite(u8 Copy_u8SlaveAdd)
{
	TWI_ErrStatus Local_ErrStatus = NoError;

	/*Clear Start condition bit*/
	CLR_BIT(TWCR,TWCR_TWSTA);

	/*Set Slave address in MSBs in data register*/
	TWDR = Copy_u8SlaveAdd << 1;

	/*Clear LSB in data register to Write request*/
	CLR_BIT(TWCR,0);

	/*Wait until the command is complete : interrupt flag is risen*/
	while(GET_BIT(TWCR,TWCR_TWINT)==0);

	/*Check the status */
	if((TWSR & STATUS_BIT_MASK) != SLAVE_ADD_AND_WR_ACK)
	{
		Local_ErrStatus = SlaveAddWithWriteErr;
	}

	return Local_ErrStatus;
}
TWI_ErrStatus TWI_SendSlaveAddWithRead(u8 Copy_u8SlaveAdd)
{
	TWI_ErrStatus Local_ErrStatus = NoError;

	/*Clear Start condition bit*/
	CLR_BIT(TWCR,TWCR_TWSTA);

	/*Set Slave address in MSBs in data register*/
	TWDR = Copy_u8SlaveAdd << 1;

	/*Set LSB in data register to Read request*/
	SET_BIT(TWCR,0);

	/*Wait until the command is complete : interrupt flag is risen*/
	while(GET_BIT(TWCR,TWCR_TWINT)==0);

	/*Check the status */
	if((TWSR & STATUS_BIT_MASK) != SLAVE_ADD_AND_RD_ACK)
	{
		Local_ErrStatus = SlaveAddWithReadErr;
	}

	return Local_ErrStatus;
}

TWI_ErrStatus TWI_MasterWriteDataByte(u8 Copy_u8DataByte)
{
	TWI_ErrStatus Local_ErrStatus = NoError;

	/*Set data to data register*/
	TWDR = Copy_u8DataByte;

	/*Wait until the command is complete : interrupt flag is risen*/
	while(GET_BIT(TWCR,TWCR_TWINT)==0);

	/*Check the status */
	if((TWSR & STATUS_BIT_MASK) != MSTR_WR_BYTE_ACK)
	{
		Local_ErrStatus = MasterWriteByteErr;
	}

	return Local_ErrStatus;
}

TWI_ErrStatus TWI_MasterReadDataByte(u8 *Copy_pu8DataByte)
{
	TWI_ErrStatus Local_ErrStatus = NoError;

	/*Enable master generating  Ack bit after receiving data*/
	SET_BIT(TWCR,TWCR_TWEA);

	/*Clear flag to enable slave to write on bus*/
	SET_BIT(TWCR,TWCR_TWINT);

	/*Wait until the command is complete : interrupt flag is risen*/
	while(GET_BIT(TWCR,TWCR_TWINT)==0);

	/*Check the status */
	if((TWSR & STATUS_BIT_MASK) != MSTR_RD_BYTE_WITH_ACK)
	{
		Local_ErrStatus = MasterReadByteErr;
	}
	else
	{
		/*Read the received data*/
		*Copy_pu8DataByte = TWDR;
	}

	return Local_ErrStatus;
}
void TWI_SendStopCondition(void)
{
	/*Set stop condition bit*/
	SET_BIT(TWCR,TWCR_TWSTO);

	/*Wait until the command is complete : interrupt flag is risen*/
 	SET_BIT(TWCR,TWCR_TWINT);
}
