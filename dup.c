#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    int fd = open("main.c", O_RDONLY);
    dup2(fd,0);
    char *array[] = { "cat", 0};
    execvp(array[0], array);
}