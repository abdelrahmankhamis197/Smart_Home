#include "MEMMAP.h"
#include "UTILS.h"
#include "STDTYPES.h"
#include "EXINT.h"


static void (*PTF_EXTINT0)(void)=(void*)0;
static void (*PTF_EXTINT1)(void)=(void*)0;
static void (*PTF_EXTINT2)(void)=(void*)0;

void EXI_Enable(ExInterruptSource_type Interrupt)
{
	switch(Interrupt)
	{
		case EX_INT0:
		SET_BIT(GICR,GICR_INT0);
		break;
		case EX_INT1:
		SET_BIT(GICR,GICR_INT1);
		break;
		case EX_INT2:
		SET_BIT(GICR,GICR_INT2);
		break;
	}
	
}

void EXI_Disable(ExInterruptSource_type Interrupt)
{
	switch(Interrupt)
	{
		case EX_INT0:
		CLR_BIT(GICR,GICR_INT0);
		break;
		case EX_INT1:
		CLR_BIT(GICR,GICR_INT1);
		break;
		case EX_INT2:
		CLR_BIT(GICR,GICR_INT2);
		break;
	}
}

void EXI_TriggerEdge(ExInterruptSource_type Interrupt,TriggerEdge_type Edge)
{
	switch(Interrupt){
		case EX_INT0:
		switch(Edge){
			case LOW_LEVEL:
			CLR_BIT(MCUCR,ISC00);
			CLR_BIT(MCUCR,ISC01);
			break;
			case ANY_LOGIC_CHANGE:
			SET_BIT(MCUCR,ISC00);
			CLR_BIT(MCUCR,ISC01);
			break;
			case FALLING_EDGE:
			CLR_BIT(MCUCR,ISC00);
			SET_BIT(MCUCR,ISC01);
			break;
			case RISING_EDGE:
			SET_BIT(MCUCR,ISC00);
			SET_BIT(MCUCR,ISC01);
			break;
			
		}
		break;
		case EX_INT1:
		switch(Edge){
			case LOW_LEVEL:
			CLR_BIT(MCUCR,ISC10);
			CLR_BIT(MCUCR,ISC11);
			break;
			case ANY_LOGIC_CHANGE:
			SET_BIT(MCUCR,ISC10);
			CLR_BIT(MCUCR,ISC11);
			break;
			case FALLING_EDGE:
			CLR_BIT(MCUCR,ISC10);
			SET_BIT(MCUCR,ISC11);
			break;
			case RISING_EDGE:
			SET_BIT(MCUCR,ISC10);
			SET_BIT(MCUCR,ISC11);
			break;
			
		}
		break;
		case EX_INT2:
		switch(Edge){
			case FALLING_EDGE:
			CLR_BIT(MCUCSR,MCUCSR_ISC2);
			break;
			case RISING_EDGE:
			SET_BIT(MCUCSR,MCUCSR_ISC2);
			break;
			default:
			CLR_BIT(MCUCSR,MCUCSR_ISC2);
		}
		break;
	}
}

void Enable_GlobalInterrupt(void)
{
	__asm__ __volatile__ ("sei" ::);
}

void Disable_GlobalInterrupt(void)
{
	__asm__ __volatile__ ("cli" ::);
}

void EXI_SetCallBack(ExInterruptSource_type Interrupt,void(*LocalPtr)(void))
{
	switch (Interrupt)
	{
		case EX_INT0:
		PTF_EXTINT0=LocalPtr;
		break;
		case EX_INT1:
		PTF_EXTINT1=LocalPtr;
		break;
		case EX_INT2:
		PTF_EXTINT2=LocalPtr;
		break;
	}
	
}

ISR(INT0_vect)
{
	if(PTF_EXTINT0!=(void*)0)
	{
		PTF_EXTINT0();
	}
}

ISR(INT1_vect)
{
	if(PTF_EXTINT1!=(void*)0)
	{
		PTF_EXTINT1();
	}
}

ISR(INT2_vect)
{
	if(PTF_EXTINT2!=(void*)0)
	{
		PTF_EXTINT2();
	}
}