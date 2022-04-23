#include "shell.h"

int is_ls_command(char *first, char *string)
{
    struct dirent **namelist;
    int n;
    char *extra = string;
    char *token;
    int l = 0;
    int a = 0;
    int j = 0;
    int k = 0;
    int h = 0;
    char dir_name[10][MAX_LENGTH_OF_COMMAND] = {'\0'};

    struct stat stats;
    struct passwd *username;
    struct group *group_id;
    struct tm *time_stamp;
    char outstr[300];
    char dummy[100];
    if (strcmp(first, "ls") == 0)
    {
        if (strcmp(string, "ls") == 0 || strcmp(string, "ls .") == 0)
        {
            n = scandir(".", &namelist, NULL, alphasort);

            while ((n--) > 0)
            {
                if (namelist[n]->d_name[0] != '.')
                {
                    printf("%s\n", namelist[n]->d_name);
                }

                free(namelist[n]);
            }
        }
        else
        {
            while ((token = strtok_r(extra, " ", &extra)))
            {
                if (strcmp(token, "..") == 0)
                {
                    n = scandir("..", &namelist, NULL, alphasort);
                    h = 1;
                    j = 1;
                    while ((n--) > 0)
                    {
                        if (namelist[n]->d_name[0] != '.')
                        {
                            printf("%s\n", namelist[n]->d_name);
                        }

                        free(namelist[n]);
                    }
                }

                if (strcmp(token, "~") == 0)
                {
                    n = scandir(home_address, &namelist, NULL, alphasort);
                    h = 1;
                    j = 1;
                    while ((n--) > 0)
                    {
                        if (namelist[n]->d_name[0] != '.')
                        {
                            printf("%s\n", namelist[n]->d_name);
                        }

                        free(namelist[n]);
                    }
                }

                if (strcmp(token, "-l") == 0)
                {
                    l = 1;
                    j = 1;
                }
                if (strcmp(token, "-a") == 0)
                {
                    a = 1;
                    j = 1;
                }
                if ((strcmp(token, "-la") == 0) || (strcmp(token, "-al") == 0))
                {
                    l = 1;
                    a = 1;
                    j = 1;
                }
                if ((strcmp(token, "ls") != 0) && (j == 0))
                {
                    strcpy(dir_name[k], token);
                    k++;
                }
                j = 0;
            }
            if (k == 0 && h == 0)
            {

                n = scandir(directory_name_global, &namelist, NULL, alphasort);
                if ((l == 0))
                {
                    if (a == 0)
                    {
                        while ((n--) > 0)
                        {
                            if (namelist[n]->d_name[0] != '.')
                            {
                                printf("%s\n", namelist[n]->d_name);
                            }

                            free(namelist[n]);
                        }
                    }
                    else
                    {
                        while (n--)
                        {
                            printf("%s\n", namelist[n]->d_name);
                            free(namelist[n]);
                        }
                    }
                }
                else
                {
                    if (a == 0)
                    {

                        while (n--)
                        {
                            if (namelist[n]->d_name[0] != '.')
                            {
                                if (stat(namelist[n]->d_name, &stats) == -1)
                                {
                                    perror("stat");
                                    return -1;
                                }

                                printf((S_ISDIR(stats.st_mode)) ? "d" : "-");
                                printf((stats.st_mode & S_IRUSR) ? "r" : "-");
                                printf((stats.st_mode & S_IWUSR) ? "w" : "-");
                                printf((stats.st_mode & S_IXUSR) ? "x" : "-");
                                printf((stats.st_mode & S_IRGRP) ? "r" : "-");
                                printf((stats.st_mode & S_IWGRP) ? "w" : "-");
                                printf((stats.st_mode & S_IXGRP) ? "x" : "-");
                                printf((stats.st_mode & S_IROTH) ? "r" : "-");
                                printf((stats.st_mode & S_IWOTH) ? "w" : "-");
                                printf((stats.st_mode & S_IXOTH) ? "x " : "- ");
                                printf("%li ", stats.st_nlink);

                                username = getpwuid(stats.st_uid);
                                group_id = getgrgid(stats.st_gid);
                                
                                
                                {
                                    printf("%s ", username->pw_name);
                                }

                                
                                
                                {
                                    printf("%s ", group_id->gr_name);
                                }

                                //file size
                                printf("%5ld ", stats.st_size);

                                time_t time = stats.st_mtime;
                                time_stamp = localtime(&time);
                                if (time_stamp == NULL)
                                {
                                    perror("localtime");
                                }
                                strftime(outstr, sizeof(outstr), "%b %d %R", time_stamp);
                                printf("%s ", outstr);

                                //file name
                                printf("%s\n", namelist[n]->d_name);
                            }
                        }
                    }
                    else
                    {

                        while (n--)
                        {

                            {
                                if (stat(namelist[n]->d_name, &stats) == -1)
                                {
                                    perror("stat");
                                    return -1;
                                }

                                printf((S_ISDIR(stats.st_mode)) ? "d" : "-");
                                printf((stats.st_mode & S_IRUSR) ? "r" : "-");
                                printf((stats.st_mode & S_IWUSR) ? "w" : "-");
                                printf((stats.st_mode & S_IXUSR) ? "x" : "-");
                                printf((stats.st_mode & S_IRGRP) ? "r" : "-");
                                printf((stats.st_mode & S_IWGRP) ? "w" : "-");
                                printf((stats.st_mode & S_IXGRP) ? "x" : "-");
                                printf((stats.st_mode & S_IROTH) ? "r" : "-");
                                printf((stats.st_mode & S_IWOTH) ? "w" : "-");
                                printf((stats.st_mode & S_IXOTH) ? "x " : "- ");
                                printf("%li ", stats.st_nlink);

                                username = getpwuid(stats.st_uid);
                                group_id = getgrgid(stats.st_gid);
                                
                                {
                                    printf("%s ", username->pw_name);
                                }

                               
                                {
                                    printf("%s ", group_id->gr_name);
                                }

                                //file size
                                printf("%5ld ", stats.st_size);

                                time_t time = stats.st_mtime;
                                time_stamp = localtime(&time);
                                if (time_stamp == NULL)
                                {
                                    perror("localtime");
                                }
                                strftime(outstr, sizeof(outstr), "%b %d %R", time_stamp);
                                printf("%s ", outstr);

                                //file name
                                printf("%s\n", namelist[n]->d_name);
                            }
                        }
                    }
                }
            }
            else
            {
                for (int i = 0; i < k; i++)
                {   if (k > 1 && l==0)
                    {
                        printf("%s:\n", dir_name[i]);

                    }
                

                    n = scandir(dir_name[i], &namelist, NULL, alphasort);
                    if (n == -1)
                    {
                        if (l == 0)
                        {
                            if(k==1)
                            {
                                printf("%s", dir_name[i]);
                            }
                        }
                        else
                        {

                            if (stat(dir_name[i], &stats) == -1)
                            {
                                perror("stat 1:");
                                return -1;
                            }

                            printf((S_ISDIR(stats.st_mode)) ? "d" : "-");
                            printf((stats.st_mode & S_IRUSR) ? "r" : "-");
                            printf((stats.st_mode & S_IWUSR) ? "w" : "-");
                            printf((stats.st_mode & S_IXUSR) ? "x" : "-");
                            printf((stats.st_mode & S_IRGRP) ? "r" : "-");
                            printf((stats.st_mode & S_IWGRP) ? "w" : "-");
                            printf((stats.st_mode & S_IXGRP) ? "x" : "-");
                            printf((stats.st_mode & S_IROTH) ? "r" : "-");
                            printf((stats.st_mode & S_IWOTH) ? "w" : "-");
                            printf((stats.st_mode & S_IXOTH) ? "x " : "- ");
                            printf("%li ", stats.st_nlink);

                            username = getpwuid(stats.st_uid);
                            group_id = getgrgid(stats.st_gid);
                            
                            {
                                printf("%s ", username->pw_name);
                            }

                            
                            {
                                printf("%s ", group_id->gr_name);
                            }

                            //file size
                            printf("%5ld ", stats.st_size);

                            time_t time = stats.st_mtime;
                            time_stamp = localtime(&time);
                            
                            strftime(outstr, sizeof(outstr), "%b %d %R", time_stamp);
                            printf("%s", outstr);

                            printf(" %s\n", dir_name[i]);
                        }
                        continue;
                    }

                    if ((l == 0))
                    {
                        if (a == 0)
                        {
                            while ((n--) > 0)
                            {
                                if (namelist[n]->d_name[0] != '.')
                                {
                                    printf("%s\n", namelist[n]->d_name);
                                }

                                free(namelist[n]);
                            }
                        }
                        else
                        {
                            while (n--)
                            {
                                printf("%s\n", namelist[n]->d_name);
                                free(namelist[n]);
                            }
                        }
                    }
                    else
                    {
                        if (a == 0)
                        {

                            while (n--)
                            {
                                strcat(dummy, directory_name_global);
                                strcat(dummy, "/");
                                strcat(dummy, dir_name[i]);
                                strcat(dummy, "/");
                                if (namelist[n]->d_name[0] != '.')
                                {
                                    strcat(dummy, namelist[n]->d_name);
                                    printf("%s\n", dummy);

                                    if (stat(dummy, &stats) == -1)
                                    {
                                        perror("stat 1:");
                                        return -1;
                                    }

                                    printf((S_ISDIR(stats.st_mode)) ? "d" : "-");
                                    printf((stats.st_mode & S_IRUSR) ? "r" : "-");
                                    printf((stats.st_mode & S_IWUSR) ? "w" : "-");
                                    printf((stats.st_mode & S_IXUSR) ? "x" : "-");
                                    printf((stats.st_mode & S_IRGRP) ? "r" : "-");
                                    printf((stats.st_mode & S_IWGRP) ? "w" : "-");
                                    printf((stats.st_mode & S_IXGRP) ? "x" : "-");
                                    printf((stats.st_mode & S_IROTH) ? "r" : "-");
                                    printf((stats.st_mode & S_IWOTH) ? "w" : "-");
                                    printf((stats.st_mode & S_IXOTH) ? "x " : "- ");
                                    printf("%li ", stats.st_nlink);

                                    username = getpwuid(stats.st_uid);
                                    group_id = getgrgid(stats.st_gid);
                                    
                                    {
                                        printf("%s ", username->pw_name);
                                    }

                                    
                                    {
                                        printf("%s ", group_id->gr_name);
                                    }

                                    //file size
                                    printf("%5ld ", stats.st_size);

                                    time_t time = stats.st_mtime;
                                    time_stamp = localtime(&time);
                                    if (time_stamp == NULL)
                                    {
                                        perror("localtime");
                                    }
                                    strftime(outstr, sizeof(outstr), "%b %d %R", time_stamp);
                                    printf("%s ", outstr);

                                    //file name
                                    printf("%s\n", namelist[n]->d_name);
                                }
                                strcpy(dummy, "\0");
                            }
                        }
                        else
                        {

                            while (n--)
                            {

                                {
                                    strcat(dummy, directory_name_global);
                                    strcat(dummy, "/");
                                    strcat(dummy, dir_name[i]);
                                    strcat(dummy, "/");
                                    strcat(dummy, namelist[n]->d_name);
                                    printf("%s\n", dummy);
                                    if (stat(dummy, &stats) == -1)
                                    {
                                        perror("stat F");
                                        return -1;
                                    }

                                    printf((S_ISDIR(stats.st_mode)) ? "d" : "-");
                                    printf((stats.st_mode & S_IRUSR) ? "r" : "-");
                                    printf((stats.st_mode & S_IWUSR) ? "w" : "-");
                                    printf((stats.st_mode & S_IXUSR) ? "x" : "-");
                                    printf((stats.st_mode & S_IRGRP) ? "r" : "-");
                                    printf((stats.st_mode & S_IWGRP) ? "w" : "-");
                                    printf((stats.st_mode & S_IXGRP) ? "x" : "-");
                                    printf((stats.st_mode & S_IROTH) ? "r" : "-");
                                    printf((stats.st_mode & S_IWOTH) ? "w" : "-");
                                    printf((stats.st_mode & S_IXOTH) ? "x " : "- ");
                                    printf("%li ", stats.st_nlink);

                                    username = getpwuid(stats.st_uid);
                                    group_id = getgrgid(stats.st_gid);
                                    
                                    
                                    {
                                        printf("%s ", username->pw_name);
                                    }

                                    
                                    
                                    {
                                        printf("%s ", group_id->gr_name);
                                    }

                                    //file size
                                    printf("%5ld ", stats.st_size);

                                    time_t time = stats.st_mtime;
                                    time_stamp = localtime(&time);
                                    if (time_stamp == NULL)
                                    {
                                        perror("localtime");
                                    }
                                    strftime(outstr, sizeof(outstr), "%b %d %R", time_stamp);
                                    printf("%s ", outstr);

                                    //file name
                                    printf("%s\n", namelist[n]->d_name);
                                }
                                strcpy(dummy, "\0");
                            }
                        }
                    }
                }
            }
      
      
        }

        return 1;
    }else
    {
        return 0;
    }
    
}