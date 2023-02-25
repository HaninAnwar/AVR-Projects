/***********************************************************************/
/***********************************************************************/
/************************ AUTHER : Hanin Anwar  ************************/
/************************ LAYER  : HAL          ************************/
/************************ SWC    : MOTOR         ************************/
/************************ VERSION: 1.00         ************************/
/***********************************************************************/
/***********************************************************************/


/*Preprocessor file guard*/
#ifndef  MOTOR_INTERFACE_H_
#define  MOTOR_INTERFACE_H_

#define MOTOR_CLK_WISE			1
#define MOTOR_UNTI_CLK_WISE		2

/*PWM Pins :
 * 1. PORTB_PIN3
 * 2. PORTD_PIN4
 * 3. PORTD_PIN5
 * 4. PORTD_PIN7
 * */

#define PWM_PIN_1		1
#define PWM_PIN_2		2
#define PWM_PIN_3		3
#define PWM_PIN_4		4

typedef struct
{
	u8 Port;
	u8 Pin1;
	u8 Pin2;

}DC_Motor;

typedef struct
{
	u8 Port;
	u8 Pink_Pin;
	u8 Blue_Pin;
	u8 Yellow_Pin;
	u8 Orange_Pin;

}Stepper_Motor;

u8 MOTOR_u8DCRotate(DC_Motor *motor,u8 Copy_u8Direction,u8 Copy_u8PWMPin,u8 Copy_u8Speed);

void MOTOR_voidDCStop(DC_Motor *motor);

u8 MOTOR_u8StepperRotate(Stepper_Motor *Stepper,u8 Copy_u8Direction);

u8 MOTOR_u8StepperRotateAngle(Stepper_Motor *Stepper ,u16 Copy_u16Angle,u8 Copy_u8Direction);

void MOTOR_voidStepperStop(Stepper_Motor *Stepper);

#endif
