#include "shell.h"

void execute_fg(char *string)
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
            printf("Too many arguments\n Usage: fg job_no");
            return;
        }
        i++;
    }
    if (i < 1)
    {
        printf("Too few arguments\n Usage: fg job_no");
        return;
    }

    if (job_number > number_of_processes)
    {
        printf("Job doesnt exist\n");
    }
    else
    {
        struct process *dummy = current;
        while (dummy->process_number != job_number)
        {
            dummy = dummy->next;
        }
        char pid_s[50];
        sprintf(pid_s,"%d",dummy->pid);
        strcpy(command, "/proc/");
        strcat(command, pid_s);
        strcat(command, "/stat");

        FILE *fd;
        if ((fd = fopen(command, "r")) == NULL)
        {
            printf("The process is terminated.\n");
        }
        else
        {
            foreground->pid=dummy->pid;
            strcpy(foreground->process_name,dummy->process_name);
            running_foreground=dummy->pid;
            kill(dummy->pid, SIGCONT);
            int k;
            waitpid(dummy->pid, &k, WUNTRACED);
            running_foreground=-1;
            
            //waitpid(-1, NULL, WUNTRACED);
        }
        
    }
}