#include <stdio.h>
#include <io.h>

int main(void)
{
    chdir("C:/Users/Charles/Desktop/CS Projects");

    char strin[256];
    getcwd(strin, 256);

    printf("%s", strin);
    // printf("%d", chdir(""));

    return 0;
}