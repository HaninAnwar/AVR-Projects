/***********************************************************************/
/***********************************************************************/
/************************ AUTHER : Hanin Anwar  ************************/
/************************ LAYER  : MCAL         ************************/
/************************ SWC    : EXTI          ************************/
/************************ VERSION : 1.00         ************************/
/***********************************************************************/
/***********************************************************************/

#ifndef  EXTI_INTERFACE_H_
#define  EXTI_INTERFACE_H_

#define LOW_LEVEL           1
#define ON_CHANGE           2
#define FALLING_EDGE        3
#define RISING_EDGE         4

#define ENABLED				1
#define DISABLED			2

#define EXTI_INT0		    1
#define EXTI_INT1	 	    2
#define EXTI_INT2    		3

void EXTI_voidInt0Init(void); 

void EXTI_voidInt1Init(void); 

void EXTI_voidInt2Init(void); 


/*Description : A function to set sense control of any external interrupt using postbuild configuration
 * Input :
 * 1. Copy_IntNum , options :		1. EXTI_INT0
 * 									2. EXTI_INT1
 * 									3. EXTI_INT2
 *
 * 2. Copy_u8Sense , options : 		1. LOW_LEVEL(INT0 & INT1 only)
 *                                  2. ON_CHANGE(INT0 & INT1 only)
 *                                  3. FALLING_EDG
 *                                  4. RISING_EDGE
 * Output : Error status type of u8
 * */
u8 EXTI_u8IntSetSenseControl(u8 Copy_IntNum,u8 Copy_u8Sense);

/*Description : A function to enable/disable any external interrupt using postbuild configuration
 * Input :
 * 1. Copy_IntNum , options :		1. EXTI_INT0
 * 									2. EXTI_INT1
 * 									3. EXTI_INT2
 *
 * 2. Copy_u8Enable , options : 	1. ENABLED
 *                                  2. DISABLED

 * Output : Error status type of u8
 * */
u8 EXTI_u8IntEnableControl(u8 Copy_IntNum , u8 Copy_u8Enable);


/*Description : functions to get ISR function address from user
 * and send it to EXTI driver to execute ISR
 *
 * Input : Pointer to user defined ISR function
 *
 * Output :  Error status type of u8
 * */
u8 EXTI_u8Int0SetCallback(void (* Copy_pvInt0Func) (void));

u8 EXTI_u8Int1SetCallback(void (* Copy_pvInt1Func) (void));

u8 EXTI_u8Int2SetCallback(void (* Copy_pvInt2Func) (void));
#endif
