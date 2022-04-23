#include "shell.h"

void execute_echo(char *string)
{
    char *extra_1 = string;
    char first_1[50];
    //strcpy(first_1,strtok(extra_1, " "));
    strcpy(first_1,strtok_r(extra_1, " ", &extra_1));    
    char second_1[512];
    //strcpy(first_1,strtok(NULL, " "));
    printf("%s\n",extra_1);
}

void execute_pwd(char* string)
{
    char* path = malloc(MAX_LENGTH_DIRECTORY_NAME);
    getcwd(path, MAX_LENGTH_DIRECTORY_NAME);
    printf("%s\n", path);
    free(path);

}

void exec_cd_check(char *string)
{
    
    if (chdir(string)!=0) {
        perror("chdir() failed");
        return;
    }
    strcpy(previous_command, directory_name_global);
    
}

void execute_cd(char* string)
{
    if (strcmp(string, "cd")==0)
    {
        exec_cd_check(home_address);
    }
    
    
    char *extra_2 = string;
    char first_1[50];
    char* dummy = malloc(MAX_LENGTH_OF_COMMAND);
    strcpy(dummy, home_address);
    
    strcpy(first_1,strtok_r(extra_2, " ", &extra_2));    
    char* extra_1 = malloc(MAX_LENGTH_OF_COMMAND);
    strcpy(extra_1, extra_2);

    strcpy(first_1,strtok_r(extra_2, " ", &extra_2));
    if (strcmp(extra_2,"\0")!=0)
    {
        printf("cd: too many arguments");
        return;
    }
    

    if (strncmp(extra_1, "~", 1)==0)
    {
        if (init == 0)
        {
            init = 1;
        }
        
        
        if (strcmp(extra_1,"~")==0)
        {
            chdir(home_address);
        }
        else
        {
            strcpy(extra_1, strchr(extra_1, '/'));
            strcat(dummy, extra_1);
            exec_cd_check(dummy);
        }
        
        
        
    }
    else if ((strncmp(extra_1, "..",2)==0) || (strncmp(extra_1, "/home",5)==0))
    {
        if (init == 0)
        {
            init = 1;
        }

        
        
        exec_cd_check(extra_1);
        
    }
    else if (strncmp(extra_1, "-", 1)==0)
    {

        if (init == 0)
        {
            printf("There has not been any previous command\n");
        }
        else
        {
            printf("%s\n", previous_command);
            exec_cd_check(previous_command);
        }
        
        
        
    }
    else
    {
        if (init == 0)
        {
            init = 1;
        }

        strcpy(dummy, directory_name_global);
        strcat(dummy, "/");
        strcat(dummy, extra_1);
        //printf("%s",dummy);
        exec_cd_check(dummy);
    }
    
    
    

    
}




int is_built_in_command(char* first,char* string)
{
    if (strcmp(first, "echo")==0)
    {
        execute_echo(string);
        return 1;
    }
    else if (strcmp(first, "pwd")==0)
    {
        execute_pwd(string);
        return 1;
    }
    else if (strcmp(first, "cd")==0)
    {
        execute_cd(string);
        return 1;
    }
    else if (strcmp(first, "pinfo")==0)
    {
        execute_pinfo(string);
        return 1;
    }
    else if (strcmp(first, "sig")==0)
    {
        execute_sig(string);
    }
    
    
    
    else
    {
        return -1;
    }
    
}

