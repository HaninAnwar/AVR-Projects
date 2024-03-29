#include "STD_TYPES.h"
#include <util/delay.h>
#include "MAPPING.h"

#include "DIO_interface.h"
#include "PORT_interface.h"
#include "ADC_interface.h"
#include "GIE_register.h"

#include "CLCD_interface.h"
#include "SSD_interface.h"
#include "KEYPAD_interface.h"
#include "MOTOR_interface.h"

void HamokshaStand(void);

void IndicationFunc(void);

u16 App_u16RadingArr[2];
u8 App_u8Leds,App_u8Temp;

void main(void)
{
	u8 Local_u8PressedKey,Local_u8CurrentDigit,Local_u8Trials,Local_u8RegistrationFlag;
	u8 Local_u8EnteredArr[4] = {0,0,0,0};
	u8 Local_u8ChannelsArr[2] = {CHANNEL_ADC0,CHANNEL_ADC1};

	u16 Local_u16Password,Local_u16EnteredPass,Local_u16ID;


	SSD_T *SSD1;
	SSD1->Port = DIO_u8PORTB;
	SSD1->EnablePort = DIO_u8PORTB;
	SSD1->EnablePin = DIO_u8PIN7;
	SSD1->ComType = SSD_u8COM_CATHODE;

	Chain_t *Chain1;
	Chain1->Channel = Local_u8ChannelsArr;
	Chain1->NotificationFunc = &IndicationFunc;
	Chain1->Result = App_u16RadingArr;
	Chain1->Size = 2;

	/*Initialization*/
	PORT_voidInit();
	CLCD_voidInit();
	ADC_voidInit();
	GIE_voidEnable();

	SSD_u8Enable(SSD1);

	Local_u8CurrentDigit = 0;
	Local_u8Trials = 3;
	Local_u8RegistrationFlag = 0;

	/*Welcome*/
	CLCD_voidSendCommand(1);
	CLCD_voidSendString("Welcome");
	_delay_ms(3000);

	/*User Registration*/
	CLCD_voidSendCommand(1);
	CLCD_voidSendString("Enter ID :");

	/*ID Entering*/
	for(Local_u8CurrentDigit = 0; Local_u8CurrentDigit < 4; Local_u8CurrentDigit++)
	{
		do
		{
			Local_u8PressedKey = KPD_GetPressedKey();
		}
		while(Local_u8PressedKey == 0xff);

		/*Store & Display ID*/
		Local_u8EnteredArr[Local_u8CurrentDigit] = Local_u8PressedKey;
		CLCD_voidWriteNumber(Local_u8PressedKey,1,Local_u8CurrentDigit);

	}
	_delay_ms(250);

	/*Store ID , Password : inverse of ID*/
	Local_u16ID = Local_u8EnteredArr[0]*1000+Local_u8EnteredArr[1]*100+Local_u8EnteredArr[2]*10+Local_u8EnteredArr[3];
	Local_u16Password = Local_u8EnteredArr[0]+Local_u8EnteredArr[1]*10+Local_u8EnteredArr[2]*100+Local_u8EnteredArr[3]*1000;

	/*Password Entering*/
	CLCD_voidSendCommand(1);
	CLCD_voidSendString("Enter Password:");

	/*Only 3 trials are allowed*/
	for(Local_u8Trials = 0; Local_u8Trials < 3; Local_u8Trials++)
	{
		/*Display trials on SSD*/
		SSD_u8SetNumber(3-Local_u8Trials,SSD1);

		for(Local_u8CurrentDigit = 0; Local_u8CurrentDigit < 4; Local_u8CurrentDigit++)
		{
			do
			{
				Local_u8PressedKey = KPD_GetPressedKey();
			}
			while(Local_u8PressedKey == 0xff);

			/*Store & Display password*/
			Local_u8EnteredArr[Local_u8CurrentDigit] = Local_u8PressedKey;
			CLCD_voidWriteNumber(Local_u8PressedKey,1,Local_u8CurrentDigit);

		}
		_delay_ms(250);

		/*Store entered password*/
		Local_u16EnteredPass = Local_u8EnteredArr[0]*1000+Local_u8EnteredArr[1]*100+Local_u8EnteredArr[2]*10+Local_u8EnteredArr[3];

		if(Local_u16Password == Local_u16EnteredPass)
		{
			Local_u8RegistrationFlag = 1;
			break;
		}

		else
		{
			CLCD_voidSendCommand(1);
			CLCD_voidSendString("Wrong, try again");
		}

	}

	SSD_u8Disable(SSD1);

	/*Registration is Done*/
	if(Local_u8RegistrationFlag == 1)
	{
		CLCD_voidSendCommand(1);
		CLCD_voidSendString("Welcome");
		CLCD_voidWriteNumber(Local_u16ID,0,8);
		HamokshaStand();
		_delay_ms(3000);
		CLCD_voidSendCommand(1);
	}

	/*Trials are finished with Wrong password*/
	else
	{
		SSD_u8SetNumber(0,SSD1);
		CLCD_voidSendCommand(1);
		CLCD_voidSendString("Bye Bye");


		while(1)
		{

		}

	}

	while(1)
	{
		CLCD_voidGoToXY(0,0);
		CLCD_voidSendString("Temp :");
		CLCD_voidGoToXY(1,0);
		CLCD_voidSendString("LEDs : ");

		ADC_u8StartChainAsynch(Chain1);

		if(App_u8Temp > 23)
		{
			MOTOR_u8DCRotate(MOTOR_CLK_WISE);
			CLCD_voidGoToXY(0,15);
			CLCD_voidSendString("M");
		}

		else
		{
			MOTOR_voidDCStop();
			CLCD_voidGoToXY(0,15);
			CLCD_voidSendString(" ");
		}
	}
}

void HamokshaStand(void)
{
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
	CLCD_voidWriteSpcialCharacter(Local_pu8uHead,1,0,15);
	CLCD_voidWriteSpcialCharacter(Local_pu8uStand,2,1,15);

}

void IndicationFunc(void)
{
	u8 Local_u8MilliVolt;
	App_u8Leds = Mapping(0,255,1,8,App_u16RadingArr[0]);

	Local_u8MilliVolt = ((u32)App_u16RadingArr[1]*5000UL)/256UL;
	App_u8Temp = Local_u8MilliVolt / 10;


	CLCD_voidGoToXY(0,6);
	CLCD_voidSendString("     ");
	CLCD_voidWriteNumber(App_u8Temp,0,6);
	CLCD_voidWriteNumber(8-App_u8Leds,1,6);
	CLCD_voidGoToXY(0,0);

}
