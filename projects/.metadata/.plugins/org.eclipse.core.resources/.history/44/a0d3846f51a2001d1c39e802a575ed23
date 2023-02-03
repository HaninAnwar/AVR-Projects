/***********************************************************************/
/***********************************************************************/
/************************ AUTHER : Hanin Anwar  ************************/
/************************ LAYER  : MCAL         ************************/
/************************ SWC    : USART         ************************/
/************************ VERSION : 1.00         ************************/
/***********************************************************************/
/***********************************************************************/

#ifndef  USART_REGISTER_H_
#define  USART_REGISTER_H_


#define UDR					*((volatile u8*)0x2C)	/*Data Register Read(Rx)/Write(Tx)*/


#define UCSRA				*((volatile u8*)0x2B)	/*Control status register A*/

#define UCSRA_RXC			7						/*Receive complete */
#define UCSRA_TXC			6						/*Transmitter complete*/
#define UCSRA_UDRE			5						/*Data Register Empty*/
#define UCSRA_FE			4						/*Frame error*/
#define UCSRA_DOR			3						/*Data OverRun*/
#define UCSRA_PE			2						/*Parity Error*/
#define UCSRA_U2X			1						/*Double the USART Transmission Speed*/
#define UCSRA_MPCM			0						/*Multi-processor Communication Mode*/


#define UCSRB				*((volatile u8*)0x2A)	/*Control status register B*/

#define UCSRB_RXCIE			7						/*RX Complete Interrupt Enable*/
#define UCSRB_TXCIE			6						/*TX Complete Interrupt Enable*/
#define UCSRB_UDRIE			5						/*Data Register Empty Interrupt Enable*/
#define UCSRB_RXEN			4						/*Receiver Enable*/
#define UCSRB_TXEN			3						/*Transmitter Enable*/
#define UCSRB_UCSZ2			2						/*Character size bit1*/
#define UCSRB_RXB8			1						/*Receive Data Bit 8*/
#define UCSRB_TXB8			0						/*Transmit Data Bit 8*/

#define UBRRL				*((volatile u8*)0x29)	/*Baud rate register Low*/


#define UCSRC_UBRRH			*((volatile u8 *)0x40) 	/*Control status register C / Baud rate register High*/

#define UCSRC_UBRRH_URSEL	7						/*Register selection : UCSRRC OR URRBL*/
#define UCSRC_UMSEL			6						/*Mode selection : Synch or Asynch*/
#define UCSRC_UPM1			5						/*Parity mode bit 1*/
#define UCSRC_UPM0			4						/*Parity mode bit 0*/
#define UCSRC_USBS			3						/*Stop bit selection*/
#define UCSRC_UCSZ1			2						/*Character size bit1*/
#define UCSRC_UCSZ0			1						/*Character size bit0*/
#define UCSRC_UCPOL			0						/*Clock polarity bit*/

#define UBRRH_UBRR11		3						/*Baud rate selection bit11*/
#define UBRRH_UBRR10		2						/*Baud rate selection bit10*/
#define UBRRH_UBRR9			1						/*Baud rate selection bit9*/
#define UBRRH_UBRR8			0						/*Baud rate selection bit8*/


#endif
