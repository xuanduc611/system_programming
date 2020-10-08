#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    FILE *fp;
    char c;

    if (argc <= 1) {
        perror("my_cat: No such file or directory");
        exit(EXIT_FAILURE);
    }

    fp = fopen(argv[1], "r");
    if (fp != NULL) {
        c = getc(fp);
        while (c != EOF) {
            putchar(c);
            c = getc(fp);
        }
    } else {
        perror("my_cat: No such file or directory");
        exit(EXIT_FAILURE);
    }

    if (feof(fp)) {
        exit(EXIT_SUCCESS);
    } else {
        perror("my_cat: Can not reach the end of file");
        exit(EXIT_FAILURE);
    }
}
