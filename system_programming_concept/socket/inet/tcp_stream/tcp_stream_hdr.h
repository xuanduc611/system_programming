#ifndef _TCP_STREAM_HDR_H_
#define _TCP_STREAM_HDR_H_

#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>

#define MAX     80
#define PORT    50000

typedef struct sockaddr SOCKADDR_t;
typedef struct sockaddr_in SOCKADDR_IN_t;

#endif // _TCP_STREAM_HDR_H_

