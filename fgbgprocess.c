#include "shell.h"

int back_ground = 0;
int counter = 0;

int is_background(char *first, char *string)
{
    if (string[strlen(string) - 1] == '&')
    {
        back_ground = 1;
        return 1;
    }
    else
    {
        return 0;
    }
}

void execute_background(char *first, char *string)
{
    back_ground = is_background(first, string);
    int length = strlen(string);
    if (back_ground == 1)
    {
        string[strlen(string) - 1] = '\0';
    }

    char *token_array[10];
    char *token;
    char *rest = string;
    int i = 0;
    int k;
    while ((token = strtok_r(rest, " ", &rest)))
    {
        token_array[i] = malloc(MAX_LENGTH_OF_COMMAND);
        strcpy(token_array[i++], token);
    }
    //strcpy(token_array[i], string);
    token_array[i] = NULL;

    int pid = fork();

    if (pid == 0)
    {
        if (back_ground == 1)
            setpgid(0, 0);
        int checkk = execvp(token_array[0], token_array);
        if (checkk == -1)
        {
            perror("no command");
        }

        exit(0);
    }
    else
    {
        if (back_ground == 0)
        {
            foreground->pid=pid;
            strcpy(foreground->process_name,token_array[0]);
            running_foreground=pid;
            waitpid(pid, &k, WUNTRACED);
            running_foreground=-1;
        }
        else
        {
            process *P;
            P = malloc(sizeof(process));
            P->pid = pid;
            strcpy(P->process_name, token_array[0]);
            P->next = current;
            P->status = 1;
            P->process_number=number_of_processes;
            current = P;
            
            //struct process *dummy = current;
            //struct process *previous = dummy;
            


            /* while (dummy != NULL)
            {
                if (strcmp(dummy->process_name, P->process_name) <= 0)
                {
                    previous = dummy;
                    dummy = dummy->next;
                    continue;
                }
                else
                {
                    previous->next = P;
                    P->next = dummy;
                    break;
                }
            }
            if (dummy==NULL)
            {
                previous->next=P;
                P->next = NULL;
            } */
            
            //current=current->next;
            
            counter++;
            printf("%d\n", pid);
            strcpy(process_names[number_of_processes], token_array[0]);
            number_of_processes++;
            //printf("%s  1", process_names[number_of_processes - 1]);
        }
    }
}

char* execute_pinfo(char *string)
{
    
    char *token;
    char *rest = string;
    int count = 0;
    int process_id_1;
    char process_id[100];
    while ((token = strtok_r(rest, " ", &rest)))
    {
        if (count == 1)
        {
            if (token != NULL)
            {
                sprintf(process_id, "%s", token);
            }
        }

        count++;
    }

    if (count == 1)
    {

        {
            process_id_1 = getpid();
        }

        sprintf(process_id, "%d", process_id_1);
    }

    char file_path[512];
    sprintf(file_path, "/proc/%s/status", process_id);

    FILE *file_pinfo = fopen(file_path, "r");
    if (file_pinfo == NULL)
    {
        perror(file_path);
        return "failed";
    }

    printf("pid -- %s\n", process_id);
    size_t n = 0;
    ssize_t ret;
    char **first_elem = &string;
    ret = getline(first_elem, &n, file_pinfo);

    int s = 0;
    int count_1 = 0;
    int c;
    char string_1[50];
    while (ret != -1)
    {

        if (strncmp("VmSize", string, 6) == 0)
        {
            printf("Memory -- ");
            c = 7;
            while (string[c] != 0)
            {
                string_1[count_1] = string[c];
                c++;
                count_1++;
            }
            string_1[count_1] = '\0';
            //printf("%s\n", string);
            printf("%s\t{Virtual Memory}\n", string_1);
            count_1 = 0;
        }

        if (strncmp("State", string, 5) == 0)
        {
            printf("Process Status -- ");
            c = 7;
            while (string[c] != 0)
            {
                string_1[count_1] = string[c];
                c++;
                count_1++;
            }
            string_1[count_1] = '\0';
            printf("%s", string_1);
            count_1 = 0;
            strcpy(process_status, string_1);
        }

        ret = getline(first_elem, &n, file_pinfo);
    }
    fclose(file_pinfo);

    sprintf(file_path, "/proc/%s/exe", process_id);

    printf("Executable path -- ");
    count_1 = readlink(file_path, string_1, 512);
    string_1[count_1] = '\0';
    printf("%s\n", string_1);
    return process_status;
}


char* process_status_pinfo(char* string)
{
    
    char *token;
    char *rest = string;
    int count = 0;
    int process_id_1;
    char process_id[100];
    while ((token = strtok_r(rest, " ", &rest)))
    {
        if (count == 1)
        {
            if (token != NULL)
            {
                sprintf(process_id, "%s", token);
            }
        }

        count++;
    }

    if (count == 1)
    {

        {
            process_id_1 = getpid();
        }

        sprintf(process_id, "%d", process_id_1);
    }

    char file_path[512];
    sprintf(file_path, "/proc/%s/status", process_id);

    FILE *file_pinfo = fopen(file_path, "r");
    if (file_pinfo == NULL)
    {
        perror(file_path);
        return "failed";
    }

    //printf("pid -- %s\n", process_id);
    size_t n = 0;
    ssize_t ret;
    char **first_elem = &string;
    ret = getline(first_elem, &n, file_pinfo);

    int s = 0;
    int count_1 = 0;
    int c;
    char string_1[50];
    while (ret != -1)
    {

        if (strncmp("VmSize", string, 6) == 0)
        {
            //printf("Memory -- ");
            c = 7;
            while (string[c] != 0)
            {
                string_1[count_1] = string[c];
                c++;
                count_1++;
            }
            string_1[count_1] = '\0';
            //printf("%s\n", string);
            //printf("%s\t{Virtual Memory}\n", string_1);
            count_1 = 0;
        }

        if (strncmp("State", string, 5) == 0)
        {
            //printf("Process Status -- ");
            c = 7;
            while (string[c] != 0)
            {
                string_1[count_1] = string[c];
                c++;
                count_1++;
            }
            string_1[count_1] = '\0';
            //printf("%s", string_1);
            count_1 = 0;
            strcpy(process_status, string_1);
        }

        ret = getline(first_elem, &n, file_pinfo);
    }
    fclose(file_pinfo);
    return process_status;
}
