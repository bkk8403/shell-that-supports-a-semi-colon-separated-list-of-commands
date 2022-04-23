#include "shell.h"

int check_for_redirection(char *read_string)
{
    for (int i = 0; i < strlen(read_string); i++)
    {
        if ((read_string[i] == '<') || (read_string[i] == '>'))
        {
            return 1;
        }
    }
    return -1;
}

void interpret_redirection(char *string)
{
    char *token;
    char *rest = string;
    int original_input = dup(STDIN_FILENO);
    int original_output = dup(STDOUT_FILENO);
    char chunks[100][MAX_LENGTH_OF_COMMAND];
    int i = 0;
    char changed_string_input[MAX_LENGTH_OF_COMMAND] = {'\0'};
    char changed_string_output[MAX_LENGTH_OF_COMMAND] = {'\0'};

    while ((token = strtok_r(rest, " ", &rest)))
    {
        strcpy(chunks[i], token);
        i++;
    }

    int fd_input, fd_output;
    int check_input = -1;
    int check_output = -1;
    for (int k = 0; k < i; k++)
    {
        if (strcmp(chunks[k], "<") == 0)
        {
            strcpy(chunks[k],"");
            check_input = k;
            if (chunks[k + 1])
            {
                fd_input = open(chunks[k + 1], O_RDONLY);
                strcpy(chunks[k+1],"");
                if (fd_input < 0)
                {
                    perror("Error opening file");
                    return;
                }
                else
                {
                    dup2(fd_input, STDIN_FILENO);
                    close(fd_input);
                }
            }
            else
            {
                printf("Invalid syntax");
            }

            
            if (check_input != -1)
            {
                for (int h = 0; h < check_input; h++)
                {
                    //if (h!=check_input)
                    //{
                    strcat(changed_string_input, chunks[h]);
                    strcat(changed_string_input, " ");
                    strcpy(chunks[h],"");
                    //}
                }
                changed_string_input[strlen(changed_string_input) - 1] = '\0';
            }

            //printf("%s",changed_string);
            
        }
        if (strcmp(chunks[k], ">") == 0 || strcmp(chunks[k], ">>") == 0)
        {
            check_output = k;
            if (chunks[k + 1])
            {   
                if (strcmp(chunks[k],">>")==0)
                {
                    fd_output = open(chunks[k + 1], O_CREAT | O_APPEND | O_WRONLY, S_IRUSR | S_IWUSR);
                    
                }
                else
                {
                    fd_output = open(chunks[k + 1], O_CREAT | O_TRUNC | O_APPEND | O_WRONLY, S_IRUSR | S_IWUSR);
                    
                }
                
                
                if (fd_output < 0)
                {
                    perror("Error opening file");
                    return;
                }
                else
                {
                    dup2(fd_output, STDOUT_FILENO);
                    close(fd_output);
                }
            }
            else
            {
                printf("Invalid syntax");
            }
            
            if (check_output != -1)
            {
                for (int h = 0; h < check_output; h++)
                {
                    //if (h!=check_input)
                    //{
                    strcat(changed_string_output, chunks[h]);
                    strcat(changed_string_output, " ");
                    //}
                }
                changed_string_output[strlen(changed_string_output) - 1] = '\0';
            }            

            
        }
    }
    interpret_each_command(changed_string_input);
           
    interpret_each_command(changed_string_output);
    //printf("%s",changed_string_input);
    //printf("%s",changed_string_output);
            dup2(original_output ,STDOUT_FILENO);
             dup2(original_input, STDIN_FILENO);
}