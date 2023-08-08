#include <dirent.h>

int _cd(const char* cwd, char** argv)
{
    if (argv[1] == NULL)
    {
        chdir("C:/");
    }
    else if (strcmp(argv[1], "..") == 0)
    {
        chdir("..");
    }
    else if (strcmp(argv[1], "-") == 0)
    {
        chdir(getenv("HOME"));
    }
    else if (access(argv[1], 0) == 0)
    {
        chdir(argv[1]);
    }
    else
    {
        perror("chdir");
    }

    return 0;
}