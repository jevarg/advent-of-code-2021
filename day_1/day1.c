#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    if (argc < 1) {
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        perror("Could not open file");
        return 1;
    }

    char *line = NULL;
    size_t n;
    
    int res = getline(&line, &n, file);
    int nb_of_increases = 0;
    int last_depth = -1;

    while (res && res != -1)
    {
        int nb = atoi(line);

        if (last_depth > -1 && nb > last_depth)
            ++nb_of_increases;
        last_depth = nb;

        res = getline(&line, &n, file);
    }

    if (res == -1 && errno)
    {
        perror("Could not read stream");
        fclose(file);
        return 1;
    }
    
    printf("Number of increases: %d\n", nb_of_increases);
    fclose(file);
    return 0;
}
