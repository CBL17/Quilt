#include <stdio.h> 
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <Windows.h>

#include "commands\commands.h"

#define MAX_LN_LENGTH 512
#define MAX_NUM_ARGS 10
#define HOME_DIR "C:/Users/Charles/Desktop/CS Projects"

int get_input(char* line)
{
    fgets(line, MAX_LN_LENGTH, stdin);

    return 0;
}

int parse_input(char* line, int* argc, char** argv)
{
    char* token = strtok(line, " \n\t");
    *argc = 0;

    while (token != NULL)
    {
        if (token[strlen(token)-1] == '\\')
        {
            token[strlen(token)-1] = '\0';
            argv[*argc] = strcat(strcat(strdup(token), " "), strtok(NULL, " \n\t")); // leave space in between tokens
        } 
        else
        {
            argv[*argc] = strdup(token);
        }
        token = strtok(NULL, " \n\t");

        (*argc)++;
    }

    return 0;
}


int command_runner(const int argc, char** argv, char* current_dir)
{
    if (argv[0] == NULL)
    {
        exit(1);
    }
    if (strcmp(argv[0], "ls") == 0)
    {
        _ls(current_dir);
    } 
    else if (strcmp(argv[0], "pwd") == 0)
    {
        _pwd(current_dir);
    }
    else if (strcmp(argv[0], "cd") == 0)
    {
        _cd(current_dir, argv);
    }  
    else
    {
        printf("%s: command not recognized\n", argv[0]);
    }
    return 0;
}


int main(void)
{
    chdir(HOME_DIR);

    char current_dir[MAX_PATH] = HOME_DIR;
    SetEnvironmentVariable("HOME", HOME_DIR);

    char success = EXIT_SUCCESS;

    while(success != EXIT_FAILURE) 
    {
        char line[MAX_LN_LENGTH];
        int num_args;
        char* arguments[MAX_NUM_ARGS] = {NULL};

        DWORD pathSize = GetFullPathName(".", MAX_PATH, current_dir, NULL);

        if (pathSize > MAX_PATH)
        {
            perror("Path name too big");
        }

        printf("\n(%s)\n", current_dir);
        printf("> ");

        get_input(line);
        parse_input(line, &num_args, arguments);
        command_runner(num_args, arguments, current_dir);

        for (int i = 0; i < num_args; i++) {
            free(arguments[i]);
        }
    }

    return 0;
}