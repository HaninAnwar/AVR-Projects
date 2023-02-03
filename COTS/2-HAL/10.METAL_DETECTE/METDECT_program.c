#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "METDECT_config.h"
#include "METDECT_interface.h"
#include "METDECT_private.h"

#include "EXTI_interface.h"

u8 METDECT_MineFlag = 0;

void Metal_Detection(void);

u8 METDECT_u8MetalDetected(void)
{
	EXTI_u8Int0SetCallback(&Metal_Detection);

	return METDECT_MineFlag;
}

void Metal_Detection(void)
{
	static u8 Local_u8Counter = 0;

	/*Toggle for each change */
	TOGGLE_BIT(Local_u8Counter,0);

	if(Local_u8Counter == 1)
	{
		METDECT_MineFlag = 1;
	}
	else
	{
		METDECT_MineFlag = 0;
	}
}
