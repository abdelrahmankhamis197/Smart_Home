
#include "STDTYPES.h"
#include "DIO_interface.h"
 #include "KeyPad_cfg.h"
#include "KeyPad.h"

void KEYPAD_Init(void)
 {
     for(u8 i=0;i<ROWS;i++)
 	{
 		DIO_WritePin(ROW_arr[i],HIGH);
 	}
 
 }
 
  u8 KEYPAD_Get_Key(void)
  {
 	u8 r,c;
 	u8 key=NO_KEY;
 	for(r=0;r<ROWS;r++)
 	{
 		DIO_WritePin(ROW_arr[r],LOW);
 		for(c=0;c<COLS;c++)
 		{
 			if(DIO_ReadPin(COL_arr[c])==LOW)
 			{
 				key=KeysArray[r][c];
 				while(DIO_ReadPin(COL_arr[c])==LOW);
 			}
 		}
 		
 		DIO_WritePin(ROW_arr[r],HIGH);
 	}
 	return key;
  }
  
 //********************************************************************
//   const u8 KeysArray[ROWS][COLS]={
 // 	 {'7','8','9','/'},
 // 	 {'4','5','6','*'},
 // 	 {'1','2','3','-'},
 // 	 {'c','0','=','+'},
 //  };
 //  void KEYPAD_Init(void)
 //  {
 // 	 DIO_WritePin(FIRST_OUTPUT,HIGH);
 // 	 DIO_WritePin(FIRST_OUTPUT+1,HIGH);
 // 	 DIO_WritePin(FIRST_OUTPUT+2,HIGH);
 // 	 DIO_WritePin(FIRST_OUTPUT+3,HIGH);
 //  }
 // 
 //  u8 KEYPAD_GetKey(void)
 //  {
 // 	 u8 r,c,key=NO_KEY;
 // 	 for (r=0;r<ROWS;r++)
 // 	 {
 // 		 DIO_WritePin(FIRST_OUTPUT+r,LOW);
 // 		 for (c=0;c<COLS;c++)
 // 		 {
 // 			 if (DIO_ReadPin(FIRST_INPUT+c)==LOW)
 // 			 {
 // 				 key=KeysArray[r][c];
 // 				 while(DIO_ReadPin(FIRST_INPUT+c)==LOW);
 // 			 }
 // 		 }
 // 		 DIO_WritePin(FIRST_OUTPUT+r,HIGH);
 // 	 }
 // 	 
 // 	 return key;
 // 	 
 //  }