#ifndef _U_HDR_H
#define _U_HDR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <sys/types.h>
#include <sys/socket.h> 
#include <sys/un.h>

#include <errno.h>
#include <unistd.h>

// * Make sure that you create /tmp/dxduc before run this program
#define SOCKET_SV_PATH      "/tmp/dxduc/unix_basic"
#define BUF_SIZE            200

#endif // _U_HDR_H