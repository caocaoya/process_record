
#ifndef   __CODE_PROCESS_RECODE_H
#define   __CODE_PROCESS_RECODE_H

#define uint8_t  unsigned char
#define uint16_t unsigned int 
#define uint32_t unsigned long

typedef struct 
{
	uint8_t   Line_Number;
	uint8_t   Process_Number;
	char      CMD_Name[20];
    void     (*Precess_Function)(void); 
    
}Function_Call_Type;



typedef struct 
{
	uint8_t   Line_Number;
	uint8_t   Process_Number;
	uint32_t  UTC_Time;
	char      CMD_Name[20];	
	
	uint8_t   Save_Len;
	uint8_t   Save_Front;
	Function_Call_Type Save_Process[10];
	
}Process_Record_Type;





#endif 









