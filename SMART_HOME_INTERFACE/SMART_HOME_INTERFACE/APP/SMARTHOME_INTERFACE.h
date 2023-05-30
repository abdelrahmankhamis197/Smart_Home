
#ifndef SMARTHOME_INTERFACE_H_
#define SMARTHOME_INTERFACE_H_


/*		                        DEFINTIONS							             */

/** FOR HANDLING THE SECURITY PART**/
#define  EEPROM_STATUS_LOCATION 0x20
#define  EEPROM_PASSWORD_LOCATION 0x21
#define NOTPRESSED 0xff
#define PRESSED 0x00
#define SET 0
#define CHECK 1
#define  RESET 2
#define MAX_TRIALS 3
/***********************************/

/*_______________________________________________________________________________________*/

/****** handling the security part *****/

void SMARTHOME_Security_Runnable(void); // to be put in the main runnable function

void MAX_TRIALS_HNADLER(void); // handles the max trials case  turn on buzzer and asking for the pin to reset a new password
bool_type SMARTHOME_CheckPassword(void); // checks the password
void SMARTHOME_SetPassword(void); // sets the password for the first time
u8 SMARTHOME_Security_Init(void); // making the decision if the password is set for the first time or not
u8 SMARTHOME_Security_Scan(void); // takes or sets the password from keypad
void SMARTHOME_DoorOpen(void); // move servo 180

void SMARTHOME_DoorClose(void); // back the servo to 0

/****************************************************/




#endif /* SMARTHOME_INTERFACE_H_ */