#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define THREADS 4
#define ALLOCS 50

void *worker(void *arg)
{
    (void)arg;

    printf("worker started\n");

    for (int i = 0; i < ALLOCS; i++)
    {
        printf("allocation %d\n", i);

        char *ptr = malloc(16);

        if (ptr == NULL)
        {
            printf("malloc failed\n");
            return NULL;
        }

        memset(ptr, 'A', 16);
        free(ptr);
    }

    printf("worker finished\n");
    return NULL;
}

int main(void)
{
    pthread_t threads[THREADS];

    printf("Starting...\n");

    for (int i = 0; i < THREADS; i++)
    {
        if (pthread_create(&threads[i], NULL, worker, NULL) != 0)
        {
            printf("pthread_create failed\n");
            return 1;
        }
    }

    for (int i = 0; i < THREADS; i++)
        pthread_join(threads[i], NULL);

    printf("All threads finished successfully!\n");

    return 0;
}