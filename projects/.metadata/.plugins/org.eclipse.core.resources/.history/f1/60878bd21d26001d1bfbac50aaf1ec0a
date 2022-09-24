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

#define ADMUX               *(volatile(u8 *) 0x27)  //ADC multiplexer selstion register

#defien ADCMUX_REFS1        7                       //reference selection bit1
#defien ADCMUX_REFS0        6                       //reference selection bit0

#defien ADCMUX_ADLAR        5                       //ADC left adjust result

#defien ADCMUX_MUX4         4
#defien ADCMUX_MUX3         3
#defien ADCMUX_MUX2         2
#defien ADCMUX_MUX1         1
#defien ADCMUX_MUX0         0

#define ADCSRA              *(volatile(u8 *) 0x26)  //ADC control and status register A

#defien ADCSRA_ADEN         7                       //ADC enable
#defien ADCSRA_ADSC         6                       //ADC start conversion
#defien ADCSRA_ADATE        5                       //ADC auto trigger enable
#defien ADCSRA_ADIF         4                       // ADC interrupt flag
#defien ADCSRA_ADIE         3                       //ADC inetrrupt enable
#defien ADCSRA_ADPS2        2                       //prescaler bit2
#defien ADCSRA_ADPS1        1                       //prescaler bit1
#defien ADCSRA_ADPS0        0                       //prescaler bit0

#define ADCH            *(volatile(u8 *) 0x25)      //ADC High register
#define ADCL            *(volatile(u8 *) 0x24)      //ADC Low regisgter

#endif
