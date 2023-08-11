#include <stdio.h>

int _echo(const char* string)
{
    if (string == NULL)
    {
        printf("No argument provided!\n");

        return 1;
    }
    printf("%s\n", string);

    return 0;
}