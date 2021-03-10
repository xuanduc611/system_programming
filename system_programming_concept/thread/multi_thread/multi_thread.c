#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

static int g = 0;
static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

static void *my_thread(void *arg);

static void *my_thread(void *arg)
{
    int *my_id = (int *)arg;
    static int s = 0;

    while (1) {
        pthread_mutex_lock(&mtx);
        
        printf("Thread ID = %d, Static = %d, Global = %d\n", *my_id, s++, g++);

        pthread_mutex_unlock(&mtx);
        sleep(1);
    }
    return 0;
}

int main(int argc, char *argv[])
{
    int i;
    pthread_t tid[3];

    for (i = 0; i < 3; i++) {
        pthread_create(&tid[i], NULL, my_thread, (void *)&tid[i]);
    }

    for (i = 0; i < 3; i++) {
        pthread_join(tid[i], NULL);
    }

    return 0;
}

