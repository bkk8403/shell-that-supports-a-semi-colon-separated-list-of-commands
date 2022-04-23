#include "shell.h"


char buffer[1000];

void initialise()
{

    home_address = malloc(MAX_LENGTH_DIRECTORY_NAME);
    getcwd(home_address, MAX_LENGTH_DIRECTORY_NAME);
    init = 0;
    for (int i = 0; i < 100; i++)
    {
        strcpy(process_names[i], "\0");
    }
    number_of_processes=1;
    current=NULL;
    shell_pid=getpid();
    running_foreground=-1;
    foreground = malloc(sizeof(process));
}

void prompt(){
    char* user_name = malloc(MAX_LENGTH_USER_NAME);
    char* system_name = malloc(MAX_LENGTH_SYSTEM_NAME);
    directory_name = (char*)malloc(512*sizeof(char));
    directory_name_global = (char*)malloc(512*sizeof(char));
    getlogin_r(user_name,MAX_LENGTH_USER_NAME);
    gethostname(system_name, MAX_LENGTH_SYSTEM_NAME);
    getcwd(directory_name, MAX_LENGTH_DIRECTORY_NAME);

        strcpy(directory_name_global, directory_name);
   

    char colon[1000] = "~";
    if (strncmp(directory_name, home_address, strlen(home_address)) == 0)
    {
        directory_name += strlen(home_address); 
        strcat(colon,directory_name);
        strcpy(directory_name, colon);
    }
    
    /* printf("%s", directory_name);
    printf("%s\n", home_address); */
    sprintf(buffer, "<%s@%s:%s>",user_name, system_name, directory_name);
    printf("%s",buffer);
    //free(user_name);
    //free(system_name);
    //free(directory_name);
}
