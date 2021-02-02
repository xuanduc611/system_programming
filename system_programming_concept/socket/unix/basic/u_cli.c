#include "u_hdr.h"

int main (int argc, char *argv[]) 
{
    struct  sockaddr_un addr;
    int                 sfd;
    ssize_t             num_read;
    char                buf[BUF_SIZE];

    // Create socket:
    sfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sfd == -1) {
        printf("Fail to create socket\n");
        exit(EXIT_FAILURE);
    }

    // Construct server address:
    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOCKET_SV_PATH, sizeof(addr.sun_path) - 1);

    // Connect to server:
    if (connect(sfd, (struct sockaddr *) &addr, sizeof(struct sockaddr_un)) == -1) {
        printf("Fail to connect\n");
        exit(EXIT_FAILURE);
    }

    // * Work with server in a infinite loop:
    // * 1) Get input from STDIN
    // * 2) Send what got at (1) to Server
    while (1) {
        num_read = read(STDIN_FILENO, buf, BUF_SIZE);
        if (num_read > 0) {
            if (write(sfd, buf, num_read) != num_read) {
                printf("Fail to send data to server\n");
                exit(EXIT_FAILURE);
            }
        } else if (num_read == -1) {
            break;
        }
    }

    exit(EXIT_SUCCESS);
}
