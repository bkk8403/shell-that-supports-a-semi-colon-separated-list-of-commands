#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

char* process_names[2];
int number_of_processes = 0;

int myCompare (const void * a, const void * b ) {
    const char *pa = *(const char**)a;
    const char *pb = *(const char**)b;

    return strcmp(pa,pb);
}

void execute_jobs()
{
    int stringLen = sizeof(process_names) / sizeof(char *);
    qsort(process_names, stringLen, sizeof(char *), myCompare);
    for (int i = 0; i < 100; i++)
    {
        printf("%s",process_names[i]);
    }
    
    

}

int cstring_cmp(const void *a, const void *b) 
{ 
    const char **ia = (const char **)a;
    const char **ib = (const char **)b;
    return strcmp(*ia, *ib);
	/* strcmp functions works exactly as expected from
	comparison function */ 
} 
 
/* C-string array printing function */ 
void print_cstring_array(char **array, size_t len) 
{ 
    size_t i;
 
    for(i=0; i<2; i++) 
        printf("%s | ", array[i]);
 
    putchar('\n');
} 
 
/* sorting C-strings array using qsort() example */ 
void sort_cstrings_example() 
{ 
    //char *strings[] = { "Zorro", "Alex", "Celine", "Bill", "Forest", "Dexter" };
    size_t strings_len = sizeof(process_names) / sizeof(char *);
 
    /** STRING */ 
    puts("*** String sorting...");
 
    /* print original string array */ 
    print_cstring_array(process_names, strings_len);
 
    /* sort array using qsort functions */ 
    qsort(process_names, strings_len, sizeof(char *), cstring_cmp);
 
    /* print sorted string array */ 
    print_cstring_array(process_names, strings_len);
} 
 



int main()
{
        process_names[0]=malloc(100*sizeof(char));
        process_names[1]=malloc(100*sizeof(char));
        strcpy(process_names[0],"sleep");
        strcpy(process_names[1],"gedit");
        //execute_jobs(); */
        sort_cstrings_example();
}




/* #include <stdio.h>
#include <string.h>

int main()
{

        char string[100];
        strcpy(string, "\t; \t\t");
        int j =0;
        for (int i = 0; string[i] != '\0'; i++)
        {
                
                if ((!((string[i] == ' ') || (string[i] == '\t'))||(i>0 && !(string[i-1]==' ' || string[i-1] == '\t' ))))
                {
                        if (!((string[i - 1] == ';') && ((string[i] == ' ') || (string[i] == '\t'))))
                        {
                                string[j] = string[i];
                                j++;
                        }
                }
        }
        string[j]='\0';
        printf("%s1",string);
}
 */
/* 

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>

int main(int argc, char **argv)
{
        struct dirent **namelist;
        int n;
        if (argc < 1)
        {
                exit(EXIT_FAILURE);
        }
        else if (argc == 1)
        {
                n = scandir("..", &namelist, NULL, alphasort);
        }
        else
        {
                n = scandir(argv[1], &namelist, NULL, alphasort);
        }
        if (n < 0)
        {
                perror("scandir");
                exit(EXIT_FAILURE);
        }
        else
        {
                while (n--)
                {
                        printf("%s\n", namelist[n]->d_name);
                        free(namelist[n]);
                }
                free(namelist);
        }
        exit(EXIT_SUCCESS);
} */