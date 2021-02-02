#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

static int g = 0;

static void *my_thread(void *arg);

static void *my_thread(void *arg)
{
    int *my_id = (int *)arg;
    static int s = 0;

    ++s;
    ++g;

    printf("Thread ID = %d, Static = %d, Global = %d\n", *my_id, ++s, ++g);

    return 0;
}

int main(int argc, char *argv[])
{
    int i;
    pthread_t tid;

    for (i = 0; i < 3; i++) {
        pthread_create(&tid, NULL, my_thread, (void *)&tid);
    }

    pthread_exit(NULL);
    
    return 0;
}

