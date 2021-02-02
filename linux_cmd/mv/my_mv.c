#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main (int argc, char **argv)
{
    if (argc <= 1) {
        perror("missing file operand");
        exit(EXIT_FAILURE);
    }

    if (argc == 2) {
        printf("missing file destination for %s\r\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    if (access(argv[1], F_OK) == -1) {
        printf("%s does not exist\r\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    rename(argv[1], argv[2]);
    return 0;
}
