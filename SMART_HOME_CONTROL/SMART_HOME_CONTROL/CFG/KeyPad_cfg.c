#include "DIO_interface.h"
#include "KeyPad_cfg.h"
	
	const u8 KeysArray[ROWS][COLS]={
		
		{'7','8','9','A'},
		{'4','5','6','B'},
		{'1','2','3','C'},
		{'c','0','=','D'}
	};
	
	
	
	const u8 ROW_arr[ROWS]={PINB4,PINB5,PINB6,PINB7};
	const u8 COL_arr[COLS]={PINC2,PINC3,PINC4,PINC5};
		
		