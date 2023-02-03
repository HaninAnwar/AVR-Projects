/***********************************************************************/
/***********************************************************************/
/************************ AUTHER : Hanin Anwar  ************************/
/************************ LAYER  : MCAL         ************************/
/************************ SWC    : TWI          ************************/
/************************ VERSION : 1.00         ************************/
/***********************************************************************/
/***********************************************************************/


#ifndef  TWI_REGISTER_H_
#define  TWI_REGISTER_H_

#define TWCR			*((volatile u8*)0x56)		/*Control register*/

#define TWCR_TWINT		7							/*Interrupt Flag*/
#define TWCR_TWEA		6							/*Enable Acknowledge Bit*/
#define TWCR_TWSTA		5							/*START Condition Bit*/
#define TWCR_TWSTO		4							/*STOP Condition Bit*/
#define TWCR_TWWC		3							/*Write Collision Flag*/
#define TWCR_TWEN		2							/*TWI Enable Bit*/
#define TWCR_TWIE		0							/*TWI Interrupt Enable*/


#define TWDR			*((volatile u8*)0x23)		/*Data register*/

#define TWAR			*((volatile u8*)0x22)		/*Slave address register*/

#define TWAR_TWGCE		0							/*General Call recognition enable bit*/

#define TWSR			*((volatile u8*)0x21)		/*Status register*/

#define TWSR_TWPS1		1							/*Prescaler bit1*/
#define TWSR_TWPS0		0							/*Prescaler bit0*/

#define TWBR			*((volatile u8*)0x20)		/*Bit rate register*/

#endif
