
#ifndef EXINT_H_
#define EXINT_H_

typedef enum
{
	EX_INT0=0,
	EX_INT1,
	EX_INT2
}ExInterruptSource_type;

typedef enum
{
	LOW_LEVEL=0,
	ANY_LOGIC_CHANGE,
	FALLING_EDGE,
	RISING_EDGE
}TriggerEdge_type;


void Enable_GlobalInterrupt(void);
void Disable_GlobalInterrupt(void);
void EXI_Enable(ExInterruptSource_type Interrupt);
void EXI_Disable(ExInterruptSource_type Interrupt);
void EXI_TriggerEdge(ExInterruptSource_type Interrupt,TriggerEdge_type Edge);
void EXI_SetCallBack(ExInterruptSource_type Interrupt,void(*LocalPtr)(void));



#endif /* EXINT_H_ */