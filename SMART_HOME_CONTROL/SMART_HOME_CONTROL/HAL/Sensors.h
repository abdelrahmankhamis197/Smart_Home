
#ifndef SENSORS_H_
#define SENSORS_H_

#define  LM35_CH CH_0
#define  PRESS_CH CH_1
#define LDR_CH CH_2

u16 TEMP_Read(void);

u16 PRESSURE_Read(void);

u16 LDR_Read(void);


#endif /* SENSORS_H_ */