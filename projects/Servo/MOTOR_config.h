/***********************************************************************/
/***********************************************************************/
/************************ AUTHER : Hanin Anwar   ***********************/
/************************ LAYER  : HAL           ************************/
/************************ SWC    : PORT          ************************/
/************************ VERSION : 1.00         ************************/
/***********************************************************************/
/***********************************************************************/


#ifndef MOTOR_CONFIG_H_
#define MOTOR_CONFIG_H_

#define MOTOR_DC_PORT				DIO_u8PORTB
#define MOTOR_DC_PIN1				DIO_u8PIN7
#define MOTOR_DC_PIN2				DIO_u8PIN6

#define MOTOR_STEPPER_PORT			DIO_u8PORTB

#define MOTOR_STEPPER_PINK			DIO_u8PIN3
#define MOTOR_STEPPER_BLUE			DIO_u8PIN2
#define MOTOR_STEPPER_YELLOW		DIO_u8PIN4
#define MOTOR_STEPPER_ORANGE		DIO_u8PIN5


/*Stepper Resolution :
 * Options : 1.FULL_STEP
* 			 2.HALF_STEP*/
#define MOTOR_STEPPER_RESOLUTIUON	FULL_STEP


#endif
