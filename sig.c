#include "shell.h"

void execute_sig(char* string)
{
    char* token;
	char* rest = string;

    int i =0;
    int proc_num;
    int sig_num;
	while ((token = strtok_r(rest, " ", &rest)))
	{
        if (i==1)
        {
            proc_num = atoi(token);
        }
        else if (i==2)
        {
            sig_num = atoi(token);
        }
        else if (i==3)
        {
            break;
        }
        i++;
        
    }

    if ((sig_num<0)||(sig_num>32))
    {
        printf("Signal number doesnt exist");
    }
    

    if (proc_num>number_of_processes)
    {
        printf("Process doesnt exist\n");
        return;
    }

    struct process* dummy = current;

    if (dummy==NULL)
    {
        printf("Process doesnt exist\n");
        return;
    }
    

    while (dummy->process_number!=proc_num)
    {
        dummy=dummy->next;
    }
    
    kill(dummy->pid, sig_num);
    
}