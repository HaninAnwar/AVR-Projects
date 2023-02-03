/***********************************************************************/
/***********************************************************************/
/************************ AUTHER : Hanin Anwar  ************************/
/************************ LAYER  : MCAL         ************************/
/************************ SWC    : USART         ************************/
/************************ VERSION : 1.00         ************************/
/***********************************************************************/
/***********************************************************************/

#ifndef  USART_CONFIG_H_
#define  USART_CONFIG_H_

/* USART Mode Select :
 * 1. ASYNCH
 * 2. SYNCH
 * */
#define  USART_MODE		ASYNCH

/*Parity Mode Select :
 * 1.DISABLED
 * 2.EVEN
 * 3.ODD
 * */

#define  PARITY_MODE	DISABLED

/* Stop Bit Select :
 * 1. ONE_BIT
 * 2. TWO_BIT
 * */
#define  STOP_BIT		ONE_BIT


/* Character Size :
 * 1. FIVE_BIT
 * 2. SIX_BIT
 * 3. SEVEN_BIT
 * 4. EIGHT_BIT
 * 5. NINE_BIT
 * */
#define CHAR_SIZE		EIGHT_BIT

/*Clock Polarity (This bit is used in synch mode only):
 * 1. RISING
 * 2. FALLING
 * */
#define CLK_POL			RISING


/*Baud rate select (See Data sheet page 165):
 * NORMAL : 9600
 * */
#define BOUAD_RATE		51


#endif
