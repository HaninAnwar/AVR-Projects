/***********************************************************************/
/***********************************************************************/
/************************ AUTHER : Hanin Anwar  ************************/
/************************ LAYER  : MCAL         ************************/
/************************ SWC    : TWI          ************************/
/************************ VERSION : 1.00         ************************/
/***********************************************************************/
/***********************************************************************/


#ifndef  TWI_PRIVATE_H_
#define  TWI_PRIVATE_H_


/*Private Macros*/
#define START_ACK                0x08 //start has been sent
#define REP_START_ACK            0x10 //repeated start
#define SLAVE_ADD_AND_WR_ACK     0x18 //Master transmit ( slave address + Write request ) ACK
#define SLAVE_ADD_AND_RD_ACK     0x40 //Master transmit ( slave address + Read request ) ACK
#define MSTR_WR_BYTE_ACK         0x28 //Master transmit data ACK
#define MSTR_RD_BYTE_WITH_ACK    0x50 //Master received data with ACK
#define MSTR_RD_BYTE_WITH_NACK   0x58 //Master received data with not ACK
#define SLAVE_ADD_RCVD_RD_REQ    0xA8 //means that slave address is received with read request
#define SLAVE_ADD_RCVD_WR_REQ    0x60 //means that slave address is received with write request
#define SLAVE_DATA_RECEIVED      0x80 //means that a byte is received
#define SLAVE_BYTE_TRANSMITTED   0xB8 //means that the written byte is transmitted

/*Registers and their bits*/
#define TWI_u8_TWDR_REG			*((volatile u8 *)(0x23))			//  TWI Data Register
#define	TWI_u8_TWDR_TWD0		0									//  TWI Read/Write Request


#define TWI_u8_TWAR_REG			*((volatile u8 *)(0x22))			//  TWI Address Register
#define	TWI_u8_TWAR_TWGCE		0									//  TWI Global Call Enable

#define TWI_u8_TWSR_REG			*((volatile u8 *)(0x21))			//  TWI Status Register
#define TWI_u8_TWSR_TWPS0		0									//  TWI Prescaler bit0
#define TWI_u8_TWSR_TWPS1		1                                   //  TWI Prescaler bit1

#define TWI_u8_TWCR_REG			*((volatile u8 *)(0x56))			//  TWI Control Register
#define	TWI_u8_TWCR_TWIE		0									//  TWI Interrupt Enable
#define	TWI_u8_TWCR_TWEN		2									//  TWI Enable
#define	TWI_u8_TWCR_TWWC		3									//  TWI Write Collision Flag
#define	TWI_u8_TWCR_TWSTO		4									//  TWI Stop Condition
#define	TWI_u8_TWCR_TWSTA		5									//  TWI Start Condition
#define	TWI_u8_TWCR_TWEA		6									//  TWI Enable Acknowledge
#define	TWI_u8_TWCR_TWINT		7									//  TWI Interrupt Flag

#define TWI_u8_TWBR_REG			*((volatile u8 *)(0x20))			//  TWI Bit Rate Register

#define STATUS_BIT_MASK		    0xF8

#endif
