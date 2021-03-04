#include "urd_hdr.h"

#define MAX_MSG_SIZE     200

static void send_msg(int sd, const SOCK_ADDR_UN_t *addr, SOCKLEN_t addr_len);

int main(int argc, char **argv)
{
    SOCK_ADDR_UN_t      svr_addr;
    int                 sfd, i;
    ssize_t             num_rw;
    SOCKLEN_t           svr_addr_len;
    char                sock_buf[SOCK_BUF_SIZE];
    char                in_buf[IN_BUF_SIZE];

    // Create socket:
    sfd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (sfd == -1) {
        printf("%s, %s-line %d\n", strerror(errno), __func__, __LINE__);
        exit(EXIT_FAILURE);
    }

    // Construct server's address:
    memset(&svr_addr, 0, sizeof(SOCK_ADDR_UN_t));
    svr_addr.sun_family = AF_UNIX;
    strncpy(svr_addr.sun_path, SOCKET_SV_PATH, sizeof(svr_addr.sun_path) - 1);
    svr_addr_len = sizeof(SOCK_ADDR_UN_t);

    printf("Client is ready to run\n");

    while (1) {
        send_msg(sfd, &svr_addr, svr_addr_len);

        sleep(2000);
    }
}

static void send_msg(int sd, const SOCK_ADDR_UN_t *addr, SOCKLEN_t addr_len)
{
    static u_int32_t    idx = 0;
    static u_int8_t     str[] = "message ";
    static u_int8_t     msg[MAX_MSG_SIZE];

    // Format message before sending:
    memset(&msg, 0, sizeof(msg));
    sprintf(msg, "%s-%d", str, idx++);

    // Send msg to server:
    if (sendto(sd, msg, strlen(msg), 0, addr, addr_len) != strlen(msg)) {
        printf("%s, %s-line %d\n", strerror(errno), __func__, __LINE__);
        exit(EXIT_FAILURE);
    } else {
        printf("Message is sent successfully, %s\n", __func__);
    }
}