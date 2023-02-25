/***********************************************************************/
/***********************************************************************/
/************************ AUTHER : Hanin Anwar  ************************/
/************************ LAYER  : MCAL         ************************/
/************************ SWC    : TIMER          ************************/
/************************ VERSION : 1.00         ************************/
/***********************************************************************/
/***********************************************************************/

#ifndef  TIMER_REGISTER_H_
#define  TIMER_REGISTER_H_

/***	Timer0 Registers	***/

#define  TCCR0				*((volatile u8 *)0x53) 	/*Timer0 control register*/
#define  TCCR0_WGM00		6					   	/*Waveform generation modes bit0*/
#define  TCCR0_WGM01		3					   	/*Waveform generation modes bit1*/

#define  TCCR0_CS00			0						/*prescaler bit0*/
#define  TCCR0_CS01			1						/*prescaler bit1*/
#define  TCCR0_CS02			2						/*prescaler bit2*/

#define TCCR0_COM00			4						/*Compare Output Mode bit0*/
#define TCCR0_COM01			5						/*Compare Output Mode bit1*/

#define  TIMSK_TOIE0		0						/*Timer Overflow Interrupt Enable*/
#define  TIMSK_OCIE0		1						/*Timer Output Compare Match Interrupt Enable*/

#define  OCR0				*((volatile u8*)0x5C)	/*Output compare match register*/


/***	Timer1 Registers 	***/

#define TCNT1				*((volatile u16 *)0x4C)	/*Timer/Counter Register to store timer value*/

/***	Timer1 Registers Channel A	***/

#define ICR1				*((volatile u16 *)0x46)	/* Input Capture Register*/

#define TCCR1A				*((volatile u8 *)0x4F)	/*Timer1 control register*/

#define TCCR1A_WGM10		0						/*Waveform generation modes bit0*/
#define TCCR1A_WGM11		1						/*Waveform generation modes bit1*/

#define TCCR1A_COMA0		6						/*Compare Output Mode bit0*/
#define TCCR1A_COMA1		7						/*Compare Output Mode bit1*/

#define TIMSK				*((volatile u8*)0x59)	/*Timer Mask*/
#define TIMSK_TOIE1			2						/*Timer Overflow Interrupt Enable*/
#define TIMSK_OCIE1A		4						/*Timer Output Compare A Match Interrupt Enable*/
#define TIMSK_TICIE1		5						/*Time input capture interrupt enable*/

#define OCR1A				*((volatile u16 *)0x4A)	/*Output compare match register*/


/***	Timer1 Registers Channel B	***/

#define TCCR1B				*((volatile u8 *)0x4E)  /*Timer1 control register*/

#define TCCR1A_COMB0		4						/*Compare Output Mode bit0*/
#define TCCR1A_COMB1		5						/*Compare Output Mode bit1*/

#define TCCR1B_CS10			0						/*prescaler bit0*/
#define TCCR1B_CS11			1						/*prescaler bit1*/
#define TCCR1B_CS12			2						/*prescaler bit2*/

#define TCCR1B_WGM12		3						/*Waveform generation modes bit2*/
#define TCCR1B_WGM13		4						/*Waveform generation modes bit3*/

#define TCCR1B_ICES			6						/*Input capture edge select*/

#define TIMSK_OCIE1B		3						/*Timer Output Compare B Match Interrupt Enable*/

#define OCR1B				*((volatile u16 *)0x48)	/*Output compare match register for B */



/*** 	Timer2 Registers 	***/

#define  TCCR2				*((volatile u8 *)0x45) 	/*Timer2 control register*/
#define  TCCR2_WGM20		6					   	/*Waveform generation modes bit0*/
#define  TCCR2_WGM21		3					   	/*Waveform generation modes bit1*/

#define  TCCR2_CS20			0						/*prescaler bit0*/
#define  TCCR2_CS21			1						/*prescaler bit1*/
#define  TCCR2_CS22			2						/*prescaler bit2*/

#define TCCR2_COM20			4						/*Compare Output Mode bit0*/
#define TCCR2_COM21			5						/*Compare Output Mode bit1*/

#define  OCR2				*((volatile u8*)0x43)	/*Output compare match register*/

#define TIMSK_TOIE2		6						/*Timer2 Overflow Interrupt Enable*/
#define TIMSK_OCIE2			7						/*Output compare interrupt enable*/


#endif
