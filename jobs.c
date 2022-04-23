#include "shell.h"

int myCompare(const void *a, const void *b)
{
    const char *pa = *(const char **)a;
    const char *pb = *(const char **)b;

    return strcmp(pa, pb);
}

int cstring_cmp(const void *a, const void *b)
{
    const char **ia = (const char **)a;
    const char **ib = (const char **)b;
    return strcmp(*ia, *ib);
    /* strcmp functions works exactly as expected from
	comparison function */
}

void execute_jobs(char *string)
{
    char *processes[number_of_processes - 1];
    char pinfo[50];
    char status[50];
    for (int i = 1; i < number_of_processes; i++)
    {
        processes[i - 1] = malloc(MAX_LENGTH_OF_COMMAND * sizeof(char));
        strcpy(processes[i - 1], process_names[i]);
    }

    struct process *zero = current;
    while (zero != NULL)
    {
        zero->printed = 0;
        zero = zero->next;
    }
    
    
    size_t strings_len = sizeof(processes) / sizeof(char *);
    qsort(processes, strings_len, sizeof(char *), cstring_cmp);

    int r = 0;
    int s = 0;
    if (strcmp(string, "jobs") == 0)
    {
        r = 1;
        s = 1;
    }
    else if (string[strlen(string) - 1] == 's')
    {
        s = 1;
    }
    else if (string[strlen(string) - 1] == 'r')
    {
        r = 1;
    }
    struct process *dummy = current;

    for (int i = 0; i < number_of_processes - 1; i++)
    {
        int j = 0;
        //printf("%d",i);

        while (dummy != NULL)
        {//printf("%d",i);

            if (strcmp(dummy->process_name, processes[i]) == 0)
            {
                if (dummy->printed == 0)
                {
                    if ((dummy->status == 1) && (r == 1))
                    {
                        
                        sprintf(pinfo, "pinfo %d", dummy->pid);
                        process_status_pinfo(pinfo);
                        
                        if (process_status[0] == 'R')
                        {
                            strcpy(process_status, "Running");
                            printf("[%d] %s %s [%d]\n", dummy->process_number, process_status, dummy->process_name, dummy->pid);
                        dummy->printed = 1;
                        
                        }
                        if (process_status[0] == 'S' && process_status[1] == ' ')
                        {
                            strcpy(process_status, "Running");
                            printf("[%d] %s %s [%d]\n", dummy->process_number, process_status, dummy->process_name, dummy->pid);
                        dummy->printed = 1;
                        
                        }
                        
                        if (process_status[0] == 'Z')
                        {
                            strcpy(process_status, "Zombie");
                            printf("[%d] %s %s [%d]\n", dummy->process_number, process_status, dummy->process_name, dummy->pid);
                        dummy->printed = 1;
                        
                        }
                        if (process_status[0] == 'T')
                        {
                            strcpy(process_status, "Stopped");
                            //continue;
                        }

                        
                    }
                    if ((dummy->status == 1) && (s == 1))
                    {
                        sprintf(pinfo, "pinfo %d", dummy->pid);
                        process_status_pinfo(pinfo);
                        
                        if (process_status[0] == 'T')
                        {
                            strcpy(process_status, "Stopped");
                            printf("[%d] %s %s [%d]\n", dummy->process_number, process_status, dummy->process_name, dummy->pid);
                        dummy->printed = 1;
                        
                            
                        }
                        if (process_status[0] == 'R')
                        {
                            strcpy(process_status, "Running");
                            
                        
                            //continue;
                        }
                        if (process_status[0] == 'Z')
                        {
                            strcpy(process_status, "Zombie");
                            
                        
                            //continue;
                        }
                        
                        //dummy->printed = 1;
                                                  //  printf("[%d] %s %s [%d]\n", dummy->process_number, process_status, dummy->process_name, dummy->pid);
                        
                    }
                    
                     if ((dummy->status == 0))
                    {
                        

                        //printf("[%d] Stopped %s [%d]\n", dummy->process_number, dummy->process_name, dummy->pid);
                        dummy->printed = 1;
                        break;
                    }
                }

                
            }
            dummy = dummy->next;
            //printf("%d",dummy->next);
        }
        j = 0;
        dummy = current;
    }
}
/* for (int i = 0; i < number_of_processes; i++)
    {
        printf("%s",dummy->process_name);
        dummy=dummy->next;
    }  */
