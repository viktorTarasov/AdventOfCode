#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int trees = 0, offs = 0, sz = 0;

    if (argc < 2)   {
        printf("Usage: %s <input data file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    fp = fopen(argv[1], "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    if ((read = getline(&line, &len, fp)) == -1)
        exit(EXIT_FAILURE);

    sz = read - 1;
    offs = 3;
    while ((read = getline(&line, &len, fp)) != -1) {
        if (read != sz + 1)
            exit(EXIT_FAILURE);

        if (*(line + (offs%sz)) == '#')
            trees++;
        offs += 3;
    }

    printf("Trees %d\n", trees);
    fclose(fp);
    if (line)
        free(line);
    exit(EXIT_SUCCESS);
}

