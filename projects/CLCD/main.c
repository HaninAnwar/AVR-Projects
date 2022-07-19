#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <util/delay.h>

#include "DIO_interface.h"
#include "CLCD_interface.h"

void main(void)
{
	u8 Local_u8Counter;

	/*Initialize LCD Direction */

	DIO_u8SetPortDirection(DIO_u8PORTA,DIO_u8PORT_OUTPUT);
	DIO_u8SetPinDirection(DIO_u8PORTC,DIO_u8PIN0,DIO_u8PIN_OUTPUT);
	DIO_u8SetPinDirection(DIO_u8PORTC,DIO_u8PIN1,DIO_u8PIN_OUTPUT);
	DIO_u8SetPinDirection(DIO_u8PORTC,DIO_u8PIN2,DIO_u8PIN_OUTPUT);

	CLCD_voidInit();




	while(1)
	{

/**************************	Hello *************************/
		u8 Local_pu8uHead[8] =	{
								0b00001110,
								0b00010001,
								0b00010001,
								0b00010001,
								0b00001110,
								0b00000100,
								0b00000100,
								0b00000100,
								};
		u8 Local_pu8uStand[8] =	{
									0b00011111,
									0b00000100,
									0b00000100,
									0b00000100,
									0b00000100,
									0b00001010,
									0b00010001,
									0b00000000,
									};
		/*Clear LCD*/
		CLCD_voidSendCommand(1);
		/*Hello I'm Hamoksha*/
		CLCD_voidSendString("Hello I'm");
		CLCD_voidGoToXY(1,0);
		CLCD_voidSendString("Hamoksha");

		/*Display Hamoksha*/
		CLCD_voidWriteSpcialCharacter(Local_pu8uHead,1,0,15);
		CLCD_voidWriteSpcialCharacter(Local_pu8uStand,2,1,15);

		_delay_ms(2000);

/**************************	PLAY *************************/
		u8 Local_pu8uHand[8] =	{
									0b00000111,
									0b00001100,
									0b00010100,
									0b00000100,
									0b00000100,
									0b00001010,
									0b00010001,
									0b00000000,
									};

		u8 Local_pu8uBallUp[8] =	{
									0b00001110,
									0b00010001,
									0b00010001,
									0b00001110,
									0b00000000,
									0b00000000,
									0b00000000,
									0b00000000
									};

		u8 Local_pu8uBallDN[8] =	{
										0b00000000,
										0b00000000,
										0b00000000,
										0b00001110,
										0b00010001,
										0b00010001,
										0b00001110,
										0b00000000,
									};
		for(Local_u8Counter = 0;Local_u8Counter < 5 ; Local_u8Counter++)
		{
			/*Clear LCD*/
			CLCD_voidSendCommand(1);

			/*I can play football*/
			CLCD_voidSendString("I can play");
			CLCD_voidGoToXY(1,0);
			CLCD_voidSendString("football");

			/*Hamoksha's Head*/
			CLCD_voidWriteSpcialCharacter(Local_pu8uHead,1,0,15);

			/*Play with football UP*/
			CLCD_voidWriteSpcialCharacter(Local_pu8uStand,2,1,15);
			CLCD_voidWriteSpcialCharacter(Local_pu8uBallUp,3,1,14);
			_delay_ms(250);

			/*Play with football Down*/
			CLCD_voidWriteSpcialCharacter(Local_pu8uHand,2,1,14);
			CLCD_voidWriteSpcialCharacter(Local_pu8uBallDN,3,1,14);
			_delay_ms(250);
		}

		_delay_ms(500);
/**************************	RUN	*************************/
		u8 Local_pu8uRun1[8] =	{
									0b00011100,
									0b00000110,
									0b00000101,
									0b00000100,
									0b00000100,
									0b00001100,
									0b00010100,
									0b00000000,
									};

		u8 Local_pu8uRun2[8] =	{
									0b00000111,
									0b00001100,
									0b00010100,
									0b00000100,
									0b00000100,
									0b00000110,
									0b00000101,
									0b00000000,
									};
		Local_u8Counter = 0;

		for(Local_u8Counter = 0; Local_u8Counter < 6 ;Local_u8Counter++)
		{
			CLCD_voidSendCommand(1);
			/*I can run*/
			CLCD_voidSendString("I can run");
			/*Hamoksha's Head*/
			CLCD_voidWriteSpcialCharacter(Local_pu8uHead,1,0,15-Local_u8Counter);

			if (Local_u8Counter %2 == 0)
			{
				CLCD_voidWriteSpcialCharacter(Local_pu8uRun1,2,1,15-Local_u8Counter);

			}
			else
			{
				CLCD_voidWriteSpcialCharacter(Local_pu8uRun2,2,1,15-Local_u8Counter);

			}
			_delay_ms(250);

		}
		for(Local_u8Counter = 0; Local_u8Counter <= 6 ;Local_u8Counter++)
		{
			CLCD_voidSendCommand(1);
			/*I can run*/
			CLCD_voidSendString("I can run");
			/*Hamoksha's Head*/
			CLCD_voidWriteSpcialCharacter(Local_pu8uHead,1,0,15-6+Local_u8Counter);
			if (Local_u8Counter %2 == 0)
			{
				CLCD_voidWriteSpcialCharacter(Local_pu8uRun1,2,1,15-6+Local_u8Counter);

			}
			else
			{
				CLCD_voidWriteSpcialCharacter(Local_pu8uRun2,2,1,15-6+Local_u8Counter);

			}
			_delay_ms(250);

		}
		_delay_ms(500);

/**************************	Dance *************************/
		u8 Local_pu8uHeadDance1[8]= {
									0b00001110,
									0b00010001,
									0b00010001,
									0b00010001,
									0b00001110,
									0b00010100,
									0b00001100,
									0b00000111,
									};


		u8 Local_pu8uHeadDance2[8]= {
									0b00001110,
									0b00010001,
									0b00010001,
									0b00010001,
									0b00001110,
									0b00000101,
									0b00000110,
									0b00011100,
									};
		u8 Local_pu8uDance1[8] = {
									0b00000100,
									0b00000100,
									0b00000100,
									0b00000100,
									0b00000100,
									0b00001010,
									0b00010001,
									0b00000000,
									};
		u8 Local_pu8uDance2[8] = {
									0b00011100,
									0b00000110,
									0b00000101,
									0b00010100,
									0b00001100,
									0b00000100,
									0b00000010,
									0b00000001,
									};

		u8 Local_pu8uDance3[8] = {
									0b00000111,
									0b00001100,
									0b00010100,
									0b00000101,
									0b00000110,
									0b00000100,
									0b00001000,
									0b00010000,
									};
		Local_u8Counter = 0;

		for(Local_u8Counter = 0; Local_u8Counter < 4;Local_u8Counter++)
		{
			CLCD_voidSendCommand(1);
			/*I can run*/
			CLCD_voidSendString("I can dance");

			if (Local_u8Counter %2 == 0)
			{
				/*Hamoksha's Head*/
				CLCD_voidWriteSpcialCharacter(Local_pu8uHeadDance1,1,0,15-Local_u8Counter);
				CLCD_voidWriteSpcialCharacter(Local_pu8uDance1,2,1,15-Local_u8Counter);

			}
			else
			{
				/*Hamoksha's Head*/
				CLCD_voidWriteSpcialCharacter(Local_pu8uHeadDance2,1,0,15-Local_u8Counter);
				CLCD_voidWriteSpcialCharacter(Local_pu8uDance1,2,1,15-Local_u8Counter);

			}
			_delay_ms(750);

		}
		for(Local_u8Counter = 0; Local_u8Counter <=4;Local_u8Counter++)
		{
			CLCD_voidSendCommand(1);
			/*I can run*/
			CLCD_voidSendString("I can dance");

			if (Local_u8Counter %2 == 0)
			{
				/*Hamoksha's Head*/
				CLCD_voidWriteSpcialCharacter(Local_pu8uHead,1,0,15-4+Local_u8Counter);
				CLCD_voidWriteSpcialCharacter(Local_pu8uDance2,2,1,15-4+Local_u8Counter);

			}
			else
			{
				/*Hamoksha's Head*/
				CLCD_voidWriteSpcialCharacter(Local_pu8uHead,1,0,15-4+Local_u8Counter);
				CLCD_voidWriteSpcialCharacter(Local_pu8uDance3,2,1,15-4+Local_u8Counter);

			}
			_delay_ms(750);

		}
		_delay_ms(500);
/**************************	Don't Kill Me **************************/
		u8 Local_pu8uGun1[8] =	{
								0b00011111,
								0b00011111,
								0b00011101,
								0b00011101,
								0b00011111,
								0b00011100,
								0b00011100,
								0b00011100,
								};

		u8 Local_pu8uGun2[8] =	{
								0b00011111,
								0b00011111,
								0b00011111,
								0b00000000,
								0b00000000,
								0b00000000,
								0b00000000,
								0b00000000,
								};

		u8 Local_pu8uBullet[8] =	{
								0b00000100,
								0b00001110,
								0b00000100,
								0b00000000,
								0b00000000,
								0b00000000,
								0b00000000,
								0b00000000,
								};

		u8 Local_pu8uKilledHead[8]={
								0b00001110,
								0b00010001,
								0b00010001,
								0b00010001,
								0b00001110,
								0b00000000,
								0b00000000,
								0b00000000,
								};

		u8 Local_pu8uKilledNeck[8]={
									0b00000000,
									0b00000000,
									0b00000000,
									0b00011111,
									0b00000000,
									0b00000000,
									0b00000000,
									0b00000000,
									};

		u8 Local_pu8uKilledBody[8]={
										0b00010001,
										0b00010001,
										0b00010001,
										0b00011111,
										0b00010001,
										0b00010001,
										0b00010001,
										0b00000000,
										};
		for (Local_u8Counter = 0; Local_u8Counter < 14 ; Local_u8Counter++)
		{
			/*Clear LCD*/
			CLCD_voidSendCommand(1);


			/*Don't kill me*/
			CLCD_voidGoToXY(0,2);
			CLCD_voidSendString("Don't kill me");

			/*Hamoksha's Pattern*/
			CLCD_voidWriteSpcialCharacter(Local_pu8uHead,1,0,15);
			CLCD_voidWriteSpcialCharacter(Local_pu8uStand,2,1,15);

			/*Gun Pattern*/
			CLCD_voidWriteSpcialCharacter(Local_pu8uGun1,3,1,0);
			CLCD_voidWriteSpcialCharacter(Local_pu8uGun2,4,1,1);

			/*Bullet Pattern*/
			CLCD_voidWriteSpcialCharacter(Local_pu8uBullet,5,1,2+Local_u8Counter);

			_delay_ms(500);
		}

		/*Clear LCD*/
		CLCD_voidSendCommand(1);


		/*Hamoksha is dead*/
		CLCD_voidWriteSpcialCharacter(Local_pu8uKilledHead,1,1,15);
		CLCD_voidWriteSpcialCharacter(Local_pu8uKilledNeck,2,1,14);
		CLCD_voidWriteSpcialCharacter(Local_pu8uKilledBody,3,1,13);

		/*Gun pattern*/
		CLCD_voidWriteSpcialCharacter(Local_pu8uGun1,4,1,0);
		CLCD_voidWriteSpcialCharacter(Local_pu8uGun2,5,1,1);


		_delay_ms(2000);


	}

}
