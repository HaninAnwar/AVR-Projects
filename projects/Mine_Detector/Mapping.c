/***********************************************************************/
/***********************************************************************/
/************************ AUTHER : Hanin Anwar  ************************/
/************************ LAYER  : LIB          ************************/
/************************ VERSION : 1.00         ************************/
/***********************************************************************/
/***********************************************************************/


#include "STD_TYPES.h"
#include "MAPPING.h"

s32 Mapping(s32 Copy_s32InputMin,s32 Copy_s32InputMax,s32 Copy_s32OutputMin,s32 Copy_s32OutputMax,s32 Copy_s32InputValue)
{
	s32 Local_s32MappedValue;
	Local_s32MappedValue = (((Copy_s32InputValue - Copy_s32InputMin)*(Copy_s32OutputMax - Copy_s32OutputMin))/(Copy_s32InputMax - Copy_s32InputMin)) + Copy_s32InputMin;

	return Local_s32MappedValue;
}
