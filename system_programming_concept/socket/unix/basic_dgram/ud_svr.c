#include "ud_hdr.h"

int main(int argc, char **argv)
{
    struct sockaddr_un  svr_addr, cli_addr;
    int                 sfd, i;
    ssize_t             num_rw;
    socklen_t           cli_addr_len;
    char                buf[SOCK_BUF_SIZE];

    // Create socket:
    sfd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (sfd == -1) {
        printf("Error line|%d|: %s\n", __LINE__, strerror(errno));
        exit(EXIT_FAILURE);
    }

    // Verify socket's name path:
    if (strlen(SOCKET_SV_PATH) > (sizeof(svr_addr.sun_path) - 1)) {
        printf("Error line|%d|: invalid socket name", __LINE__);
        exit(EXIT_FAILURE);
    }

    // Remove any existing file having the same namepath with server's:
    if ((remove(SOCKET_SV_PATH) == -1) && (errno != ENOENT)) {
        printf("Error line|%d|: %s\n", __LINE__, strerror(errno));
        exit(EXIT_FAILURE);
    }

    // Bind the socket to desired addr:
    memset(&svr_addr, 0, sizeof(struct sockaddr_un));
    svr_addr.sun_family = AF_UNIX;
    strncpy(svr_addr.sun_path, SOCKET_SV_PATH, sizeof(svr_addr.sun_path) - 1);

    if (bind(sfd, (struct sockaddr *)&svr_addr, sizeof(struct sockaddr_un)) == -1) {
        printf("Error line|%d|: %s\n", __LINE__, strerror(errno));
        exit(EXIT_FAILURE);
    }

    while (1) {
        // Receive data from client:
        memset(buf, 0, sizeof(buf));
        cli_addr_len = sizeof (struct sockaddr_un);
        num_rw = recvfrom(sfd, buf, SOCK_BUF_SIZE, 0, (struct sockaddr *) &cli_addr, &cli_addr_len);

        if (num_rw == -1) {
            printf("Error line|%d|: %s\n", __LINE__, strerror(errno));
            exit(EXIT_FAILURE);
        }

        printf("Server received %ld bytes from %s, ret_buf=|%.*s|, len=%ld\n", (long)num_rw, cli_addr.sun_path, (int)num_rw, buf, num_rw);

        // Uppercase received characters:
        for (i = 0; i < num_rw; i++) {
            buf[i] = toupper((unsigned char)buf[i]);
        }

        // Send back uppercase-ed characters to client:
        printf("Send back to client: |%.*s|, len=%ld\n", (int)num_rw, buf, num_rw);
        if (sendto(sfd, buf, strlen(buf), 0, (struct sockaddr *) &cli_addr, cli_addr_len) != strlen(buf)) {
            printf("Error line|%d|: %s\n", __LINE__, strerror(errno));
            exit(EXIT_FAILURE);
        }
    }
}
