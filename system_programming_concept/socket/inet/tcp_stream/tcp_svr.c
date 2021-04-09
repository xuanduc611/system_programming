#include "tcp_stream_hdr.h"
#include <time.h>

#define BACKLOG     5

static void client_handler(int fd, SOCKADDR_IN_t *addr);

int main(int argc, char** argv)
{
    int             sockfd, confd;
    SOCKADDR_IN_t   svr_addr, cli_addr;
    socklen_t       addrlen;

    // Create socket:
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("%s, line %d: Fail to create socket\n", __FUNCTION__, __LINE__);
        exit(EXIT_FAILURE);
    }

    bzero(&svr_addr, sizeof(svr_addr));

    // Bind created socket to specified address:
    svr_addr.sin_family = AF_INET;
    svr_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    svr_addr.sin_port = htons(PORT);

    if (bind(sockfd, (SOCKADDR_t *)&svr_addr, sizeof(SOCKADDR_IN_t)) != 0) {
        printf("%s, line %d: Fail to bind socket, %s\n", __FUNCTION__, __LINE__, strerror(errno));
        exit(EXIT_FAILURE);
    }

    // Listen to other clients:
    if (listen(sockfd, BACKLOG) != 0) {
        printf("%s, line %d: Fail to listen\n", __FUNCTION__, __LINE__);
        exit(EXIT_FAILURE);
    }

    // Handle data from clients:
    while (1) {
        confd = accept(sockfd, (SOCKADDR_t *)&cli_addr, &addrlen);
        if (confd < 0) {
            printf("%s, line %d: Server does not accecp connection \n", __FUNCTION__, __LINE__);
            close(confd);        
        }

        client_handler(confd, &cli_addr);
    }

    close(sockfd);
}

static void client_handler(int fd, SOCKADDR_IN_t *addr)
{
    time_t      T = time(NULL);
    struct tm   cur_time = *localtime(&T);
    char        msg_buf[MAX];
    char        addr_str[MAX];

    while (1) {
        bzero(msg_buf, MAX);

        // Read the msg from client:
        read(fd, msg_buf, sizeof(msg_buf));
        inet_ntop(AF_INET, &addr->sin_addr.s_addr, addr_str, sizeof(addr_str));
        printf("%s, line %d: Msg from %s is %s ", __FUNCTION__, __LINE__, addr_str, msg_buf);

        if (strncmp("time", msg_buf, strlen("time")) == 0) {
            printf("=> Response time\n");
            bzero(msg_buf, MAX);
            sprintf(msg_buf, "Time is %02d:%02d:%02d", cur_time.tm_hour, cur_time.tm_min, cur_time.tm_sec);
            write(fd, msg_buf, sizeof(msg_buf));
        } else if (strncmp("date", msg_buf, strlen("date")) == 0) {
            printf("=> Response date\n");
            bzero(msg_buf, MAX);
            sprintf(msg_buf, "Date is %02d/%02d/%04d", cur_time.tm_mday, cur_time.tm_mon + 1, cur_time.tm_year + 1900);
            write(fd, msg_buf, sizeof(msg_buf));
        } else {
            printf("=> Ignore this message\n");
            bzero(msg_buf, MAX);
            write(fd, msg_buf, sizeof(msg_buf));
        }
    }
}