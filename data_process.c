
#include "string.h"
#include "stdio.h"
#include "code_process_recode.h"

#define CMD_TATOL  20

void pritnf_set(void)
{
	char str[12] = "123456\0";
	printf("%s\n",str);
}

Process_Record_Type  Process_Record = {0};
Function_Call_Type   Process_Command[CMD_TATOL] = 
{
	{1,2, "at+cmd0\0", pritnf_set},
	{1,2, "at+cmd1\0", pritnf_set},
};

uint8_t Process_Check(Process_Record_Type  *process_record)
{
	uint8_t checkou_count = 0;
	
	for(checkou_count = 0; checkou_count < 3/*(sizeof(Process_Command)/sizeof(Function_Call_Type))*/; checkou_count++)
	{
		/*
		//printf("process_record -> Line_Number    = %d\n\n",process_record->Line_Number );
		//printf("process_record -> Process_Number = %d\n\n",process_record->Process_Number );
		//printf("process_record -> CMD_Name       = %s\n\n",process_record->CMD_Name );

		//printf("Process_Command[%d].Line_Number    = %d\n\n",checkou_count,Process_Command[checkou_count].Line_Number );
		//printf("Process_Command[%d].Process_Number = %d\n\n",checkou_count,Process_Command[checkou_count].Process_Number );
		//printf("Process_Command[%d].CMD_Name       = %s\n\n",checkou_count,Process_Command[checkou_count].CMD_Name );
		*/		
		 if( ((process_record->Line_Number == Process_Command[checkou_count].Line_Number) && \
		      (process_record->Process_Number == Process_Command[checkou_count].Process_Number)) || \
			 ((strstr(process_record->CMD_Name, Process_Command[checkou_count].CMD_Name) != 0) && (Process_Command[checkou_count].CMD_Name != 0))
		   )
		  {
		  	if(Process_Command[checkou_count].Precess_Function != 0) 
		  	{
		  		Process_Command[checkou_count].Precess_Function();	
			}
		  	/*//printf("check_count = %d\n\n",checkou_count);*/
		  }
	}
}

uint8_t Process_Record_Wirte(Process_Record_Type  *process_record,Process_Record_Type  *process_record_now)
{
	uint8_t save_len = 0;
	uint8_t save_recod_len = (sizeof(process_record -> Save_Process)/sizeof(Function_Call_Type));
	        
	printf("sizeof(process_record -> Save_Process)       = %d\n\n", sizeof(process_record -> Save_Process));
	printf("sizeof(Process_Record_Type)                  = %d\n\n", sizeof(Function_Call_Type));

	process_record -> Line_Number     = process_record_now -> Line_Number; 
	process_record -> Process_Number  = process_record_now -> Process_Number; 
	
	memcpy(process_record -> CMD_Name, process_record_now -> CMD_Name, sizeof(Process_Record.CMD_Name));
	
	if( process_record -> Save_Len < save_recod_len)
	{
		save_len = process_record -> Save_Len;
	}
	else
	{
		save_len = (process_record -> Save_Len)%(save_recod_len);
		
		if(process_record -> Save_Len >= 5*save_recod_len)
		{
			process_record -> Save_Len = save_recod_len;
		}
	}
	
	process_record -> Save_Process[save_len].Line_Number = process_record -> Line_Number;
	process_record -> Save_Process[save_len].Process_Number = process_record -> Process_Number;
	memcpy(process_record -> Save_Process[save_len].CMD_Name, process_record -> CMD_Name, sizeof(Process_Record.CMD_Name));
	process_record -> Save_Len++;
	process_record -> Save_Front = save_len;
    
}

uint8_t Process_Record_Read(Process_Record_Type *process_record)
{
	uint8_t record_count = 0;
	uint8_t save_recod_len = (sizeof(process_record -> Save_Process)/sizeof(Function_Call_Type));

	if(process_record -> Save_Len > 0)
	{
		printf("process_record -> Save_Len         = %d\n\n", process_record -> Save_Len);	
        printf("process_record -> Save_Front       = %d\n\n", process_record -> Save_Front);
        
        if(save_recod_len > process_record -> Save_Len )
        {
        	save_recod_len = process_record -> Save_Len; 
		}
        
		for(;record_count < save_recod_len; record_count++ )	
		{
			printf("process_record -> Save_Process[%d].Line_Number    = %d\n\n", record_count,process_record -> Save_Process[record_count].Line_Number );
			printf("process_record -> Save_Process[%d].Process_Number = %d\n\n", record_count,process_record -> Save_Process[record_count].Process_Number );
			printf("process_record -> Save_Process[%d].CMD_Name       = %s\n\n", record_count,process_record -> Save_Process[record_count].CMD_Name );	
		} 
	}
} 

int main()
{
	uint8_t count = 0;
	
	Process_Record_Type  Process_Record_now = {0};
	Process_Record_now.Line_Number = 1;
	Process_Record_now.Process_Number = 2;
	memcpy(Process_Record_now.CMD_Name, "AT+CMD", sizeof(Process_Record_now.CMD_Name));
	
	for(count = 0; count < 4; count++)
	{
	    Process_Record_now.Line_Number = count;
	    Process_Record_Wirte(&Process_Record, &Process_Record_now);
		Process_Check(&Process_Record);
	}
	
	Process_Record_Read(&Process_Record);
}
