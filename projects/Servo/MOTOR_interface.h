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

#define MOTOR_CLK_WISE			0
#define MOTOR_UNTI_CLK_WISE		1

#define SERVO_CHANNEL_A			0
#define SERVO_CHANNEL_B			1

u8 MOTOR_u8DCRotate(u8 Copy_u8Direction);

void MOTOR_voidDCStop(void);

u8 MOTOR_u8StepperRotate(u8 Copy_u8Direction);

u8 MOTOR_u8StepperRotateAngle(u16 Copy_u16Angle,u8 Copy_u8Direction);

void MOTOR_voidStepperStop(void);

void MOTOR_voidServoRotate(u8 Copy_u8Channel, u16 Copy_u16Degree);

#endif
