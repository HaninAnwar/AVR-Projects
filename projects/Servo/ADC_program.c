/***********************************************************************/
/***********************************************************************/
/************************ AUTHER : Hanin Anwar  ************************/
/************************ LAYER  : MCAL         ************************/
/************************ SWC    : ADC          ************************/
/************************ VERSION : 1.00         ************************/
/***********************************************************************/
/***********************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "ADC_register.h"
#include "ADC_config.h"
#include "ADC_private.h"
#include "ADC_interface.h"

static u16 *ADC_p16Reading = NULL;
static void (*ADC_pvCallBackNotificationFunc)(void) = NULL;
static u8 ADC_ISRSource;

static Chain_t ADC_chain;
static u8 ADC_u8ChainIndex = 0;

u8 ADC_u8State = IDLE;

void ADC_voidInit(void)
{

	/*1. check reference voltage*/
#if ADC_REF_VOLT == AREF
	CLR_BIT(ADMUX,ADCMUX_REFS0);
	CLR_BIT(ADMUX,ADCMUX_REFS1);

#elif ADC_REF_VOLT == AVCC
	SET_BIT(ADMUX,ADCMUX_REFS0);
	CLR_BIT(ADMUX,ADCMUX_REFS1);

#elif ADC_REF_VOLT == INTERNAL_VOLT
	SET_BIT(ADMUX,ADCMUX_REFS0);
	SET_BIT(ADMUX,ADCMUX_REFS1);

#else
#error "Wrong ADC_REF_VOLT configuration option"

#endif


	/*2. check ADC adjust*/
#if ADC_RESOLUTION == EIGHT_BITS
	SET_BIT(ADMUX,ADCMUX_ADLAR);

#elif ADC_RESOLUTION == TEN_BITS
	CLR_BIT(ADMUX,ADCMUX_ADLAR);

#else
#error "Wrong ADC_ADJUST configuration option"

#endif

	/*3. Set selected prescaler using bit masking*/
	ADCSRA &= PRESCALING_MASK; //Clear prescaler bits
	ADCSRA |= ADC_PRESCALER;

	/*4. Check auto trigger enable*/
#if ADC_AUTO_TRIGGER_EN == ENABLED
	SET_BIT(ADCSRA,ADCSRA_ADATE);

	/*Set ADC interrupt source*/
	SFIOR &= TRIGGER_SRC_MASK;
	SFIOR |= ADC_TRIGGER_SRC;


#elif ADC_AUTO_TRIGGER_EN == DISABLED
	CLR_BIT(ADCSRA,ADCSRA_ADIE);
	CLR_BIT(ADCSRA,ADCSRA_ADATE);

#else
#error "Wrong ADC_AUTO_TRIGGER_EN configuration option"

#endif

	/*5. Check ADC interrupt enable*/
#if ADC_INT_EN == ENABLED
	SET_BIT(ADCSRA,ADCSRA_ADIE);

#elif ADC_INT_EN == DISABLED
	CLR_BIT(ADCSRA,ADCSRA_ADIE);

#else
#error "Wrong ADC_INT_EN configuration option"

#endif

	/*6. Set selected trigger source*/
	SFIOR &= TRIGGER_SRC_MASK;
	SFIOR |= (ADC_TRIGGER_SRC << 5);

	/*7. Check peripheral enable*/
#if ADC_ENABLE == ENABLED
	SET_BIT(ADCSRA,ADCSRA_ADEN);

#elif ADC_ENABLE == DISABLED
	CLR_BIT(ADCSRA,ADCSRA_ADEN);

#else
#error "Wrong ADC_ENABLE configuration option"

#endif
}

u8 ADC_u8StartConversionSynch(u8 Copy_u8Channel , u16 *Copy_p16Reading)
{
	u8 Local_u8ErrorState = OK;
	u32 Local_u32Counter = 0;

	if(ADC_u8State == IDLE)
	{

		/*ADC is busy for conversion*/
		ADC_u8State = BUSY;

		/*Clear MUX bits in ADMUX register */
		ADMUX &= MUX_MASK;

		/*Set the selected channel into MUX bits*/
		ADMUX |= Copy_u8Channel;

		/*Start Conversion*/
		SET_BIT(ADCSRA,ADCSRA_ADSC);


		/*Polling (busy waiting) until the conversion complete flag is risen OR Counter reaching timeout*/
		while(((GET_BIT(ADCSRA,ADCSRA_ADIF))==0) && (Local_u32Counter != ADC_u32TIME_OUT))
		{
			Local_u32Counter++;
		}

		if(Local_u32Counter == ADC_u32TIME_OUT)
		{
			/*Loop is broken because timeout is reached*/
			Local_u8ErrorState = NOK;
		}

		else
		{
			/*Loop is broken because flag is risen*/

			/*Clear the conversion complete flag*/
			SET_BIT(ADCSRA,ADCSRA_ADIF);

#if ADC_RESOLUTION == TEN_BITS
			*Copy_p16Reading = ADC;

#elif ADC_RESOLUTION == EIGHT_BITS
			*Copy_p16Reading = ADCH;

#else
#error "Wrong ADC_USED_BITS configuration option"

#endif

			/*ADC State is idle after conversion is completed*/
			ADC_u8State = IDLE;
		}
	}
	return Local_u8ErrorState;
}

u8 ADC_u8StartConversionAsynch(u8 Copy_u8Channel , u16 *Copy_p16Reading , void (*Copy_pvNotificationFunc(void)))
{
	u8 Local_u8ErrorState = OK;

	if(ADC_u8State == IDLE)
	{
		if((Copy_p16Reading == NULL) || (Copy_pvNotificationFunc == NULL))
		{
			Local_u8ErrorState = NULL_POINTER;
		}

		else
		{

			/*ADC is busy for conversion*/
			ADC_u8State = BUSY;

			/*Make ISR source is single channel*/
			ADC_ISRSource = SINGLE_CHANNEL;

			/*Initialize Reading variable globally*/
			ADC_p16Reading = Copy_p16Reading;

			/*Initialize callback notification function globally*/
			ADC_pvCallBackNotificationFunc = Copy_pvNotificationFunc;

			/*Clear MUX bits in ADMUX register */
			ADMUX &= MUX_MASK;

			/*Set the selected channel into MUX bits*/
			ADMUX |= Copy_u8Channel;

			/*Start Conversion*/
			SET_BIT(ADCSRA,ADCSRA_ADSC);

			/*ADC interrupt enable*/
			SET_BIT(ADCSRA,ADCSRA_ADIE);


		}
	}

	else
	{
		Local_u8ErrorState = BUSY_FUNC;
	}

	return Local_u8ErrorState;
}

u8 ADC_u8StartChainsynch(Chain_t *Copy_chain)
{

	u8 Local_u8ErrorState = OK;
	u8 Local_u8Counter = 0;

	if (Copy_chain == NULL)
	{
		Local_u8ErrorState = NULL_POINTER;
	}

	else
	{
		/*Set ISR source : Chain channels*/
		ADC_ISRSource = CHAIN_CHANNEL;

		/*Initialize all variables globally*/
		ADC_chain.Channel = Copy_chain->Channel;
		ADC_chain.Result = Copy_chain->Result;
		ADC_chain.Size = Copy_chain->Size;
		ADC_chain.NotificationFunc = Copy_chain->NotificationFunc;

		/*Initialize current conversion index*/
		ADC_u8ChainIndex = 0;

		/*Start Conversion*/
		ADC_u8StartConversionSynch(Copy_chain->Channel[ADC_u8ChainIndex],Copy_chain->Result[ADC_u8ChainIndex]);

	}
}

u8 ADC_u8StartChainAsynch(Chain_t *Copy_chain)
{
	u8 Local_u8ErrorState = OK;


	/*check null pointer*/
	if(Copy_chain == NULL)
	{
		Local_u8ErrorState = NULL_POINTER;
	}
	else
	{
		/*check ADC is busy or not*/
		if(ADC_u8State == IDLE)
		{

			/*ADC is busy for conversion*/
			ADC_u8State = BUSY;

			/*Make ISR source is chain*/
			ADC_ISRSource = CHAIN_CHANNEL;

			/*Initialize all variables globally*/
			ADC_chain.Channel = Copy_chain->Channel;
			ADC_chain.Result = Copy_chain->Result;
			ADC_chain.Size = Copy_chain->Size;
			ADC_chain.NotificationFunc = Copy_chain->NotificationFunc;

			/*Initialize current conversion index*/
			ADC_u8ChainIndex = 0;

			/*Set the required channel*/
			ADMUX &= MUX_MASK;
			ADMUX |= ADC_chain.Channel[ADC_u8ChainIndex];

			/*Start conversion*/
			SET_BIT(ADCSRA,ADCSRA_ADSC);

			/*Enable conversion complete interrupt*/
			SET_BIT(ADCSRA,ADCSRA_ADIE);
		}
		else
		{
			Local_u8ErrorState = BUSY_FUNC;
		}

	}

	return Local_u8ErrorState;
}
void __vector_16 (void) __attribute__((signal));
void __vector_16 (void)
{

	/*Check ISR source*/
	if(ADC_ISRSource == SINGLE_CHANNEL)
	{
		/*Reading ADC result*/
		if(ADC_RESOLUTION == TEN_BITS)
		{
			*ADC_p16Reading = ADC;
		}

		else if(ADC_RESOLUTION == EIGHT_BITS)
		{
			*ADC_p16Reading = ADCH;
		}

		/*ADC State is idle after conversion is completed*/
		ADC_u8State = IDLE;

		/*Call notification function*/
		ADC_pvCallBackNotificationFunc();


		/*Disable ADC interrupt */
		CLR_BIT(ADCSRA,ADCSRA_ADIE);

	}
	/*ISR source is chain*/
	else if (ADC_ISRSource == CHAIN_CHANNEL)
	{
		/*Read the current conversion*/
#if ADC_RESOLUTION == TEN_BITS
		ADC_chain.Result[ADC_u8ChainIndex] = ADC;

#elif ADC_RESOLUTION == EIGHT_BITS
		ADC_chain.Result[ADC_u8ChainIndex] = ADCH;
#endif
		/*Increment chain index*/
		ADC_u8ChainIndex++;

		/*check if chain is finished or not*/
		if(ADC_u8ChainIndex == ADC_chain.Size)
		{
			///*Chain is finished*///

			/*Make ADc state is idle*/
			ADC_u8State = IDLE;

			/*Call notification function*/
			ADC_chain.NotificationFunc();

			/*Disable conversion complete interrupt*/
			CLR_BIT(ADCSRA,ADCSRA_ADIE);

		}

		else
		{
			///*Chain is not finished*///

			/*Set new required Channel*/
			ADMUX &= MUX_MASK;
			ADMUX |= ADC_chain.Channel[ADC_u8ChainIndex];

			/*Start conversion*/
			SET_BIT(ADCSRA,ADCSRA_ADSC);
		}
	}
}
