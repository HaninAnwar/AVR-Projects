/***********************************************************************/
/***********************************************************************/
/************************ AUTHER : Hanin Anwar  ************************/
/************************ LAYER  : MCAL         ************************/
/************************ SWC    : SPI         ************************/
/************************ VERSION : 1.00         ************************/
/***********************************************************************/
/***********************************************************************/

#ifndef  SPI_REGISTER_H_
#define  SPI_REGISTER_H_

#define SPDR			*((volatile u8 *)0x2F)		/*SPI data register*/

#define SPSR			*((volatile u8 *)0x2E)		/*SPI status register*/

#define SPSR_SPIF		7							/*interrupt flag*/
#define SPSR_WCOL		6							/*Write  collision flag*/
#define SPSR_SPI2X		0							/*Clock prescaler selection bit2*/


#define SPCR			*((volatile u8 *)0x2D)		/*SPI control register*/

#define SPCR_SPIE		7							/*Interrupt enable*/
#define SPCR_SPE		6							/*SPI enable*/
#define SPCR_DORD		5							/*Data order*/
#define SPCR_MSTR		4							/*Master/Salve selection*/
#define SPCR_CPOL		3							/*Clock polarity*/
#define SPCR_CPHA		2							/*Clock phase*/
#define SPCR_SPR1		1							/*Clock prescaler selection bit1*/
#define SPCR_SPR0		0							/*Clock prescaler selection bit0*/

#endif
