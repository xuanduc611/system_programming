#include "urd_hdr.h"
#include <pthread.h>

#define SERVER_LOCK()       pthread_mutex_lock(&mtx)
#define SERVER_UNLOCK()     pthread_mutex_unlock(&mtx);

static u_int8_t rx_is_allowed = 0;
static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

static int init_server(char *svr_path);
static void *check_cmd_thr(void *arg);
static void *server_thr(void *arg);

/**
 * @brief Initialize server
 * @param svr_path socket pathname of server
 * @return Bound socket of server, -1 for errors
*/
static int init_server(char *svr_path)
{
    SOCK_ADDR_UN_t  svr_addr;
    int             sfd;

    // Create socket:
    sfd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (sfd == -1) {
        printf("Error line[%d]: %s\n", __LINE__, strerror(errno));
        return -1;
    }

    // Verify socket's namepath:
    if (strlen(svr_path) > (sizeof(svr_addr.sun_path) - 1)) {
        printf("Error line[%d]: invalid socket name\n", __LINE__);
        return -1;
    }

    // Remove any exitsting file having the same namepath with server's:
    if ((remove(svr_path) == -1) && (errno != ENOENT)) {
        printf("Error line[%d]: %s\n", __LINE__, strerror(errno));
        return -1;
    }

    // Bind the socket to desired addr:
    memset(&svr_addr, 0, sizeof(SOCK_ADDR_UN_t));
    svr_addr.sun_family = AF_UNIX;
    strncpy(svr_addr.sun_path, svr_path, sizeof(svr_addr.sun_path) - 1);

    if (bind(sfd, (SOCK_ADDR_t *)&svr_addr, sizeof(SOCK_ADDR_UN_t)) == -1) {
        printf("Error line[%d]: %s\n", __LINE__, strerror(errno));
        return -1;
    }

    return sfd;
}

static void *check_cmd_thr(void *arg)
{
    char in_buf[10];
    int8_t len;

    printf ("Start %s\n", __func__);
    while (1) {
        SERVER_LOCK();

        len = read(STDIN_FILENO, in_buf, sizeof(in_buf)); 
        if (len == -1) {
            printf("Error line[%d]: fails to read from stdin, %s\n", __LINE__, strerror(errno));
            continue;
        }

        if (len > sizeof(in_buf)) {
            printf("The length of input buffer is too long\n");
            continue;
        }

        in_buf[len - 1] = 0x0;

        if (strcmp(in_buf, "start") == 0) {
            printf("=> Start receiving packets\n");
            rx_is_allowed = 1;
        } else if (strcmp(in_buf, "stop") == 0) {
            printf("=> Stop receiving packets\n");
            rx_is_allowed = 0;
        } else {
            printf("Invalid input buffer\n");
        }

        fflush(stdout);
        SERVER_UNLOCK();
    }

    return 0;
}

static void *server_thr(void *arg)
{
    int16_t     sfd;
    int8_t      buf[SOCKET_BUF_SIZE];
    ssize_t     num_rw;

    printf ("Start %s\n", __func__);

    sfd = init_server(SOCKET_SV_PATH);
    if (sfd == -1) {
        printf("Failed to initialize server\n");
    } else {
        printf("Initialize server successfully\n");
    }

    while (1) {
        SERVER_LOCK();
        fflush(stdout); // * clear the output buffer and move the buffered data to output (a.k.a console in this case)

        if (rx_is_allowed) {    
            // Receive data from client:
            memset(buf, 0, sizeof(buf));
            num_rw = recvfrom(sfd, buf, SOCKET_BUF_SIZE, 0, NULL, NULL);

            if (num_rw == -1) {
                printf("Error line[%d]: %s\n", __LINE__, strerror(errno));
                continue;
            }
            
            printf("Server received %ld bytes, ret_buf=[%.*s]\n", (long)num_rw, (int)num_rw, buf);
        }

        SERVER_UNLOCK();
    }

    return 0;
}

int main(int argc, char **argv)
{
    pthread_t tid_1, tid_2;
    int ret;

    rx_is_allowed = 1;

    ret = pthread_create(&tid_1, NULL, server_thr, NULL);
    if (ret != 0) {
        printf("Fail to create server_thr\n");
    } else {
        printf("Create server_thr succesfully\n");
    }

    ret = pthread_create(&tid_2, NULL, check_cmd_thr, NULL);
    if (ret != 0) {
        printf("Fail to create check_cmd_thr\n");
    } else {
        printf("Create check_cmd_thr succesfully\n");
    }

    ret = pthread_join(tid_1, NULL);
    if (ret != 0) {
        printf("Fail to join server_thr\n");
    } else {
        printf("Join server_thr succesfully\n");
    }

    ret = pthread_join(tid_2, NULL);
    if (ret != 0) {
        printf("Fail to join check_cmd_thr\n");
    } else {
        printf("Join check_cmd_thr succesfully\n");
    }

    return 0;
}