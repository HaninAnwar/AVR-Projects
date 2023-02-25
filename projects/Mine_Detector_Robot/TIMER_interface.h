/***********************************************************************/
/***********************************************************************/
/************************ AUTHER : Hanin Anwar  ************************/
/************************ LAYER  : MCAL         ************************/
/************************ SWC    : TIMER          ************************/
/************************ VERSION : 1.00         ************************/
/***********************************************************************/
/***********************************************************************/

#ifndef  TIMER_INTERFACE_H_
#define  TIMER_INTERFACE_H_

/************ Timer Number ************/

#define TIMER_0						1
#define TIMER_1A					2
#define TIMER_1B					3
#define TIMER_2						4


/************ Timers Interrupt sources ************/

#define TIMER0_OVERFLOW_INT			0
#define TIMER0_OUTPUT_COM_INT		1

#define TIMER1_OVERFLOW_INT			2
#define TIMER1_OUTPUT_COM_A_INT		3
#define TIMER1_OUTPUT_COM_B_INT		4
#define TIMER1_ICU_INT				5

#define TIMER2_OVERFLOW_INT			6
#define TIMER2_OUTPUT_COM_INT		7

/************ ICU Configuration ************/

#define ICU_RISING_EDGE				1
#define ICU_FALLING_EDGE			2

#define ICU_INT_ENABLE				1
#define ICU_INT_DISABLE				2

/************ Waveform Generation Selection ************/

#define NORMAL						0
#define PHASE_CORRECT				1
#define CTC							2
#define FAST_PWM					3

/************ Output Compare Mode ************/

#define DISCONNECT					0
#define TOGGLE						1
#define CLEAR						2
#define SET							3

#define NON_INVERTING_PWM			2
#define INVERTING_PWM				3

/************ Clock Scaler Selection ************/

#define TIMER_DIV_BY_1				1
#define TIMER_DIV_BY_8				2
#define TIMER_DIV_BY_64				3
#define TIMER_DIV_BY_256			4
#define TIMER_DIV_BY_1024			5
#define TIMER_EXT_CLK_FALLING_EDGE	6
#define TIMER_EXT_CLK_RISING_EDGE	7

#define TIMER1_CHANNEL_A			1
#define TIMER1_CHANNEL_B			2

u8 TIMER0_u8Init(u8 Copy_u8WaveMode , u8 Copy_u8CompereMode ,u8 Copy_u8Prescaler);

u8 TIMER1_u8Init(u8 Copy_u8Channel , u8 Copy_u8WaveMode , u8 Copy_u8CompereMode ,u8 Copy_u8Prescaler);

u8 TIMER2_u8Init(u8 Copy_u8WaveMode , u8 Copy_u8CompereMode ,u8 Copy_u8Prescaler);

void TIMER0_voidSetCompMatchVal(u8 Copy_u8Value);


void TIMER1_voidSetICR(u16 Copy_u16Top);

void TIMER1_voidSetChannelACompMatchVal(u16 Copy_u16Value);

void TIMER1_voidSetTimerValue(u16 Copy_u16Value);

u16 TIMER1_u16ReadTimerValue(void);

void TIMER2_voidSetCompMatchVal(u8 Copy_u8Value);

void ICU_voidInit(void);

u8 ICU_u8SetTiggerEdge(u8 Copy_u8Edge);

u8 ICU_u8EnableControl(u8 Copy_u8Enable);

u16 ICU_u16ReadingICU(void);

u8 TIMER_u8SetCallBack(u8 Copy_u8INT_ID,void (*Copy_pvCallBackFunc)(void));


void PWM_voidSetPWM(u8 Copy_u8TimerNum,u16 Copy_u16Duration) ;

#endif
