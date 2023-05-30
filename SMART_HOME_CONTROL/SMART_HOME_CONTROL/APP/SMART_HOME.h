 
#ifndef SMART_HOME_H_
#define SMART_HOME_H_

#define NO_TASKS 13

#define  FAN_PIN   0
#define  LIGHT_PIN 1
#define  TV_PIN    2
#define  PUMP_PIN  3 


typedef struct task{
	u8 task_name;
	void(*pfnc)(void);
}task_t;

void PASSED_Security(void);
void FAILED_Security(void);
void AUTO_Mode(void);
void MANUAL_Mode(void);
void EXIT_AUTO(void);
void FAN_ON(void);
void FAN_OFF(void);

void LIGHT_ON(void);
void LIGHT_OFF(void);

void TV_ON(void);
void TV_OFF(void);

void PUMP_ON(void);
void PUMP_OFF(void);



void task_search(u8 task_name);
void SLAVE_Runnable(void);



#endif /* SMART_HOME_H_ */