#include "STD_TYPES.h"
#include <util/delay.h>

#include "DIO_interface.h"
#include "TIMER_interface.h"

#include "MOTOR_config.h"
#include "MOTOR_interface.h"
#include "MOTOR_private.h"


u8 MOTOR_u8DCRotate(DC_Motor *motor,u8 Copy_u8Direction,u8 Copy_u8PWMPin,u8 Copy_u8Speed)
{
	u8 Local_u8ErrorState = OK;

	if (Copy_u8Direction == MOTOR_CLK_WISE)
	{
		DIO_u8SetPinValue(motor->Port,motor->Pin2,DIO_u8PIN_LOW);
		DIO_u8SetPinValue(motor->Port,motor->Pin1,DIO_u8PIN_HIGH);

	}

	else if(Copy_u8Direction == MOTOR_UNTI_CLK_WISE)
	{
		DIO_u8SetPinValue(motor->Port,motor->Pin1,DIO_u8PIN_LOW);
		DIO_u8SetPinValue(motor->Port,motor->Pin2,DIO_u8PIN_HIGH);
	}

	else
	{
		Local_u8ErrorState = NOK;
	}

	switch(Copy_u8PWMPin)
	{
	case PWM_PIN_1 : PWM_voidSetPWM(TIMER_0,Copy_u8Speed);break;
	case PWM_PIN_2 : PWM_voidSetPWM(TIMER_1A,Copy_u8Speed);break;
	case PWM_PIN_3 : PWM_voidSetPWM(TIMER_1B,Copy_u8Speed);break;
	case PWM_PIN_4 : PWM_voidSetPWM(TIMER_2,Copy_u8Speed);break;
	default : Local_u8ErrorState = NOK;
	}
	return Local_u8ErrorState;
}

void MOTOR_voidDCStop(DC_Motor *motor)
{
	DIO_u8SetPinValue(motor->Port,motor->Pin1,DIO_u8PIN_LOW);
	DIO_u8SetPinValue(motor->Port,motor->Pin2,DIO_u8PIN_LOW);
}

u8 MOTOR_u8StepperRotate(Stepper_Motor *Stepper,u8 Copy_u8Direction)
{
	u8 Local_u8ErrorState = OK;

	if(Copy_u8Direction == MOTOR_CLK_WISE)
	{
		DIO_u8SetPinValue(Stepper->Port,Stepper->Pink_Pin,DIO_u8PIN_LOW);
		DIO_u8SetPinValue(Stepper->Port,Stepper->Blue_Pin,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(Stepper->Port,Stepper->Yellow_Pin,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(Stepper->Port,Stepper->Orange_Pin,DIO_u8PIN_HIGH);
		_delay_ms(2);

		DIO_u8SetPinValue(Stepper->Port,Stepper->Blue_Pin,DIO_u8PIN_LOW);
		DIO_u8SetPinValue(Stepper->Port,Stepper->Pink_Pin,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(Stepper->Port,Stepper->Yellow_Pin,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(Stepper->Port,Stepper->Orange_Pin,DIO_u8PIN_HIGH);
		_delay_ms(2);

		DIO_u8SetPinValue(Stepper->Port,Stepper->Orange_Pin,DIO_u8PIN_LOW);
		DIO_u8SetPinValue(Stepper->Port,Stepper->Blue_Pin,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(Stepper->Port,Stepper->Pink_Pin,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(Stepper->Port,Stepper->Yellow_Pin,DIO_u8PIN_HIGH);
		_delay_ms(2);

		DIO_u8SetPinValue(Stepper->Port,Stepper->Yellow_Pin,DIO_u8PIN_LOW);
		DIO_u8SetPinValue(Stepper->Port,Stepper->Blue_Pin,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(Stepper->Port,Stepper->Pink_Pin,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(Stepper->Port,Stepper->Orange_Pin,DIO_u8PIN_HIGH);
		_delay_ms(2);
	}
	else if (Copy_u8Direction == MOTOR_UNTI_CLK_WISE)
	{

		DIO_u8SetPinValue(Stepper->Port,Stepper->Blue_Pin,DIO_u8PIN_LOW);
		DIO_u8SetPinValue(Stepper->Port,Stepper->Pink_Pin,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(Stepper->Port,Stepper->Yellow_Pin,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(Stepper->Port,Stepper->Orange_Pin,DIO_u8PIN_HIGH);
		_delay_ms(2);

		DIO_u8SetPinValue(Stepper->Port,Stepper->Pink_Pin,DIO_u8PIN_LOW);
		DIO_u8SetPinValue(Stepper->Port,Stepper->Blue_Pin,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(Stepper->Port,Stepper->Yellow_Pin,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(Stepper->Port,Stepper->Orange_Pin,DIO_u8PIN_HIGH);
		_delay_ms(2);

		DIO_u8SetPinValue(Stepper->Port,Stepper->Yellow_Pin,DIO_u8PIN_LOW);
		DIO_u8SetPinValue(Stepper->Port,Stepper->Blue_Pin,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(Stepper->Port,Stepper->Pink_Pin,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(Stepper->Port,Stepper->Orange_Pin,DIO_u8PIN_HIGH);
		_delay_ms(2);

		DIO_u8SetPinValue(Stepper->Port,Stepper->Orange_Pin,DIO_u8PIN_LOW);
		DIO_u8SetPinValue(Stepper->Port,Stepper->Blue_Pin,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(Stepper->Port,Stepper->Pink_Pin,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(Stepper->Port,Stepper->Yellow_Pin,DIO_u8PIN_HIGH);
		_delay_ms(2);
	}

	else
	{
		Local_u8ErrorState = NOK;
	}
	return Local_u8ErrorState;
}

u8 MOTOR_u8StepperRotateAngle(Stepper_Motor *Stepper ,u16 Copy_u16Angle,u8 Copy_u8Direction)
{
	u8 Local_u8ErrorState = OK;
	u16 Local_u16Counter,Local_u16Revolution;


	Local_u16Revolution = Copy_u16Angle / (MOTOR_STEPPER_RESOLUTIUON*4);

	for(Local_u16Counter = 0; Local_u16Counter < Local_u16Revolution ;Local_u16Counter++)
	{
		MOTOR_u8StepperRotate(Stepper,Copy_u8Direction);
	}

	return Local_u8ErrorState;

}
void MOTOR_voidStepperStop(Stepper_Motor *Stepper)
{
	DIO_u8SetPinValue(Stepper->Port,Stepper->Blue_Pin,DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(Stepper->Port,Stepper->Pink_Pin,DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(Stepper->Port,Stepper->Yellow_Pin,DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(Stepper->Port,Stepper->Orange_Pin,DIO_u8PIN_HIGH);

}
