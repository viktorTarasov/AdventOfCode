#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

struct task {
    int dx;
    int dy;
};

struct task tasks[] = {{1,1}, {3,1}, {5,1}, {7,1}, {1,2}};

int main(int argc, char *argv[])
{
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    long int res = 1l;

    if (argc < 2)   {
        printf("Usage: %s <input data file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    fp = fopen(argv[1], "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    for (int tt=0; tt < sizeof(tasks)/sizeof(tasks[0]); tt++)   {
        int trees = 0, offs = 0, sz = 0; 

        fseek(fp, 0, SEEK_SET);
        if ((read = getline(&line, &len, fp)) == -1)
            exit(EXIT_FAILURE);
        sz = read - 1;

        do   {
            for (int rr = 0; rr < tasks[tt].dy; rr++)   {
                read = getline(&line, &len, fp);
                if (read == -1)
                    break;
                if (read != sz + 1)
                    exit(EXIT_FAILURE);
            }

            if (read == -1)
                break;

            offs += tasks[tt].dx;
            if (*(line + (offs%sz)) == '#')
                trees++;
        } while (1);

        res *= trees;
        printf("Trees %d; res:%ld\n", trees, res);
    }

    fclose(fp);

    if (line)
        free(line);

    exit(EXIT_SUCCESS);
}

