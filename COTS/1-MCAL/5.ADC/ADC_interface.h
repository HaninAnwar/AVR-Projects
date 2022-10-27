/***********************************************************************/
/***********************************************************************/
/************************ AUTHER : Hanin Anwar  ************************/
/************************ LAYER  : MCAL         ************************/
/************************ SWC    : ADC          ************************/
/************************ VERSION : 1.00         ************************/
/***********************************************************************/
/***********************************************************************/

#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

#define AREF						1
#define AVCC			            2
#define INTERNAL_VOLT	            3


#define ENABLED			            1
#define DISABLED		            2

#define EIGHT_BITS		            1
#define TEN_BITS		            2

#define DIV_BY_2   		            1
#define DIV_BY_4     	            2
#define DIV_BY_8     	            3
#define DIV_BY_16     	            4
#define DIV_BY_32     	            5
#define DIV_BY_64     	            6
#define DIV_BY_128     	            7

#define PRESCALING_MASK	 	        0b11111000

#define FREE_RUN		 	        0
#define ANALOG_COMP		 	        1
#define EXTI			 	        2
#define TIMER0_COMP		 	        3
#define TIMER0_OVERFLOW	 	        4
#define TIMER1_COMP		 	        5
#define TIMER1_OVERFLOW	 	        6
#define TIMER1_EVENT_CAPT	        7

#define TRIGGER_SRC_MASK 	        0b00011111

#define CHANNEL_ADC0				0b00000
#define CHANNEL_ADC1				0b00001
#define CHANNEL_ADC2				0b00010
#define CHANNEL_ADC3				0b00011
#define CHANNEL_ADC4				0b00100
#define CHANNEL_ADC5				0b00101
#define CHANNEL_ADC6				0b00110
#define CHANNEL_ADC7				0b00111

#define CHANNEL_ADC0_ADC0_X10		0b01000
#define CHANNEL_ADC1_ADC0_X10		0b01001
#define CHANNEL_ADC0_ADC0_X200		0b01010
#define CHANNEL_ADC1_ADC0_X200		0b01011
#define CHANNEL_ADC2_ADC2_X10		0b01100
#define CHANNEL_ADC3_ADC2_X10       0b01101
#define CHANNEL_ADC2_ADC2_X200      0b01110
#define CHANNEL_ADC3_ADC2_X200      0b01111
#define CHANNEL_ADC0_ADC1_X1		0b10000
#define CHANNEL_ADC1_ADC1_X1        0b10001
#define CHANNEL_ADC2_ADC1_X1        0b10010
#define CHANNEL_ADC3_ADC1_X1        0b10011
#define CHANNEL_ADC4_ADC1_X1        0b10100
#define CHANNEL_ADC5_ADC1_X1        0b10101
#define CHANNEL_ADC6_ADC1_X1        0b10110
#define CHANNEL_ADC7_ADC1_X1        0b10111
#define CHANNEL_ADC0_ADC2_X1        0b11000
#define CHANNEL_ADC1_ADC2_X1        0b11001
#define CHANNEL_ADC2_ADC2_X1        0b11010
#define CHANNEL_ADC3_ADC2_X1        0b11011
#define CHANNEL_ADC4_ADC2_X1        0b11100

#define MUX_MASK					0b11100000

typedef struct
{
	u8   *Channel;
	u16  *Result;
	u8   Size;
	void (*NotificationFunc)(void);
}Chain_t;

void ADC_voidInit(void);

u8 ADC_u8StartConversionSynch(u8 Copy_u8Channel , u16 *Copy_p16Reading);

u8 ADC_u8StartConversionAsynch(u8 Copy_u8Channel , u16 *Copy_p16Reading , void (*Copy_pvNotificationFunc(void)));

u8 ADC_u8StartChainAsynch(Chain_t *Copy_chain);

u8 ADC_u8StartChainsynch(Chain_t *Copy_chain);

#endif
