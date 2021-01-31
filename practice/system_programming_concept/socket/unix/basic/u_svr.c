#include "u_hdr.h"
#define BACKLOG     5

int main (int argc, char **argv) 
{
    struct sockaddr_un  addr;
    int                 sfd, clfd;
    ssize_t             num_read;
    char                buf[BUF_SIZE];

    // Create socket:
    sfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sfd == -1) {
        printf("Fail to create socket\n");
        exit(EXIT_FAILURE);
    }

    // Verify socket's namepath:
    if (strlen(SOCKET_SV_PATH) > (sizeof(addr.sun_path) - 1)) {
        printf("Invalid socket's namepath\n");
        exit(EXIT_FAILURE);
    }

    // Remove any existing file having the same namepath with server's:
    if ((remove(SOCKET_SV_PATH) == -1) && (errno != ENOENT)) {
        printf("Error line[%d]: %s\n", __LINE__, strerror(errno));
        exit(EXIT_FAILURE);
    }

    // Bind the socket to the desired address:
    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOCKET_SV_PATH, sizeof(addr.sun_path) - 1);

    printf("Bind %s\n", addr.sun_path);
    if (bind(sfd, (struct sockaddr *) &addr, sizeof(struct sockaddr_un)) == -1) {
        printf("Error line[%d]: %s\n", __LINE__, strerror(errno));
        exit(EXIT_FAILURE);
    }

    if (listen(sfd, BACKLOG) == -1) {
        printf("Error line[%d]: %s\n", __LINE__, strerror(errno));
        exit(EXIT_FAILURE);
    }

    // Handle client connections:
    while (1) {
        clfd = accept(sfd, NULL, 0);
        if (clfd == -1) {
            printf("Error line[%d]: %s\n", __LINE__, strerror(errno));
            exit(EXIT_FAILURE);
        }

        while (1) {
            num_read = read(clfd, buf, BUF_SIZE);
            if (num_read > 0) {
                if (write(STDOUT_FILENO, buf, num_read) != num_read) {
                    printf("Fail to write\n");
                    exit(EXIT_FAILURE);
                }
            } else if (num_read == -1) {
                printf("Error line[%d]: %s\n", __LINE__, strerror(errno));
                break;
            }
        }

        if (close(clfd) == -1) {
            printf("Error line[%d]: %s\n", __LINE__, strerror(errno));
        }
    }
}
