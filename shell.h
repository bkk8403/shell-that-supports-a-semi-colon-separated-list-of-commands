#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <grp.h>
#include <pwd.h>
#include <time.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAX_LENGTH_USER_NAME 512
#define MAX_LENGTH_SYSTEM_NAME 512
#define MAX_LENGTH_DIRECTORY_NAME 512
#define MAX_LENGTH_OF_COMMAND 512

//initialisations for shell
char read_string[512];
char *home_address;
char* directory_name;
char* directory_name_global;


//initailisations for built_in_commands
int init;

char previous_command[MAX_LENGTH_OF_COMMAND];

//function declarations
void initialise();
void prompt();
char* read_command();
void interpret_command(char* string);
void display_exit_children();
void interpret_each_command(char* string);
void execute_repeat(char *string);
void interpret_redirection(char *string);
int check_for_redirection(char* read_string);
char* strip_extra_whitespaces(char* string);
void piping(char* string);
int check_if_piping(char *string);
void execute_jobs(char *string);
void execute_fg(char *string);
void execute_bg(char *string);
void execute_sig(char* string);



//function declarations of built_in_commands.c
void execute_echo(char *string);
int is_built_in_command(char* first,char* string);
void execute_cd(char* string);
char* execute_pinfo(char *string);
void kjob(char *string);

//function declrarations of ls command
int is_ls_command(char* first, char* string);

//function declarations for fgbgprocesses.c
int is_background(char* first, char* string);
void execute_background(char* first, char* string);
char* process_status_pinfo(char* string);
struct process
{
    int pid;
    char process_name[512];
    struct process *next;
    int status;
    int process_number;
    int printed;
};
char process_status[50];
struct process *current;

typedef struct process process;

char process_names[100][MAX_LENGTH_OF_COMMAND];
int number_of_processes;

int shell_pid;
int running_foreground;


void ctrl_c(int sig_num);

void ctrl_z(int sig_num);
process* foreground;