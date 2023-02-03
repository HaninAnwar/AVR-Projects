/***********************************************************************/
/***********************************************************************/
/************************ AUTHER : Hanin Anwar  ************************/
/************************ LAYER  : MCAL         ************************/
/************************ SWC    : ADC          ************************/
/************************ VERSION : 1.00         ************************/
/***********************************************************************/
/***********************************************************************/

#ifndef  ADC_REGSITER_H_
#define  ADC_REGSITER_H_

#define ADMUX               *((volatile u8 *) 0x27)  //ADC multiplexer selstion register

#define ADCMUX_REFS1        7                       //reference selection bit1
#define ADCMUX_REFS0        6                       //reference selection bit0

#define ADCMUX_ADLAR        5                       //ADC left adjust result

#define ADCMUX_MUX4         4
#define ADCMUX_MUX3         3
#define ADCMUX_MUX2         2
#define ADCMUX_MUX1         1
#define ADCMUX_MUX0         0

#define ADCSRA              *((volatile u8*) 0x26)  //ADC control and status register A

#define ADCSRA_ADEN         7                       //ADC enable
#define ADCSRA_ADSC         6                       //ADC start conversion
#define ADCSRA_ADATE        5                       //ADC auto trigger enable
#define ADCSRA_ADIF         4                       // ADC interrupt flag
#define ADCSRA_ADIE         3                       //ADC interrupt enable
#define ADCSRA_ADPS2        2                       //prescaler bit2
#define ADCSRA_ADPS1        1                       //prescaler bit1
#define ADCSRA_ADPS0        0                       //prescaler bit0

#define ADCH            *((volatile u8 *) 0x25)      //ADC High register
#define ADCL            *((volatile u8 *) 0x24)      //ADC Low register

#define ADC				*((volatile u16 *)0x24)

#define SFIOR			*((volatile u8 *) 0x50)

#define SFIOR_ADTS2		7
#define SFIOR_ADTS1		6
#define SFIOR_ADTS0		5

#endif
