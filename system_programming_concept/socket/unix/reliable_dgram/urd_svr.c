#include "urd_hdr.h"
#include <pthread.h>

static u_int8_t rx_is_allowed = false;

static void *check_cmd_thr(void *arg);
static void *server_thr(void *arg);