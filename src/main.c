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
    *argc = 0;
    char* token = strtok(line, " \n\t");

    while (token != NULL)
    {
        if (token != NULL && token[strlen(token)-1] == '\\')
        {
            char* temp = (char*) malloc(1); 
            temp[0] = '\0';

            while (token[strlen(token)-1] == '\\')
            {
                token[strlen(token)-1] = ' ';

                temp = (char*) realloc(temp, strlen(temp) + strlen(token) + 1);
                temp = strcat(temp, token);
                
                token = strtok(NULL, " \n\t");
                if (token == NULL)
                {
                    break;
                }

                if (token != NULL && token[strlen(token)-1] == '\\')
                {
                    continue;
                }
                else
                {
                    temp = (char*) realloc(temp, strlen(temp) + strlen(token) + 1);
                    temp = strcat(temp, token);
                }
            }
            argv[*argc] = strdup(temp);
            free(temp);
        }

        else if (token[0] == '\"')
        {
            char* pog = strdup(token+1);
            while (token[strlen(token)-1] != '\"')
            {
                token = strtok(NULL, " \n\t");
                strcat(strcat(argv[*argc], " "), strdup(token));
            }
            strcat(argv[*argc], strdup(pog));

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
    else if (strcmp(argv[0], "echo") == 0)
    {
        _echo(argv[1]);
    }
    else
    {
        fprintf(stdout, "%s: command not recognized\n", argv[0]);
    }
    return 0;
}


int main(void)
{
    chdir(HOME_DIR);

    char current_dir[MAX_PATH] = HOME_DIR;

    char success = EXIT_SUCCESS;

    while(success != EXIT_FAILURE) 
    {
        char line[MAX_LN_LENGTH];

        int num_args;
        char* arguments[MAX_NUM_ARGS] = {NULL};


        printf("\n(%s)\n", current_dir);
        printf("> ");

        get_input(line);
        if (parse_input(line, &num_args, arguments) == -1)
        {
            printf("Parsing failure.");
            return EXIT_FAILURE;
        }
        command_runner(num_args, arguments, current_dir);

        fflush(stdout);

        for (int i = 0; i < num_args; i++) {
            free(arguments[i]);
        }
    }

    return EXIT_SUCCESS;
}