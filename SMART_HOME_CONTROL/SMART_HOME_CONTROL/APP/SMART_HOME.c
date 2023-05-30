
#define F_CPU 8000000
#include<util/delay.h>
#include "MEMMAP.h"
#include "STDTYPES.h"
#include "UTILS.h"
#include "ADC.h"
#include "Sensors.h"
#include "UART.h"
#include "UART_SERVICE.h"
#include "SMART_HOME.h"


#define MANUAL 1
#define AUTO   2
#define EDIT   3
#define CLEAR  'C'

/*_________________  GLOBAL VARIABLES  ____________*/
volatile static u8 TV_FLAG,LIGHT_FLAG,FAN_FLAG,PUMP_FLAG;  //0 OFF  1 ON

volatile u8 EXIT_AUTO_FLAG=0;
volatile u8 rec_data;  // TO TAKE THE MSGs FROM UART

/*__________________________________________________*/
	
task_t tasks[NO_TASKS]={
	
	{'x',PASSED_Security},
	{'b',FAILED_Security},
	{'m',MANUAL_Mode},
	{'a',AUTO_Mode},
	{'t',TV_ON},
	{'s',TV_OFF},
	{'l',LIGHT_ON},
	{'r',LIGHT_OFF},
	{'f',FAN_ON},
	{'g',FAN_OFF},
	{'p',PUMP_ON},
	{'e',EXIT_AUTO},
	{'q',PUMP_OFF}
	
};


void EXIT_AUTO(void)
{
	LCD_Clear();
	LCD_SetCursor(1,0);
	LCD_WriteString("EXIT");
	_delay_ms(1000);
	EXIT_AUTO_FLAG=0;
	TV_FLAG=0;
	LIGHT_FLAG=0;
	FAN_FLAG=0;
	PUMP_FLAG=0;
	FAN_OFF();
	TV_OFF();
	PUMP_OFF();
	LIGHT_OFF();
}

void PASSED_Security(void)
{
	LCD_Clear();
	LCD_WriteString("Welcome Home");
	_delay_ms(2000);
}
void FAILED_Security(void)
{
	LCD_Clear();
	LCD_WriteString("BLOCKED");
}
void f1(void)
{
	EXIT_AUTO_FLAG=1;
	UART_RX_InterruptDisable();
}
void AUTO_Mode(void)
{
	u16 temp,light,smoke;
	LCD_Clear();
	LCD_WriteString("AUTO");
	_delay_ms(2000);
	LCD_Clear();
	UART_RX_InterruptEnable();
	UART_RX_SetCallBack(f1);
	while(EXIT_AUTO_FLAG==0)
	{
		light=LDR_Read();
		temp=TEMP_Read();
		smoke=PRESSURE_Read();
		if(light>=800)
		{
			LIGHT_OFF();
		}
		else if(light<=512)
		{
			LIGHT_ON();
		}
		if(temp>=300)
		{
			FAN_ON();
		}
		else if(temp<=250)
		{
			FAN_OFF();
		}
		if(smoke>=650)
		{
			PUMP_ON();
		}
		else if(smoke<=550)
		{
			PUMP_OFF();
		}
		tasks_monitor();

	}
	
	 	
		 
}
void MANUAL_Mode(void)
{
	LCD_Clear();
	LCD_WriteString("MANUAL");
	_delay_ms(2000);
	LCD_Clear();
}

void TV_ON(void)
{
	SET_BIT(PORTC,TV_PIN);
	TV_FLAG=1;
}
void TV_OFF(void)
{
	CLR_BIT(PORTC,TV_PIN);
	TV_FLAG=0;
}
void LIGHT_ON(void)
{
	SET_BIT(PORTC,LIGHT_PIN);
	LIGHT_FLAG=1;
}
void LIGHT_OFF(void)
{
	CLR_BIT(PORTC,LIGHT_PIN);
	LIGHT_FLAG=0;
}

void FAN_ON(void)
{
	SET_BIT(PORTC,FAN_PIN);
	FAN_FLAG=1;
}
void FAN_OFF(void)
{
	CLR_BIT(PORTC,FAN_PIN);
	FAN_FLAG=0;
}

void PUMP_ON(void)
{
	SET_BIT(PORTC,PUMP_PIN);
	PUMP_FLAG=1;
}
void PUMP_OFF(void)
{
	CLR_BIT(PORTC,PUMP_PIN);
	PUMP_FLAG=0;
}



void task_search(u8 task_name)
{
	u8 i;
	for(i=0;i<NO_TASKS;i++)
	{
		if( UART_Char_Compare(tasks[i].task_name,task_name) == TRUE)
		{
			tasks[i].pfnc();
		}
	}
	
}
void tasks_monitor(void)
{
	//LCD_Clear();
	if(TV_FLAG==0)
	{
		LCD_SetCursor(0,0);
		LCD_WriteString("TV OFF ");
	}
	else if(TV_FLAG==1)
	{
		LCD_SetCursor(0,0);
		LCD_WriteString("TV ON ");
	}
	if(LIGHT_FLAG==0)
	{
		LCD_SetCursor(0,8);
		LCD_WriteString("LIGHT OFF ");
	}
	else if(LIGHT_FLAG==1)
	{
		LCD_SetCursor(0,8);
		LCD_WriteString("LIGHT ON ");
	}
	if(FAN_FLAG==0)
	{
		LCD_SetCursor(1,0);
		LCD_WriteString("FAN OFF ");
	}
	else if(FAN_FLAG==1)
	{
		LCD_SetCursor(1,0);
		LCD_WriteString("FAN ON ");
	}
	if(PUMP_FLAG==0)
	{
		LCD_SetCursor(1,8);
		LCD_WriteString("PUMP OFF ");
	}
	else if(PUMP_FLAG==1)
	{
		LCD_SetCursor(1,8);
		LCD_WriteString("PUMP ON ");
	}
	//_delay_ms(2000);
}

void SLAVE_Runnable(void)
{
	 rec_data=UART_ReceiveUsingpooling();
	task_search(rec_data);	
	
 	if( rec_data != 'x' || rec_data != 'b')
 	{
 		tasks_monitor();
 	}
}
// void SLAVE_Auto_Runnable(void)
// {
// 	u16 temp,light,smoke;
// 	light=LDR_Read();
// 	temp=TEMP_Read();
// 	smoke=PRESSURE_Read();
// 	LCD_SetCursor(0,0);
// 	LCD_WriteNumIn4Dig(temp);
// 	LCD_WriteString("              ");
// 	LCD_SetCursor(1,0);
// 	LCD_WriteNumber(light);
// 	LCD_WriteString("              ");
// }

// void SLAVE_Mode_Chosen(u8*recieved) 
// {
// 	u8 choice=char_2int(recieved);
// 	if( choice == MANUAL)
// 	{
// 		LCD_WriteString("MANUAL");
// 		
// 	} 
// 	else if( choice == AUTO)
// 	{
// 		LCD_WriteString("AUTO");
// 	}
// 	else if( choice == CLEAR)
// 	{
// 		LCD_WriteString("CLEAR");
// 	}
// }

// u8 char_2int(u8*recieved)
// {
//
// 	u8 num=0;
//
// 		if(*recieved >= '0' && *recieved <= '9')
// 		{
// 			num=num*10+(*recieved-'0')+0;
// 		}
// 	return num;
// }


// void SLAVE_Manual_Mode(u8*job)
// {
// 	u8 task_chosen=char_2int(job);
// 	tasks[*job]();
//
// }

// void (*tasks[NO_TASKS])(void)=
// {
// 	FAN_ON,FAN_OFF,
// 	LIGHT_ON,LIGHT_OFF,
// 	TV_ON,TV_OFF,
// 	PUMP_ON,PUMP_OFF
// };

/*void Runnable_task(void)
{
	UART_RecieveString(recieved);
	SLAVE_Mode_Chosen(recieved);
	Full_Flag=1;
	Empty_buffer_recieved(recieved);
	UART_RecieveString(recieved);
	UART_split_string(recieved,split,&parameter);
	task_search(split,&parameter);
	Empty_buffer_recieved(recieved);
	Empty_buffer_split(split);
	
}*/
// void Empty_buffer_recieved(u8*str) // takes recieved str from UART
// {  
// 	u8 i;
// 	if(Full_Flag == 1)
// 	{
// 		for(i=0;str[i];i++)
// 		{
// 			str[i]=0;
// 		}
// 		Full_Flag=0;
// 	}
// }
/*void Empty_buffer_split(u8*str) // takes recieved str from UART
{
	u8 i;
	if(Split_Full_Flag == 1)
	{
		for(i=0;str[i];i++)
		{
			str[i]=0;
		}
		Split_Full_Flag=0;
	}
}*/
// task_t tasks[NO_TASKS]={
// 	
// 	{"fanon",FAN_ON},
// 	{"fanoff",FAN_OFF},
// 	{"lighton",LIGHT_ON},
// 	{"lightoff",LIGHT_OFF},
// 	{"tvon",TV_ON},
// 	{"tvoff",TV_OFF},
// 	{"pumpon",PUMP_ON},
// 	{"pumpoff",PUMP_OFF}
// };


//u8 recieved[10];
//u8 split[10];
//u8 parameter=0;
//static u8 Full_Flag=0/*,Split_Full_Flag=0*/;
