#include "STDTYPES.h"
#include "LCD.h"
#include "KeyPad.h"
#include "TIMERS.h"
#include "EEPROM.h"
#include "SERVO.h"
#include "UART_SERVICE.h"
#include "SMARTHOME_INTERFACE.h"




/*		                        Global variables							             */
u8 GLOBAL_Password;
u8 PIN_CODE=255;
volatile u8 MAX_TRIALS_FLAG=0;
static u8 CORRECT_PASS_FLAG=0;
u8 MODE_CHOICE=0;
u8 MANUAL_MODE_CHOICE=0;
u8 OPERATING_MODE=0;
u8 EXIT_AUTO_FLAG=0;
/*_______________________________________________________________________________________*/



u8 SMARTHOME_Security_Scan(void) // to enter the password either setting or checking
{
	u8 key='n';
	u8 num=0;
	u8 i=0;
	while(key != '=')
	{
		key=KEYPAD_Get_Key();
		if (key != NO_KEY)
		{
			
			if ( (key>='0' && key<='9') )
			{
				i++;
				num=num*10+key-'0';
				
				LCD_WriteChar(key);
				
				_delay_ms(500);
				LCD_SetCursor(1,i-1);
				LCD_WriteChar('*');
				_delay_ms(500);
			}
		}
	}
	
	return num;
}


u8 SMARTHOME_Security_Init(void)
{
	u8 status;
	status=EEPROM_ReadData(EEPROM_STATUS_LOCATION);
	GLOBAL_Password= EEPROM_ReadData(EEPROM_PASSWORD_LOCATION);
	if(status==NOTPRESSED)
	{
		// set password
		return SET;
	}
	else if(status==PRESSED)
	{
		// check password
		return CHECK;
	}
}
void SMARTHOME_SetPassword(void) //setting password for the first time
{
	LCD_Clear();
	LCD_WriteString("SET PASSWORD");
	_delay_ms(1000);
	LCD_SetCursor(1,0);
	u8 entered_pass=SMARTHOME_Security_Scan();
	GLOBAL_Password=entered_pass;
	EEPROM_WriteData(EEPROM_PASSWORD_LOCATION,entered_pass);
	EEPROM_WriteData(EEPROM_STATUS_LOCATION,PRESSED);
}
bool_type SMARTHOME_CheckPassword(void)
{
	LCD_Clear();
	LCD_WriteString("CHK PASSWORD");
	_delay_ms(1000);
	LCD_SetCursor(1,0);
	for(u8 i=0;i<MAX_TRIALS;i++)
{
	 u8 entered_pass=SMARTHOME_Security_Scan();
	if(GLOBAL_Password==entered_pass)
	{
		LCD_Clear();
		LCD_SetCursor(0,0);
		LCD_WriteString("DOOR OPEN");
		_delay_ms(1000);
		LCD_SetCursor(1,0);
		LCD_WriteString("WELCOME HOME");
		_delay_ms(2000);
		SMARTHOME_DoorOpen();
		// uart send security checked
		UART_SendUsingPooling('x');
		return TRUE;
	}
	else
	{
			LCD_SetCursor(0,0);
			LCD_WriteString("WRONG CODE");
			LCD_WriteString("          ");
			MAX_TRIALS_FLAG++;
			LCD_SetCursor(1,12);
			LCD_WriteNumber(MAX_TRIALS_FLAG);
			LCD_WriteString("          ");
	}
}
return FALSE;	
}
void MAX_TRIALS_HNADLER(void)
{
	if(MAX_TRIALS_FLAG==3)
	{
		LCD_Clear();
		LCD_WriteString("enter pin");
		LCD_SetCursor(1,0);
		SMARTHOME_BuzzerOn();
		UART_SendUsingPooling('b');
		u8 pin_code=SMARTHOME_Security_Scan();
		if(pin_code==PIN_CODE)
		{
			LCD_Clear();
			LCD_WriteString("ENTER NEW PASSWORD");
			LCD_SetCursor(1,0);
			u8 new_password=SMARTHOME_Security_Scan();
			EEPROM_WriteData(EEPROM_PASSWORD_LOCATION,new_password);
			SMARTHOME_BuzzerOff();
		}
	}
	
}

void Main_Window(void)
{
	LCD_SetCursor(0,0);
	LCD_WriteString("HOME SWEET HOME");
	_delay_ms(1000);
}
void SMARTHOME_Security_Runnable(void)
{
	static u8 flag=0; //exit MANUAL flag
	if((flag==0) && (EXIT_AUTO_FLAG==0)){
	 Main_Window();
	}
	u8 mission;
	
	mission=SMARTHOME_Security_Init();
	if(mission==SET)
	{
		SMARTHOME_SetPassword();
	}
	else if (mission==CHECK)
	{
		if((flag==0) && (EXIT_AUTO_FLAG==0)){
		CORRECT_PASS_FLAG=SMARTHOME_CheckPassword();
		MAX_TRIALS_HNADLER();
		}

		if(CORRECT_PASS_FLAG==TRUE)
		{
			LCD_Clear();
			LCD_WriteString("1:MANUAL 2:AUTO");
			LCD_SetCursor(1,0);
			MODE_CHOICE=SMARTHOME_Security_Scan();
			if(MODE_CHOICE==1) // manual
			{
				
				UART_SendUsingPooling('m');
				LCD_Clear();
				LCD_WriteString("MANUAL MODE");
				//flag=0;
				_delay_ms(2000);
				while(flag!=1){/******************************/
				LCD_Clear();
				LCD_WriteString("1:TV 2:LIGHT");
				LCD_SetCursor(1,0);
				LCD_WriteString("3:FAN 4:PUMP");
				LCD_WriteString("           ");
				LCD_SetCursor(1,15);
				MANUAL_MODE_CHOICE=SMARTHOME_Security_Scan();
				if(MANUAL_MODE_CHOICE==1) // tv chosen
				{
					LCD_Clear();
					LCD_WriteString("1:ON 2:OFF");
					LCD_SetCursor(1,0);
					OPERATING_MODE=SMARTHOME_Security_Scan();
					if(OPERATING_MODE==1)
					{
						UART_SendUsingPooling('t'); //tv on
					}
					else if(OPERATING_MODE==2)
					{
						UART_SendUsingPooling('s'); //tv off
						
					}
				}
				else if(MANUAL_MODE_CHOICE==2) //light chosen
				{
					LCD_Clear();
					LCD_WriteString("1:ON 2:OFF");
					LCD_SetCursor(1,0);
					OPERATING_MODE=SMARTHOME_Security_Scan();
					if(OPERATING_MODE==1)
					{
						UART_SendUsingPooling('l'); //light on
						
					}
					else if(OPERATING_MODE==2)
					{
						UART_SendUsingPooling('r'); //light off
						
					}
				}
				else if(MANUAL_MODE_CHOICE==3) //fan chosen
				{
					LCD_Clear();
					LCD_WriteString("1:ON 2:OFF");
					LCD_SetCursor(1,0);
					OPERATING_MODE=SMARTHOME_Security_Scan();
					if(OPERATING_MODE==1)
					{
						UART_SendUsingPooling('f'); //fan on
						
					}
					else if(OPERATING_MODE==2)
					{
						UART_SendUsingPooling('g'); //fan off
						
					}
				}
				else if(MANUAL_MODE_CHOICE==4)  //pump chosen
				{
					LCD_Clear();
					LCD_WriteString("1:ON 2:OFF");
					LCD_SetCursor(1,0);
					OPERATING_MODE=SMARTHOME_Security_Scan();
					if(OPERATING_MODE==1)
					{
						UART_SendUsingPooling('p'); //pump on
						
					}
					else if(OPERATING_MODE==2)
					{
						UART_SendUsingPooling('q'); //pump off
						
					}
				}
				else if(MANUAL_MODE_CHOICE == 9)
				{
					flag=1;
				}
				
				}
				
			}
			else if(MODE_CHOICE==2)//auto
			{
				UART_SendUsingPooling('a');
				LCD_Clear();
				LCD_WriteString("AUTO MODE");
				LCD_SetCursor(1,0);
				EXIT_AUTO_FLAG=SMARTHOME_Security_Scan();
				if (EXIT_AUTO_FLAG==9)
				{
					UART_SendUsingPooling('e');
					EXIT_AUTO_FLAG=1;
				}
			}
		}
	}
	
}

void SMARTHOME_BuzzerOn(void)
{
  DIO_WritePin(PINB3,HIGH);
}
void SMARTHOME_BuzzerOff(void)
{
	DIO_WritePin(PINB3,LOW);
}
void SMARTHOME_DoorOpen(void)
{
	SERVO_SetPostiion(180);
}
void SMARTHOME_DoorClose(void)
{
	SERVO_SetPostiion(0);
}