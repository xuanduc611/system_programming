#include "urd_hdr.h"

#define MAX_MSG_SIZE     200

static void send_msg(int sd, const SOCK_ADDR_UN_t *addr, SOCKLEN_t addr_len);

int main(int argc, char **argv)
{
    SOCK_ADDR_UN_t      svr_addr;
    int                 sfd;
    SOCKLEN_t           svr_addr_len;
    
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

        sleep(1);
    }
}

static void send_msg(int sd, const SOCK_ADDR_UN_t *addr, SOCKLEN_t addr_len)
{
    static int      idx = 0;
    static char     str[] = "message ";
    static char     msg[MAX_MSG_SIZE];

    // Format message before sending:
    memset(&msg, 0, sizeof(msg));
    sprintf(msg, "%s%d", str, idx++);

    // Send msg to server:
    if (sendto(sd, msg, strlen(msg), 0, (SOCK_ADDR_t *)addr, addr_len) != strlen(msg)) {
        printf("%s, %s-line %d\n", strerror(errno), __func__, __LINE__);
        exit(EXIT_FAILURE);
    } else {
        printf("Message is sent successfully: [%s]\n", msg);
    }
}