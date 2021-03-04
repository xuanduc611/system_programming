#ifndef _URD_HDR_H_
#define _URD_HDR_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#include <errno.h>
#include <unistd.h>

#define SOCKET_SV_PATH      "/tmp/dxduc/ud_reliable"
#define SOCKET_BUF_SIZE     10

typedef struct sockaddr_un  SOCK_ADDR_UN_t;
typedef socklen_t           SOCKLEN_t;

#endif