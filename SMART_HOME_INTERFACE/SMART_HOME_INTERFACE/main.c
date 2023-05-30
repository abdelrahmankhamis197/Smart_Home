/* ---------------------------------------------------------------------------------------------------------- */
/*  Project Name           :	                             							  	                  */
/*  Project Description    :	SMAR_HOME_INTERFACE                            				              */
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
#include "TIMERS.h"
#include "UART.h"
/*_______________________________________________________________________________________*/

/*		                        HAL Layer Inclusion							             */
#include "LCD.h"
#include "KeyPad.h"
#include "SERVO.h"
/*_______________________________________________________________________________________*/

#include "UART_SERVICE.h"
#include "SMARTHOME_INTERFACE.h"

// servo init


u8 x=0;
int main(void)
{
	DIO_Init();
	LCD_Init();
	KEYPAD_Init();
	SERVO_Init();
	UART_Init();
	//LCD_WriteChar(0x65);
    while (1) 
    {
		SMARTHOME_Security_Runnable();
    }
}

