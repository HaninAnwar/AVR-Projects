#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "SPI_regester.h"
#include "SPI_private.h"
#include "SPI_config.h"
#include "SPI_interface.h"

void SPI_voidMasterInit(void)
{
	/*Master selection*/
	SET_BIT(SPCR,SPCR_MSTR);

//	/*Clock polarity : rising*/
//	SET_BIT(SPCR,SPCR_CPOL);
//
//	/*Clock phase : sample*/
//	CLR_BIT(SPCR,SPCR_CPHA);

	/*Set prescaler : Div_by_16*/
	SET_BIT(SPCR,SPCR_SPR0);
	CLR_BIT(SPCR,SPCR_SPR1);
	CLR_BIT(SPSR,SPSR_SPI2X);


	/*Peripheral enable*/
	SET_BIT(SPCR,SPCR_SPE);
}

void SPI_voidSlaveInit(void)
{
	/*Slave selection*/
	CLR_BIT(SPCR,SPCR_MSTR);
//
//	/*Clock polarity : rising*/
//	SET_BIT(SPCR,SPCR_CPOL);
//
//	/*Clock phase : sample*/
//	CLR_BIT(SPCR,SPCR_CPHA);

	/*Peripheral enable*/
	SET_BIT(SPCR,SPCR_SPE);
}
u8 SPI_Transceive(u8 Copy_u8Data)
{
	/*Start transmission by send data*/
	SPDR = Copy_u8Data;

	/*polling until transceiving is finished*/
	while(GET_BIT(SPSR,SPSR_SPIF) == 0);

	return SPDR;
}
