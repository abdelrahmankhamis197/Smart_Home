#include "STDTYPES.h"
#include "MEMMAP.h"
#include "TIMERS.h"
#include "SERVO.h"
void SERVO_SetPostiion(u8 angle)
{
	OCR1A=((angle*(u32)1000)/180)+999;
}
void SERVO_Init(void)
{
	Timer1_Init(TIMER1_FASTPWM_ICR_TOP_MODE,TIMER1_SCALER_8);
	Timer1_OCRA1Mode(OCRA_NON_INVERTING);
	ICR1=20000;
}

