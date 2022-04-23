#include "shell.h"

void display_exit_children()
{
    int stat;
    while (1)
    {
        int process_id_2 = waitpid(-1, &stat, WNOHANG | WUNTRACED);
        if (process_id_2 <= 0)
        {
            break;
        }
        if (WIFEXITED(stat) || WIFSIGNALED(stat))
        {
            process *current_proc = current;
            process *previous_proc = current;

            while (current_proc != NULL && current_proc->pid != process_id_2)
            {
                previous_proc = current_proc;
                current_proc = current_proc->next;
            }
            if (current_proc != NULL)
            {
                if (WIFEXITED(stat))
                {
                    fprintf(stderr, "%s with pid %d exited normally with status %d\n", current_proc->process_name, current_proc->pid, WEXITSTATUS(stat));
                    current_proc->status = 0;
                    //free(current_proc);
                    //number_of_processes--;
                }
                else
                {   
                    fprintf(stderr, "%s with pid %d exited abnormally with status %d\n", current_proc->process_name, current_proc->pid, WEXITSTATUS(stat));
                    current_proc->status = 0;
                }

                previous_proc->next = current_proc->next;
                //current_proc->status = 0;
                //free(current_proc);
            }
        }
    }
}