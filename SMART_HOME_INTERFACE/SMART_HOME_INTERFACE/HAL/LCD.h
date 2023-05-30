
#ifndef LCD_H_
#define LCD_H_


# define F_CPU 8000000
#include<util/delay.h>
#include "STDTYPES.h"
#include "DIO_Interface.h"


/*********************pin config*************************/

#define  RS			 PINA1
#define  EN			 PINA2
#define  LCD_PORT    PA

/*******************LCD_MODE***********************************/

#define  LCD_MODE			KIT_MODE
#define  _8_BITMODE			2
#define  _4_BITMODE			0
#define  KIT_MODE			1
#define  _4BIT_SEPARATED	3
#define  ROW1_COMMAND		0X80//return home 0b10000000
#define  ROW2_COMMAND		0XC0//DDRAM is 80 location and 16 of them unused so they used for general ram and so
							// we add 64 location on return home command to down to row no 2
 
/*******************_4_BITMODE********************************************/
#define  _4BIT_MASK        0XF0  //most 4 bit
#define  COMMAND1_MASK     0X09
#define  DATA1_MASK        0X0B
#define  KITPORTA_MASK	   0X81
#define  KIT_MASK	       0X78
#define  PORTA_DATAKIT     0x83
#define  PORTA_COMMANDKIT  0x81
/********************_4_BITMODE******************************************/
//#define  KIT_MASK         0x78  //LCD_PORT connected with PA3 pA4 PA5 PA6
#define		COMMAND_MASK		0x81
#define		DATA_MASK			0x83
#define		M_4BIT_MASK			0X78
#define		LCD_D4				PINA3
#define		LCD_D5				PINA4
#define		LCD_D6				PINA5
#define		LCD_D7				PINA6
#define		CLEAR_BITS_REG(Reg,Mask)	Reg=(Reg&(~Mask))
#define		SET_BITS_REG(Reg,Mask)		Reg|=(Mask)


void LCD_Init(void);
 void LCD_WriteData(u8 data);
 void LCD_WriteCommand(u8 command);
void LCD_WriteSignNumber(s32 num);
void LCD_Clear(void);
void LCD_WriteChar(u8 ch);
void LCD_WriteNumber(u32 num);
void LCD_WriteString(u8 *str);
void LCD_WriteNumInBin(u8 num);
void LCD_WriteNumInFullBin(u8 num);
void DIO_WriteBitsInPort(DIO_Port_type Port,u8 Value,u8 Mask);
void LCD_WriteNumberInHexa(u8 num);
void LCD_WriteNumIn4Dig(u16 num);
void LCD_WriteNumIn2Dig(u8 num);
void LCD_WriteNumIn3Dig(u16 num);
void LCD_SetCursor(u8 row,u8 col);
void LCD_WriteInArrabic(u8 *arr,u8 block_no,u8 x_loc,u8 y_loc);
#endif /* LCD_H_ */