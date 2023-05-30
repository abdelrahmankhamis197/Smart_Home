/* ---------------------------------------------------------------------------------------------------------- */
/*  Project Name           :	                             							  	                  */
/*  Project Description    :	SMAR_HOME_CONTROL                            				              */
/*  Target Controller 	   :	ATMEGA32 Family                                        					  */
/*  File Name              :	main.c                                    							          */
/*  Layer           	   :	                                             							      */
/*  Date                   :  	20,MAY,2023                                    							  */
/*  Version         	   :  	V1.0                                             							  */
/* ---------------------------------------------------------------------------------------------------------- */

/*		                        Library Inclusions								         */
# define F_CPU 8000000
#include<util/delay.h>
/*-------------------------------*/
#include "MEMMAP.h"
#include "STDTYPES.h"
#include "UTILS.h"
/*_______________________________________________________________________________________*/

/*		                        MCAL Layer Inclusion					                 */
#include "DIO_interface.h"
#include "ADC.h"
#include "UART.h"
/*_______________________________________________________________________________________*/

/*		                        HAL Layer Inclusion							             */
#include "LCD.h"
#include "Sensors.h"
/*_______________________________________________________________________________________*/

#include "UART_SERVICE.h" /*		SERVICE FOR COMMUNICATION           */
#include "SMART_HOME.h"   /*		APP INCLUSION                       */   



 
 /******************************************************************************************
 * Function Name	: MAIN								 			          
 * Parameters (in)	: None					                                              
 * Parameters (out)	: None														           
 * Return value		: None													               
 * Description		:                      
 ********************************************************************************************/
int main(void)
{
	/*		                        PERIPHAL INIT						             */
	DIO_Init();
	LCD_Init();
	ADC_Init(VREF_AVCC,ADC_SCALLER_8);
	UART_Init();
	/*_______________________________________________________________________________________*/
	
	sei();   /*		 INTERRUPTS ENABLE                       */
	
	while(1)
	{
		SLAVE_Runnable();
	}

}



