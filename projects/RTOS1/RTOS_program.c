/***********************************************************************/
/***********************************************************************/
/************************ AUTHER : Hanin Anwar  ************************/
/************************ LAYER  : RTOS_Stack         ************************/
/************************ SWC    : RTOS          ************************/
/************************ VERSION : 1.00         ************************/
/***********************************************************************/
/***********************************************************************/

#include "STD_TYPES.h"

#include "TIMER_interface.h"
#include "GIE_interface.h"

#include "RTOS_config.h"
#include "RTOS_interface.h"
#include "RTOS_private.h"

static Task_t SystemTasks[TASK_NUM] = {{NULL}};

void RTOS_voidStart(void)
{
	TIMER_u8SetCallBack(TIMER0_OUTPUT_COM_INT,&voidScheduler);
	GIE_voidEnable();
	TIMER0_u8Init(CTC,DISCONNECT,TIMER_DIV_BY_64);
	TIMER0_voidSetCompMatchVal(125);

}
u8 RTOS_voidCreatTask(u8 Copy_u8Priority, u16 Copy_u8Periodicity, void (*Copy_pvoidTaskFunc)(void), u16 Copy_u16FirstDelay)
{
	u8 Local_u8ErrorSate = OK;

	/*Check there is no previous task has the same priority*/
	if (SystemTasks[Copy_u8Priority].TaskFunc == NULL)
	{
		SystemTasks[Copy_u8Priority].Periodicity = Copy_u8Periodicity;
		SystemTasks[Copy_u8Priority].TaskFunc = Copy_pvoidTaskFunc;
		SystemTasks[Copy_u8Priority].State = TASK_RESUMED;
		SystemTasks[Copy_u8Priority].FirstDelay = Copy_u16FirstDelay;
	}

	else
	{
		/*Priority is reserved by anther task , don't create the task*/
		Local_u8ErrorSate = NOK;

	}

	return Local_u8ErrorSate;
}


static void voidScheduler(void)
{
	u8 Local_u8TaskCounter;

	/*Loop on each to check on their periodicity*/

	for(Local_u8TaskCounter = 0;Local_u8TaskCounter < TASK_NUM ; Local_u8TaskCounter++)
	{
		/*Check if the task is suspended or not*/
		if(SystemTasks[Local_u8TaskCounter].State == TASK_RESUMED)
		{
			/*Check if the system reached the first delay of the task or not*/
			if(SystemTasks[Local_u8TaskCounter].FirstDelay == 0)
			{
				/*Invoke the task function*/
				if(SystemTasks[Local_u8TaskCounter].TaskFunc != NULL)
				{
					SystemTasks[Local_u8TaskCounter].TaskFunc();

					/*Assign the first delay to the periodicity minus 1*/
					SystemTasks[Local_u8TaskCounter].FirstDelay = SystemTasks[Local_u8TaskCounter].Periodicity-1;
				}
			}
			else
			{
				/*Decrement the first delay each iteration */
				SystemTasks[Local_u8TaskCounter].FirstDelay--;
			}
		}
	}
}


void RTOS_voidSuspendTask(u8 Copy_u8Priority)
{
	SystemTasks[Copy_u8Priority].State = TASK_SUSPENDED;
}

void RTOS_voidResumeTask(u8 Copy_u8Priority)
{
	SystemTasks[Copy_u8Priority].State = TASK_RESUMED;
}

void RTOS_voidDeleteTask(u8 Copy_u8Priority)
{
	SystemTasks[Copy_u8Priority].TaskFunc = NULL;
}
