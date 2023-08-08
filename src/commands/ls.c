#include <dirent.h>

int _ls(const char* cwd)
{
    DIR* dir = opendir(cwd);
    struct dirent* entry;

    if (dir == NULL) {
        perror("Error opening directory");
        return 1;
    }

    while ((entry = readdir(dir)) != NULL) {
        printf("%s  ", entry->d_name);
    }

    printf("\n");

    closedir(dir);

    return 0;
}