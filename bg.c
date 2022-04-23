#include "shell.h"
void execute_bg(char *string)
{
    char *token;
    char *rest = string;
    int i = 0;
    int job_number;
    char command[MAX_LENGTH_OF_COMMAND];
    while ((token = strtok_r(rest, " ", &rest)))
    {
        if (i == 1)
        {
            job_number = atoi(token);
        }
        if (i == 2)
        {
            printf("Too many arguments\n Usage: bg job_no");
            return;
        }
        i++;
    }
    if (i < 1)
    {
        printf("Too few arguments\n Usage: bg job_no");
        return;
    }

    if (job_number > number_of_processes)
    {
        printf("Job doesnt exist\n");
    }

    struct process *dummy = current;
    while (dummy->process_number != job_number)
    {
        dummy = dummy->next;
    }

    int pid_bg = dummy->pid;
    kill(pid_bg, SIGTTIN);
    kill(pid_bg, SIGCONT);    

}