#include "shell.h"

void interpret_command(char *string)
{
    char *total_string = (char *)malloc(MAX_LENGTH_OF_COMMAND * sizeof(char));
    char *token;
    char *extra = string;

    while (token = strtok_r(extra, ";", &extra))
    {
        //printf("%s", token);
        interpret_each_command(token);
        //printf("\n"); //after completing the command
    }
    free(total_string);
}

void interpret_each_command(char *string)
{
    strip_extra_whitespaces(string);
    if (string[0] == '\0')
    {
        return;
    }

    char string_2[MAX_LENGTH_OF_COMMAND];
    strcpy(string_2, string);
    char string_1[MAX_LENGTH_OF_COMMAND];
    strcpy(string_1, string_2);
    char *extra = string_2;
    char first[50];
    strcpy(first, strtok_r(extra, " ", &extra));

    if (strcmp(first, "repeat") == 0)
    {
        execute_repeat(string_1);
        return;
    }
    else if (check_if_piping(string_1))
    {
    piping(string_1);
    return;
    }
    else if (is_built_in_command(first, string_1) != -1)
    {
        return; // the command is executed while checking if it is a builtin command
    }
    else if (is_ls_command(first, string_1))
    {
        return;
    }
    else if (strcmp(first, "jobs") == 0)
    {
        execute_jobs(string_1);
        return;
    }
     else if (strcmp(first, "fg") == 0)
    {
        execute_fg(string_1);
        return;
    } 
    else if (strcmp(first, "bg") == 0)
    {
        execute_bg(string_1);
        return;
    }

    else if (check_for_redirection(string_1) != -1)
    {
        interpret_redirection(string_1);
        return;
    }
    else
    {
        execute_background(first, string_1);
    }
}