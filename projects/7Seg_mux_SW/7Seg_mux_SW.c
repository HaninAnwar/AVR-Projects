#include <avr/io.h>
#include <util/delay.h>
void main(void)
{
	DDRA = 0Xff;	// 7seg port
	DDRC = 0Xff;	// common cathode for 7seg2
	DDRB = 0x00;	// SW port
	PORTB = 0xff;	// pull up activation
	char inc = 0,dec = 0;

	char num[10] = {
						0b00111111 ,
						0b00000110 ,
						0b01011011 ,
						0b01001111 ,
						0b01100110 ,
						0b01101101 ,
						0b01111101 ,
						0b00000111 ,
						0b01111111 ,
						0b01101111
		};

	while(1)
	{
		PORTC = 0b10000000;	//SEG1 ON
		PORTA = num[9-dec];
		_delay_ms(10);
		PORTA = num[inc] | 1<<7 ;	// SEG1 Off
		PORTC = 0b00000000;//SEG2 ON
		_delay_ms(10);

		if(((PINB & 0x1) == 0)) // SW1 pressed ==> increment
		{
			_delay_ms(100);
			inc++;
			if (inc  == 10)
				inc = 0;



			PORTC = 0b10000000;
			PORTA = num[9-dec];
			_delay_ms(10);
			PORTA = num[inc] | 1<<7 ;
			PORTC = 0b00000000;//SEG2 ON
			_delay_ms(10);
		}


		if(((PINB & 0x2) == 0)) // SW2 pressed ==> decrement
		{
			_delay_ms(100);
			dec++;
			if (dec  == 10)	// overflow
				dec = 0 ;


			PORTC = 0b10000000;
			PORTA = num[9-dec];
			_delay_ms(10);
			PORTA = num[inc] | 1<<7 ;
			PORTC = 0b00000000;//SEG2 ON
			_delay_ms(10);
		}

	}

}
