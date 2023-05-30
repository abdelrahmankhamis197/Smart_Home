#include "UTILS.h"
#include "LCD.h"

#if (LCD_MODE==_8_BITMODE)
void LCD_WriteCommand(u8 command)
{
	DIO_WritePin(RS,LOW);//Rs=0 in Command_request
	DIO_WritePort(LCD_PORT,command);
	DIO_WritePin(EN,HIGH);//indicate for reading data
	_delay_ms(1);
	DIO_WritePin(EN,LOW);//indicate for writing data
	_delay_ms(1);
}

void LCD_WriteData(u8 data)
{
	DIO_WritePin(RS,HIGH);//Rs=1 in data_request
	DIO_WritePort(LCD_PORT,data);
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
}

void LCD_Init(void)
{
	_delay_ms(50);
	LCD_WriteCommand(0X38);// 8 bit mode ,2 lines ,font 5*7
	_delay_ms(1);
	LCD_WriteCommand(0X0C);// 0X0C,0X0E,0X0F LCD display cursor display& blink
	_delay_ms(1);
	LCD_WriteCommand(0x01);// clear LCD
	_delay_ms(2);
	LCD_WriteCommand(0X06);// increase address in DDram and no shift
	_delay_ms(1);
}

/************************************************************************************************************/
#elif (LCD_MODE==_4_BITMODE)//PA4,PA5,PA6,PA7
void LCD_WriteCommand(u8 command)
{
	//DIO_WritePin(PINB6,HIGH);
	u8 mask;
	DIO_WritePin(RS,LOW);//connected with PA1
	PORTA=PORTA&COMMAND1_MASK;//masking with bin(0,3);
	mask=(command&_4BIT_MASK)|PORTA;
	DIO_WritePort(LCD_PORT,mask);
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
	PORTA=PORTA&COMMAND1_MASK;//masking with bin(0,3);
	mask=((command<<4)&_4BIT_MASK)|PORTA;
	DIO_WritePort(LCD_PORT,mask);
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
}

void LCD_WriteData(u8 data)
{
	//DIO_WritePin(PINB5,HIGH);
	u8 mask;
	DIO_WritePin(RS,HIGH);
	PORTA=PORTA&DATA1_MASK;//masking with bin(0,1,3);
	mask=(data&_4BIT_MASK)|PORTA;
	DIO_WritePort(LCD_PORT,mask);
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
	PORTA=PORTA&DATA1_MASK;//masking with bin(0,1,3);
	mask=((data<<4)&_4BIT_MASK)|PORTA;
	DIO_WritePort(LCD_PORT,mask);
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
}

void LCD_Init(void)
{
	//DIO_WritePin(PINB4,HIGH);
	_delay_ms(50);          
	LCD_WriteCommand(0x02);//row 1 shifted by 4to the right(function set 1) 
	_delay_ms(1);
	LCD_WriteCommand(0x28); //row 2 oring with row 3 after shifted by 4 to right(function set 2)
	_delay_ms(1);           
	LCD_WriteCommand(0x0c); //row 1 oring with row 2 after shifted by 4 to right(display on off)
	_delay_ms(1);    
	LCD_WriteCommand(0x01); //row 1 oring with row 2 after shifted by 4 to right(clear lcd)
	_delay_ms(2);
	LCD_WriteCommand(0x06);//row 1 oring with row 2 after shifted by 4 to right(mode set)
	_delay_ms(2);
}

#elif (LCD_MODE==KIT_MODE)//PA3,PA4,PA5,PA6
 void LCD_WriteCommand(u8 Command)//0b1011_1011
{
	u8 mask;
	DIO_WritePin(RS,LOW);
	PORTA=PORTA&PORTA_COMMANDKIT;//0b10000001
	mask=(Command>>1)&KIT_MASK;//0b01111000
	mask=mask|PORTA;
	DIO_WritePort(PORTA,mask);
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
	PORTA=PORTA&PORTA_COMMANDKIT;//to not_effect on Bits(0,7);
	mask=(Command<<3)&KIT_MASK;//Kit_Mask=0x78
	mask=mask|PORTA;
	DIO_WritePort(PORTA,mask);
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
}
 void LCD_WriteData(u8 data)
{
	u8 mask;
	DIO_WritePin(RS,HIGH);
	PORTA=PORTA&PORTA_DATAKIT;//KITPORTA_MASK  0x83
	mask=(data>>1)&KIT_MASK;
	mask=mask|PORTA;
	PORTA=mask;
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
	PORTA=PORTA&PORTA_DATAKIT;//#define  PORTA_DATAKIT  0x83
	mask=(data<<3)&KIT_MASK;
	mask=mask|PORTA;
	PORTA=mask;
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
}

void LCD_Init(void)
{
	_delay_ms(50);
	LCD_WriteCommand(0x02);//row 1 oring with row 2(function set 1)
	_delay_ms(1);
	LCD_WriteCommand(0x28); //row 2 oring with row 3 after shifted by 4 to right(function set 2)
	_delay_ms(1);
	LCD_WriteCommand(0x0c); //row 1 oring with row 2 after shifted by 4 to right(display on off)
	_delay_ms(1);
	LCD_WriteCommand(0x01); //row 1 oring with row 2 after shifted by 4 to right(clear lcd)
	_delay_ms(2);
	LCD_WriteCommand(0x06);//row 1 oring with row 2 after shifted by 4 to right(mode set)
	_delay_ms(2);
}

#elif (LCD_MODE==_4BIT_SEPARATED)
 void LCD_WriteCommand(u8 Command)
{
	DIO_WritePin(RS,LOW);//
	DIO_WritePin(LCD_D4,READ_BIT(Command,4));
	DIO_WritePin(LCD_D5,READ_BIT(Command,5));
	DIO_WritePin(LCD_D6,READ_BIT(Command,6));
	DIO_WritePin(LCD_D7,READ_BIT(Command,7));
	DIO_WritePin(EN,HIGH);
	_delay_ms(2);
	DIO_WritePin(EN,LOW);
	_delay_ms(2);
	DIO_WritePin(LCD_D4,READ_BIT(Command,0));
	DIO_WritePin(LCD_D5,READ_BIT(Command,1));
	DIO_WritePin(LCD_D6,READ_BIT(Command,2));
	DIO_WritePin(LCD_D7,READ_BIT(Command,3));
	DIO_WritePin(EN,HIGH);
	_delay_ms(2);
	DIO_WritePin(EN,LOW);
	_delay_ms(2);
}

void LCD_WriteData(u8 Data)
{
	DIO_WritePin(RS,HIGH);
	DIO_WritePin(LCD_D4,READ_BIT(Data,4));
	DIO_WritePin(LCD_D5,READ_BIT(Data,5));
	DIO_WritePin(LCD_D6,READ_BIT(Data,6));
	DIO_WritePin(LCD_D7,READ_BIT(Data,7));
	DIO_WritePin(EN,HIGH);
	_delay_ms(2);
	DIO_WritePin(EN,LOW);
	_delay_ms(2);
	DIO_WritePin(LCD_D4,READ_BIT(Data,0));
	DIO_WritePin(LCD_D5,READ_BIT(Data,1));
	DIO_WritePin(LCD_D6,READ_BIT(Data,2));
	DIO_WritePin(LCD_D7,READ_BIT(Data,3));
	DIO_WritePin(EN,HIGH);
	_delay_ms(2);
	DIO_WritePin(EN,LOW);
	_delay_ms(2);
}

void LCD_Init(void)
{
	_delay_ms(50);
	LCD_WriteCommand(0x02);//row 1 oring with row 2(function set 1)
	_delay_ms(1);
	LCD_WriteCommand(0x28); //row 2 oring with row 3 after shifted by 4 to right(function set 2)
	_delay_ms(1);
	LCD_WriteCommand(0x0c); //row 1 oring with row 2 after shifted by 4 to right(display on off)
	_delay_ms(1);
	LCD_WriteCommand(0x01); //row 1 oring with row 2 after shifted by 4 to right(clear lcd)
	_delay_ms(2);
	LCD_WriteCommand(0x06);//row 1 oring with row 2 after shifted by 4 to right(mode set)
	_delay_ms(2);
}

#endif

/*************************************************************************************************/

void LCD_WriteChar(u8 ch)
{
	LCD_WriteData(ch);
}


void LCD_WriteString(u8*str)
{
	u8 i;
	for(i=0;str[i];i++)
	{
		LCD_WriteData(str[i]);
	}
}

void LCD_WriteNumber(u32 num)
{
	u8 str[16]; //no. of pixels on lcd
	u8 i=0,j;
	if(num==0)
	{
		LCD_WriteData('0');
	}
	while(num)
	{
		str[i]=(num%10)+'0';
		i++;
		num/=10;
	}
	for(j=i;j>0;j--)
	{
		LCD_WriteData(str[j-1]);
	}
}


void LCD_WriteSignNumber(s32 num)
{
	u8 str[16];
	u8 i=0,j;
	if(num==0)
	{
		LCD_WriteData('0');
	}
	else if(num<0)
	{
		num*=-1;
		LCD_WriteData('-');
	}
	while(num>0)
	{
		str[i]=(num%10)+'0';
		i++;
		num/=10;
	}
	for(j=i;j>0;j--)
	{
		LCD_WriteData(str[j-1]);
	}
}


void LCD_WriteNumInBin(u8 num)
{
	u8 i,flag=0;
	if(num==0)
	{
		LCD_WriteNumInFullBin(num);
	}
	else
	{
		u8 x=(1<<7);
		LCD_WriteChar('0');
		LCD_WriteChar('b');
		for(i=0;i<8;i++)
		{
			if(((num<<i)&x)==x)
			{
				LCD_WriteData('1');
				flag=1;
			}
			else if(flag==1)
			{
				LCD_WriteData('0');
			}
		}
	}
}

void LCD_WriteNumInFullBin(u8 num)
{
	u8 i;
	LCD_WriteChar('0');
	LCD_WriteChar('B');
	u8 x=(1<<7);
	for(i=0;i<8;i++)
	{
		if(((num<<i)&x)==x)
		{
			LCD_WriteData('1');
		}
		else 
		{
			LCD_WriteData('0');
		}
	}
}

void LCD_WriteNumberInHexa(u8 num)
{
	u8 hex_num;
	LCD_WriteChar('0');
	LCD_WriteChar('X');
	hex_num=num/16;
	if(hex_num<10)
		LCD_WriteData(hex_num+'0');
	else 
		LCD_WriteData(hex_num+'7');
	hex_num=num%16;
	if(hex_num<10)
		LCD_WriteData(hex_num+'0');
	else
		LCD_WriteData(hex_num+'7');
}

void LCD_ConvertFromHex2Dec(u8 num) // takes number in hex form
{
	
}	
void LCD_Clear(void)
{
	LCD_WriteCommand(0x01);
	_delay_ms(1);
}

void LCD_WriteNumIn2Dig(u8 num)
{
	LCD_WriteChar(((num%100)/10)+'0');
	LCD_WriteChar((((num%10)/1)+'0'));
} 

void LCD_WriteNumIn3Dig(u16 num)
{
	LCD_WriteChar(((num%1000)/100)+'0');
	LCD_WriteChar((((num%100)/10)+'0'));
	LCD_WriteChar((((num%10)/1)+'0'));
}

void LCD_WriteNumIn4Dig(u16 num)
{
	LCD_WriteChar(((num%10000)/1000)+'0');
	LCD_WriteChar(((num%1000)/100)+'0');
	LCD_WriteChar((((num%100)/10)+'0'));
	LCD_WriteChar((((num%10)/1)+'0'));
}

void LCD_SetCursor(u8 row,u8 col)
{
	if(row==0)
	{
		LCD_WriteCommand(ROW1_COMMAND+col);
	}
	else if(row==1)
	{
		LCD_WriteCommand(ROW2_COMMAND+col);
	}
}

void inline LCD_WriteInArrabic(u8 *arr,u8 block_no,u8 x_loc,u8 y_loc)
{
	u8 i;
	LCD_WriteCommand(0b01000000+(block_no*8));
	for(i=0;i<8;i++)
	{
		LCD_WriteData(arr[i]);//kda bktb in CGRAM
	}
	LCD_WriteCommand(0b10000000);
	LCD_SetCursor(x_loc,y_loc);
	LCD_WriteData(block_no);
}

