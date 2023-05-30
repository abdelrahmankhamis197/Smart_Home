#include "MEMMAP.h"
#include "UTILS.h"
#include "STDTYPES.h"
# define F_CPU 8000000
#include<util/delay.h>
#include "ADC.h"

void ADC_Init(ADC_Vref_type vref,ADC_Scaller_type scaler)
{
	
	switch(vref)
	{
		case VREF_AREF:
		CLR_BIT(ADMUX,REFS1);
		CLR_BIT(ADMUX,REFS0);
		break;
		case VREF_AVCC:
		CLR_BIT(ADMUX,REFS1);
		SET_BIT(ADMUX,REFS0);
		break;
		case VREF_256V:
		SET_BIT(ADMUX,REFS1);
		SET_BIT(ADMUX,REFS0);
		break;
	}
	
	CLR_BIT(ADMUX,ADLAR);
	ADCSRA=ADCSRA&0XF8;
	ADCSRA=ADCSRA|scaler;
	//ADC_Enable
	SET_BIT(ADCSRA,ADEN);
}

u16 ADC_Read(ADC_channel_type ch)
{
	ADMUX=ADMUX&0XE0;
	ADMUX=ADMUX|ch;
	SET_BIT(ADCSRA,ADSC);
	_delay_ms(1);

	return ADC;
}

u16 ADC_ReadVolt(ADC_channel_type ch)
{
	u16 adc=ADC_Read(ch);
	u16 volt= (5000*(u32)adc)/1024;
	return volt;
}