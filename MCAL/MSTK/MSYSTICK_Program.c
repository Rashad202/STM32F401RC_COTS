/*******************************************************************************************************/
/* Author            : GP_FOTA_TEAM                                                                    */
/* Version           : V0.0.0                                                                          */
/* Data              : 15 Dec 2023                                                                     */
/* Description       : MSTK_Program.c --> implementations                                              */
/* Module  Features  :                                                                                 */
/*      01- MSTK_voidInit                                                                              */
/*      02- MSTK_voidStart                                                                             */
/*      03- MSTK_voidINTStatus                                                                         */
/*      04- MSTK_u8ReadFlag                                                                            */
/*      05- MSTK_VidSetCallBack                                                                        */
/*******************************************************************************************************/


/*#####################################################################################################*/
/*#####################################################################################################*/

/*******************************************************************************************************/
/*                                      Standard Types LIB                                             */
/*******************************************************************************************************/

#include "../Libraries/STD_TYPES.h"
#include "../Libraries/BIT_MATH.h"


/*#####################################################################################################*/
/*#####################################################################################################*/

/*******************************************************************************************************/
/*                                      MCAL Components                                                */
/*******************************************************************************************************/

#include "MSYSTICK_private.h"
#include "MSYSTICK_interface.h"
#include "MSYSTICK_config.h"

/*#####################################################################################################*/
/*#####################################################################################################*/

/*******************************************************************************************************/
/*                                      Functions Implementations                                      */
/*******************************************************************************************************/

/*#####################################################################################################*/
/*#####################################################################################################*/

/*******************************************************************************************************/
/*                                      00- SysTick_Handler                                            */
/*-----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Enable Peripheral Clock                                                  */
/* 2- Function Input       -> Copy_uBusName ,   Copy_u8PerNum                                          */
/*   - BusName_t      : The Bus Of The Prepheral ( AHB1 , AHB2 , APB1 , APB2 ) Every One               */
/*                      Detect Which REG To Choice Pripheral From It                                   */ 
/*   - Copy_u8PerName :  The Order Of Prepheral On The Selected Reg                                    */                      
/* 3- Function Return      -> No Thing                                                                 */
/*******************************************************************************************************/



void ( * MSTK_CallBack ) ( void );

void SysTick_Handler(void){

	MSTK_CallBack();

}



/*******************************************************************************************************/
/*                                      01- MSTK_voidInit                                              */
/*-----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Enable Peripheral Clock                                                  */
/* 2- Function Input       -> Copy_uBusName ,   Copy_u8PerNum                                          */
/*   - BusName_t      : The Bus Of The Prepheral ( AHB1 , AHB2 , APB1 , APB2 ) Every One               */
/*                      Detect Which REG To Choice Pripheral From It                                   */ 
/*   - Copy_u8PerName :  The Order Of Prepheral On The Selected Reg                                    */                      
/* 3- Function Return      -> No Thing                                                                 */
/*******************************************************************************************************/


void MSTK_voidInit( void ){

	// Enable Systick Interrupt  -  Clock = AHB / 8 - Stop Systic
	MSTK->CTRL = 0x00000002;
}

/*******************************************************************************************************/
/*                                      02- MSTK_voidStart                                              */
/*-----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Enable Peripheral Clock                                                  */
/* 2- Function Input       -> Copy_uBusName ,   Copy_u8PerNum                                          */
/*   - BusName_t      : The Bus Of The Prepheral ( AHB1 , AHB2 , APB1 , APB2 ) Every One               */
/*                      Detect Which REG To Choice Pripheral From It                                   */ 
/*   - Copy_u8PerName :  The Order Of Prepheral On The Selected Reg                                    */                      
/* 3- Function Return      -> No Thing                                                                 */
/*******************************************************************************************************/


void MSTK_voidStart( u32 Copy_PreloadValue ){

	// AHB = EXT = 8MHZ & CLOCK OF MSTK = AHB / 8 = 8MHZ / 8 = 1MHZ = 1 Micro For Each Count
	//Load Reload Value
	MSTK->LOAD = Copy_PreloadValue - 1;
	//Clear Val Register
	MSTK->VAL  = 0 ;
	//Enable Systick
	SET_BIT( MSTK->CTRL , 0 );

}

/*******************************************************************************************************/
/*                                      03- MSTK_voidINTStatus                                              */
/*-----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Enable Peripheral Clock                                                  */
/* 2- Function Input       -> Copy_uBusName ,   Copy_u8PerNum                                          */
/*   - BusName_t      : The Bus Of The Prepheral ( AHB1 , AHB2 , APB1 , APB2 ) Every One               */
/*                      Detect Which REG To Choice Pripheral From It                                   */ 
/*   - Copy_u8PerName :  The Order Of Prepheral On The Selected Reg                                    */                      
/* 3- Function Return      -> No Thing                                                                 */
/*******************************************************************************************************/


void MSTK_voidINTStatus( u8 Copy_u8Status ){

	MSTK->CTRL &= ~( 1 << 1 );
	MSTK->CTRL |=  ( Copy_u8Status << 1 );

}

/*******************************************************************************************************/
/*                                      04- MSTK_u8ReadFlag                                            */
/*-----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Enable Peripheral Clock                                                  */
/* 2- Function Input       -> Copy_uBusName ,   Copy_u8PerNum                                          */
/*   - BusName_t      : The Bus Of The Prepheral ( AHB1 , AHB2 , APB1 , APB2 ) Every One               */
/*                      Detect Which REG To Choice Pripheral From It                                   */ 
/*   - Copy_u8PerName :  The Order Of Prepheral On The Selected Reg                                    */                      
/* 3- Function Return      -> No Thing                                                                 */
/*******************************************************************************************************/

u8 MSTK_u8ReadFlag( void ){

	return ( GET_BIT( MSTK->CTRL , 16 ) );

}
/*******************************************************************************************************/
/*                                      05- MSTK_voidSetCallBack                                       */
/*-----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Enable Peripheral Clock                                                  */
/* 2- Function Input       -> Copy_uBusName ,   Copy_u8PerNum                                          */
/*   - BusName_t      : The Bus Of The Prepheral ( AHB1 , AHB2 , APB1 , APB2 ) Every One               */
/*                      Detect Which REG To Choice Pripheral From It                                   */ 
/*   - Copy_u8PerName :  The Order Of Prepheral On The Selected Reg                                    */                      
/* 3- Function Return      -> No Thing                                                                 */
/*******************************************************************************************************/


void MSTK_voidSetCallBack( void (*ptr)(void) ){

	MSTK_CallBack = ptr;
}


void MSTK_voidDelayMs(u32 Copy_u32Delay){

	MSTK_voidInit();
	/* Disable INT */
	MSTK_voidINTStatus( MSTK_INT_DIS );
	MSTK_voidStart( Copy_u32Delay * 1000 );
	/* Wiat Flag Polling */
	while( MSTK_u8ReadFlag() == 0 );
}


void _delay_ms( u32 Copy_u32Time ){

	MSTK_voidInit();
	/* Disable INT */
	MSTK_voidINTStatus( MSTK_INT_DIS );
	MSTK_voidStart( Copy_u32Time * 2000 );
	/* Wiat Flag Polling */
	while( MSTK_u8ReadFlag() == 0 );
}


/* Suppose That The Clock System (AHB) = 16MHZ EXT & The Systick Clock Is = AHB/8 */
void _delay_us( u32 Copy_u32Time ){

	MSTK_voidInit();
	/* Disable INT */
	MSTK_voidINTStatus( MSTK_INT_DIS );
	MSTK_voidStart( Copy_u32Time*2);
	/* Wiat Flag Polling */
	while( MSTK_u8ReadFlag() == 0 );
}



