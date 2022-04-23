#include "shell.h"

void execute_repeat(char *string)
{
    char *extra_1 = string;
    char first_1[50];
    //strcpy(first_1,strtok(extra_1, " "));
    strcpy(first_1,strtok_r(extra_1, " ", &extra_1));

    char second_1[512];
    strcpy(second_1,strtok_r(extra_1, " ", &extra_1));
    
    for (int i = 0; i < atoi(second_1); i++)
    {
        interpret_each_command(extra_1);
    }
    
    
}