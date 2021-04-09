#include "tcp_stream_hdr.h"

static void cli_proc(int fd);

static void cli_proc(int fd)
{
    char    msg_buf[MAX];
    int     n;

    while (1) {
        bzero(msg_buf, sizeof(msg_buf));

        printf("Enter msg: ");
        n = 0;
        while((msg_buf[n++] = getchar()) != '\n');

        write(fd, msg_buf, sizeof(msg_buf));
        bzero(msg_buf, sizeof(msg_buf));
        read(fd, msg_buf, sizeof(msg_buf));
        printf("Response from server: %s\n", msg_buf);
    }
}

int main(int argc, char** argv)
{
    int             confd;
    SOCKADDR_IN_t   svr_addr;

    // Create socket:
    confd = socket(AF_INET, SOCK_STREAM, 0);
    if (confd == -1) {
        printf("%s, line %d: Fail to create socket\n", __FUNCTION__, __LINE__);
        exit(EXIT_FAILURE);
    }

    // Connect client socket to server:
    svr_addr.sin_family = AF_INET;
    svr_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    svr_addr.sin_port = htons(PORT);

    if (connect(confd, (SOCKADDR_t *)&svr_addr, sizeof(SOCKADDR_IN_t)) != 0) {
        printf("%s, line %d: Fail to connect to server\n", __FUNCTION__, __LINE__);
        exit(EXIT_FAILURE);
    }

    // Send data to server:
    cli_proc(confd);

    // Close socket after working with server:
    close(confd);
}

