#include "STD_TYPES.h"

#include "DIO_interface.h"
#include "PORT_interface.h"
#include "TWI_interface.h"

#include "EEPROM_config.h"
#include "EEPROM_private.h"
#include "EEPROM_interface.h"


void EEPROM_WriteDataByte(u8 Copy_u8Data, u16 Copy_u16Address)
{
	u8 Local_u8SlaveAdd;

	/*Set 7 bits SLA : Fixed_4_bits | slave address"0,1" | 2 MSB from memory location address*/
	Local_u8SlaveAdd = ((FIXED_4_BITS) | (EEPROM_SLAVE_ADD << 2) | ((u8) Copy_u16Address >> 8));

	/*Start communication*/
	TWI_SendStartCondition();

	/*Send Slave Address with write*/
	TWI_SendSlaveAddWithWrite(Local_u8SlaveAdd);

	/*Send the rest of 8 bits memory location address */
	TWI_MasterWriteDataByte((u8)Copy_u16Address);

	/*Write Data on EEPROM */
	TWI_MasterWriteDataByte(Copy_u8Data);

	/*Stop communication*/
	TWI_SendStopCondition();

}

u8 EEPROM_ReadDataByte(u16 Copy_u16Address)
{
	u8 Local_u8SlaveAdd,Local_u8Data;
	/*Set 7 bits SLA : Fixed_4_bits | slave address"0,1" | 2 MSB from memory location address*/
	Local_u8SlaveAdd = ((FIXED_4_BITS) | (EEPROM_SLAVE_ADD << 2) | ((u8) Copy_u16Address >> 8));

	/*Start communication*/
	TWI_SendStartCondition();

	/*Send Slave Address with write*/
	TWI_SendSlaveAddWithWrite(Local_u8SlaveAdd);

	/*Send the rest of 8 bits memory location address */
	TWI_MasterWriteDataByte((u8)Copy_u16Address);

	/*Repeated Start to read from EEPROM*/
	TWI_SendReaptedStart();

	/*Send Slave Address with read*/
	TWI_SendSlaveAddWithRead(Local_u8SlaveAdd);

	/*Read data from EEPROM*/
	TWI_MasterReadDataByte(&Local_u8Data);

	/*Stop communication*/
	TWI_SendStopCondition();

	return Local_u8Data;
}
