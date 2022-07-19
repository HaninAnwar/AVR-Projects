#include <avr/io.h>
#include <util/delay.h>
void main(void)

{
	DDRA = 0Xff;
	DDRC = 0Xff;
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

		for (int i = 0; i < 10 ;i++)
		{

			PORTC = 0b10000000;//SEG2 OFF
			PORTA = num[9-i];//SEG1 ON
			_delay_ms(250);
			PORTA = num[i] | 1<<7 ;
			PORTC = 0b00000000;//SEG2 ON
			_delay_ms(250);

		}



	}
}
