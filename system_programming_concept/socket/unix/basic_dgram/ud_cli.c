#include "ud_hdr.h"

#define IN_BUF_SIZE     200

int main(int argc, char **argv)
{
    struct sockaddr_un  svr_addr, cli_addr;
    int                 sfd, i;
    ssize_t             num_rw;
    socklen_t           svr_addr_len;
    char                sock_buf[SOCK_BUF_SIZE];
    char                in_buf[IN_BUF_SIZE];

    // Create sockets:
    sfd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (sfd == -1) {
        printf("Error line|%d|: %s", __LINE__, strerror(errno));
        exit(EXIT_FAILURE);
    }

    // ! In Unix domain, the client needs to assign an address to its socket
    // ! if it wants to RECEIVE datagrams sent by server.
    memset(&cli_addr, 0, sizeof(struct sockaddr_un));
    cli_addr.sun_family = AF_UNIX;
    snprintf(cli_addr.sun_path, sizeof(cli_addr.sun_path), \
            "/tmp/dxduc/ud_cli.%ld", (long)getpid());
    if (bind(sfd, (struct sockaddr *) &cli_addr, sizeof(struct sockaddr_un)) == -1) {
        printf("Error line|%d|: %s\n", __LINE__, strerror(errno));
        exit(EXIT_FAILURE);
    }

    // Construct server's address:
    memset(&svr_addr, 0, sizeof(struct sockaddr_un));
    svr_addr.sun_family = AF_UNIX;
    strncpy(svr_addr.sun_path, SOCKET_SV_PATH, sizeof(svr_addr.sun_path) - 1);

    printf("Client is ready to run\n");
    while (1) {
        printf("Enter new msg: ");
        fflush(stdout); // * clear the output buffer and move the buffered data to output (a.k.a console in this case)
        memset(in_buf, 0, sizeof(in_buf));
        memset(sock_buf, 0, sizeof(sock_buf));
        num_rw = read(STDIN_FILENO, in_buf, IN_BUF_SIZE);

        // Remove '\n' and '\r' in input:
        for (i = 0; i < IN_BUF_SIZE; i++) {
            if ((in_buf[i] == '\r') || (in_buf[i] == '\n')) {
                in_buf[i] = 0x0;
            }
        }

        printf("Msg to server: |%s|, len = %ld, num_rw = %ld\n", in_buf, strlen(in_buf), num_rw);
        svr_addr_len = sizeof(struct sockaddr_un);
        if (num_rw > 0) {
            // Send msg to server:
            if (sendto(sfd, in_buf, strlen(in_buf), 0, (struct sockaddr *) &svr_addr, svr_addr_len) != strlen(in_buf)) {
                printf("Error line|%d|: %s\n", __LINE__, strerror(errno));
                exit(EXIT_FAILURE);
            }
        } else if (num_rw == 0) {
            printf("Nothing to send to server\n");
            continue;
        } else if (num_rw == -1) {
            printf("Error line|%d|: %s\n", __LINE__, strerror(errno));
            exit(EXIT_FAILURE);
        }

        // Read response from server
        num_rw = recvfrom(sfd, sock_buf, SOCK_BUF_SIZE, 0, (struct sockaddr *) &svr_addr, &svr_addr_len);
        if (num_rw == -1) {
            printf("Error line|%d|, %s", __LINE__, strerror(errno));
            exit(EXIT_FAILURE);
        } else {
            printf("Receive from server: |%.*s|, num_rw=%ld\n", (int)num_rw, sock_buf, num_rw);
        }
    }
}
