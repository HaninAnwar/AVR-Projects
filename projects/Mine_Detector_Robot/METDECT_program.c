#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "METDECT_config.h"
#include "METDECT_interface.h"
#include "METDECT_private.h"

#include "EXTI_interface.h"

static u8 METDECT_MineFlag = METDECT_NO_MINE;

void Metal_Detection(void);

void METDECT_voidInitMetalDetector(void)
{
	EXTI_u8Int2SetCallback(&Metal_Detection);
}

u8 METDECT_u8GetMetalDetector(void)
{
	return METDECT_MineFlag;
}

void Metal_Detection(void)
{
	static u8 Local_u8Counter = 0;

	/*Toggle for each change */
	TOGGLE_BIT(Local_u8Counter,0);

	if(Local_u8Counter == 1)
	{
		METDECT_MineFlag = METDECT_MINE;
	}
	else
	{
		METDECT_MineFlag = METDECT_NO_MINE;
	}
}
