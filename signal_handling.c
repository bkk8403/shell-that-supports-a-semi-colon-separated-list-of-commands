#include "shell.h"

void ctrl_c(int sig_num)
{
    int pid_c = getpid();
    if (pid_c!=shell_pid)
    {
        return;
    }
    if (running_foreground != -1)
    {
        kill(running_foreground, SIGINT);
    }
    signal(SIGINT, ctrl_c);


}

void ctrl_z(int sig_num)
{
    int pid = getpid();
    if (pid!=shell_pid)
    {
        return;
    }
    
    if (running_foreground!=-1)
    {
        process *P;
        P = malloc(sizeof(process));
            P->pid = running_foreground;
            strcpy(P->process_name, foreground->process_name);
            P->next = NULL;
            P->status = 1;
            P->process_number=number_of_processes;
            P->status=1;
            strcpy(process_names[number_of_processes], foreground->process_name);
            current = P;
            
            number_of_processes++;
        kill(running_foreground, SIGTTIN);
        kill(running_foreground, SIGTSTP);
        
            

    }
    
    
    signal(SIGTSTP, ctrl_z);
    
}