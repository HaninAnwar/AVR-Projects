/***********************************************************************/
/***********************************************************************/
/************************ AUTHER : Hanin Anwar  ************************/
/************************ LAYER  : MCAL         ************************/
/************************ SWC    : PORT          ************************/
/************************ VERSION : 1.00         ************************/
/***********************************************************************/
/***********************************************************************/

#ifndef  PORT_CONFIG_H_
#define  PORT_CONFIG_H_

/************************ Set Direction ************************/

/*Choose : 0 for Input 
           1 for Output         */

/*Motors Port*/

#define PORTA_PIN0_DIR                  1	/*User defined LED*/
#define PORTA_PIN1_DIR                  0
#define PORTA_PIN2_DIR                  0
#define PORTA_PIN3_DIR                  0
#define PORTA_PIN4_DIR                  1 	/*Left_Forword*/
#define PORTA_PIN5_DIR                  1	/*Right_Back*/
#define PORTA_PIN6_DIR                  1	/*Left_Back*/
#define PORTA_PIN7_DIR                  1	/*Right_Forward*/

//
#define PORTB_PIN0_DIR                  0
#define PORTB_PIN1_DIR                  0
#define PORTB_PIN2_DIR                  0	/*Metal Detector*/
#define PORTB_PIN3_DIR                  1	/*PWM for motor1*/
#define PORTB_PIN4_DIR                  0
#define PORTB_PIN5_DIR                  0
#define PORTB_PIN6_DIR                  0
#define PORTB_PIN7_DIR                  0

#define PORTC_PIN0_DIR                  0
#define PORTC_PIN1_DIR                  0
#define PORTC_PIN2_DIR                  0
#define PORTC_PIN3_DIR                  0
#define PORTC_PIN4_DIR                  0
#define PORTC_PIN5_DIR                  0
#define PORTC_PIN6_DIR                  0
#define PORTC_PIN7_DIR                  0

#define PORTD_PIN0_DIR                  0	/*Rx Pin*/
#define PORTD_PIN1_DIR                  1	/*Tx Pin*/
#define PORTD_PIN2_DIR                  0
#define PORTD_PIN3_DIR                  0
#define PORTD_PIN4_DIR                  1
#define PORTD_PIN5_DIR                  1	/*Ultrasonic trigger pin*/
#define PORTD_PIN6_DIR                  0 	/*Ultrasonic echo pin*/
#define PORTD_PIN7_DIR                  1	/*PWM for motor2*/

/************************ Set Initial Value ************************/

/*Choose : 0 for Floating if Input , Low if Output
           1 for Pull Up if Input , High if Output       */

#define PORTA_PIN0_INITIAL_VALUE          0
#define PORTA_PIN1_INITIAL_VALUE          0
#define PORTA_PIN2_INITIAL_VALUE          0
#define PORTA_PIN3_INITIAL_VALUE          0
#define PORTA_PIN4_INITIAL_VALUE          0
#define PORTA_PIN5_INITIAL_VALUE          0
#define PORTA_PIN6_INITIAL_VALUE          0
#define PORTA_PIN7_INITIAL_VALUE          0

#define PORTB_PIN0_INITIAL_VALUE          0
#define PORTB_PIN1_INITIAL_VALUE          0
#define PORTB_PIN2_INITIAL_VALUE          0
#define PORTB_PIN3_INITIAL_VALUE          0
#define PORTB_PIN4_INITIAL_VALUE          0
#define PORTB_PIN5_INITIAL_VALUE          0
#define PORTB_PIN6_INITIAL_VALUE          0
#define PORTB_PIN7_INITIAL_VALUE          0

#define PORTC_PIN0_INITIAL_VALUE          0
#define PORTC_PIN1_INITIAL_VALUE          0
#define PORTC_PIN2_INITIAL_VALUE          0
#define PORTC_PIN3_INITIAL_VALUE          0
#define PORTC_PIN4_INITIAL_VALUE          0
#define PORTC_PIN5_INITIAL_VALUE          0
#define PORTC_PIN6_INITIAL_VALUE          0
#define PORTC_PIN7_INITIAL_VALUE          0

#define PORTD_PIN0_INITIAL_VALUE          0
#define PORTD_PIN1_INITIAL_VALUE          0
#define PORTD_PIN2_INITIAL_VALUE          0
#define PORTD_PIN3_INITIAL_VALUE          0
#define PORTD_PIN4_INITIAL_VALUE          0
#define PORTD_PIN5_INITIAL_VALUE          0
#define PORTD_PIN6_INITIAL_VALUE          1
#define PORTD_PIN7_INITIAL_VALUE          0



#endif
