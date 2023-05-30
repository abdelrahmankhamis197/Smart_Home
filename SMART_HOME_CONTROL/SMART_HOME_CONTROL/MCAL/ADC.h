

#ifndef ADC_H_
#define ADC_H_

typedef enum
{
	VREF_AREF,
	VREF_AVCC,
	VREF_256V
}ADC_Vref_type;

typedef enum
{
	CH_0=0,
	CH_1,
	CH_2,
	CH_3,
	CH_4,
	CH_5,
	CH_6,
	CH_7
}ADC_channel_type;

typedef enum
{
	ADC_SCALLER_2=1,
	ADC_SCALLER_4,
	ADC_SCALLER_8,
	ADC_SCALLER_16,
	ADC_SCALLER_32,
	ADC_SCALLER_64,
	ADC_SCALLER_128
}ADC_Scaller_type;

void ADC_Init(ADC_Vref_type vref,ADC_Scaller_type scaler);
u16 ADC_Read(ADC_channel_type ch);

u16 ADC_ReadVolt(ADC_channel_type ch);



#endif /* ADC_H_ */