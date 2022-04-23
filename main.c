#include "shell.h"

int main()
{   
    initialise();
    
    //strcpy(read_string,read_command());
    signal(SIGINT, ctrl_c);
    signal(SIGTSTP, ctrl_z);
    while (1)
    {
        //char command_1[MAX_LENGTH_OF_COMMAND];
        display_exit_children();
        prompt();
        //read_command();
        strcpy(read_string,read_command());
        
        

        

        if (strcmp("empty",read_string)!=0)
        {
            interpret_command(read_string);
        }
        
        //dup2(1,STDOUT_FILENO);
        //dup2(0, STDIN_FILENO);
        
        
    }
    
}
