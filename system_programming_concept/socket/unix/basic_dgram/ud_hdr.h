#ifndef _UD_HDR_H_
#define _UD_HDR_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#include <errno.h>
#include <unistd.h>

// * The Makefile should have created /tmp/dxduc before run this program
#define SOCKET_SV_PATH      "/tmp/dxduc/ud_basic"
#define SOCK_BUF_SIZE            10

#endif // _UD_HDR_H_
