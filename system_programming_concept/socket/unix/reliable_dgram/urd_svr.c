#include "urd_hdr.h"
#include <pthread.h>

static u_int8_t rx_is_allowed = 0;
static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

static inline void SERVER_LOCK();
static inline void SERVER_UNLOCK();

static int init_server(void);
static void *check_cmd_thr(void *arg);
static void *server_thr(void *arg);

static inline void SERVER_LOCK()
{
    pthread_mutex_lock(&mtx);
}
static inline void SERVER_UNLOCK()
{
    pthread_mutex_unlock(&mtx);
}

/**
 * @brief Initialize server
 * @param none
 * @return Bound socket of server, -1 for errors
*/
static int init_server(void)
{
    SOCK_ADDR_UN_t  svr_addr;
    int             sfd;
    ssize_t         num_rw;
    char            buf[SOCKET_BUF_SIZE];

    // Create socket:
    sfd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (sfd == -1) {
        printf("Error line[%d]: %s\n", __LINE__, strerror(errno));
        return -1;
    }

    // Verify socket's namepath:
    if (strlen(SOCKET_SV_PATH) > sizeof(svr_addr.sun_path) - 1)) {
        printf("Error line[%d]: invalid socket name\n", __LINE__);
        return -1;
    }

    // Remove any exitsting file having the same namepath with server's:
    if ((remove(SOCKET_SV_PATH) == -1) && (errno != ENOENT)) {
        printf("Error line[%d]: %s\n", __LINE__, strerror(errno));
        return -1;
    }

    // Bind the socket to desired addr:
    memset(&svr_addr, 0, sizeof(SOCK_ADDR_UN_t));
    svr_addr.sun_family = AF_UNIX;
    strncpy(svr_addr.sun_path, SOCKET_SV_PATH, sizeof(svr_addr.sun_path) - 1);

    if (bind(sfd, &svr_addr, sizeof(SOCK_ADDR_UN_t)) == -1) {
        printf("Error line[%d]: %s\n", __LINE__, strerror(errno));
        return -1;
    }

    return sfd;
}

static void *check_cmd_thr(void *arg)
{
    u_int8_t in_buf[10];
    int8_t len;

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
        } else if (strcmp(in_buf, "start") == 0) {
            printf("=> Stop receiving packets\n");
            rx_is_allowed = 0;
        } else {
            printf("Invalid input buffer\n");
        }

        SERVER_UNLOCK();
    }
}