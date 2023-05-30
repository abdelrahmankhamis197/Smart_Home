

#ifndef KEYPAD_H_
#define KEYPAD_H_
# define NO_KEY 'X'

void KEYPAD_Init(void);

u8 KEYPAD_Get_Key(void);

//**************************************************************
// #define  FIRST_OUTPUT   PINB4
// #define  FIRST_INPUT   PIND2
// 
// 
// 
// 
// #define  ROWS   4
// #define  COLS   4
// 
// 
// 
// extern const u8 KeysArray[ROWS][COLS];
// #define  NO_KEY   'T'
// 
// void KEYPAD_Init(void);
// 
// u8 KEYPAD_GetKey(void);

#endif /* KEYPAD_H_ */