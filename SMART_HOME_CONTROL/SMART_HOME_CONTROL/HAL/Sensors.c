
#include "STDTYPES.h"
#include "Sensors.h"
#include "ADC.h"

/*RETURN C*10*/
u16 TEMP_Read(void)
{
	u16 volt=ADC_ReadVolt(LM35_CH);
	return volt;
}

u16 PRESSURE_Read(void)
{
	u16 adc=ADC_Read(PRESS_CH);
	u16 pressure;
	pressure = (((u32)(adc-55)*1000)/921)+150;
	return pressure;
}
u16 LDR_Read(void)
{
	u16 light=1024-ADC_Read(LDR_CH);
	return light;
}

