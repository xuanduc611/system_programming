/** @brief: How to create detached thread.
*/

#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

static void* thread_dummy(void *arg)
{
    sleep(1);
    return NULL;
}

/** @brief Check detach state of a thread.
 *  @param tid: thread to check detach state.
 *  @param tname: thread name
*/
static void detach_state(pthread_t tid, const char* tname)
{
    int rc;

    rc = pthread_join(tid, NULL);
    if (rc == EINVAL) {
        printf("%s is detached\n", tname);
    } else if (rc == 0) {
        printf("%s is joinable\n", tname);
    } else {
        printf("%s: pthread_join() = %d (%s)\n", tname, rc, strerror(rc));
    }
}

int main(int argc, char *argv[])
{
    pthread_t tid_1, tid_2, tid_3;
    pthread_attr_t attr;
    int rc;

    // Normal thread creation:
    rc = pthread_create(&tid_1, NULL, thread_dummy, NULL);
    if (rc) {
        printf("Fail to create thread 1\n");
    }
    
    detach_state(tid_1, "thread_1");

    // Detach thread from main thread:
    rc = pthread_create(&tid_2, NULL, thread_dummy, NULL);
    if (rc) {
        printf("Fail to create thread 2\n");
    }
    
    rc = pthread_detach(tid_2);
    if (rc) {
        printf("Fail to detach thread 2\n");
    }
    
    detach_state(tid_2, "thread_2");

    // Set detachstate attibute to create detached thread:
    rc = pthread_attr_init(&attr);
    if (rc) {
        printf("Fail to init attribute for thread 3\n");
    }

    rc = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    if (rc) {
        printf("Fail to set detach state\n");
    }

    rc = pthread_create(&tid_3, &attr, thread_dummy, NULL);
    if (rc) {
        printf("Fail to craete thread 3\n");
    }

    detach_state(tid_3, "thread_3");

    return 0;
}
