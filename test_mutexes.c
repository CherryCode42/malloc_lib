#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "malloc.h"

#define THREADS 4
#define ALLOCS 1000

pthread_mutex_t test_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t allocator_mutex = PTHREAD_MUTEX_INITIALIZER;

int success_count = 0;

void *worker(void *arg)
{
    int id = *(int *)arg;

    printf("Worker %d started\n", id);

    for (int i = 0; i < ALLOCS; i++)
    {
        char *ptr;

        pthread_mutex_lock(&allocator_mutex);

        ptr = malloc(16);
        if (ptr == NULL)
        {
            pthread_mutex_unlock(&allocator_mutex);
            printf("Worker %d: malloc failed\n", id);
            return NULL;
        }

        memset(ptr, 'A', 16);

        if (ptr[0] != 'A' || ptr[15] != 'A')
        {
            free(ptr);
            pthread_mutex_unlock(&allocator_mutex);
            printf("Worker %d: memory corruption!\n", id);
            return NULL;
        }

        free(ptr);

        pthread_mutex_unlock(&allocator_mutex);

        pthread_mutex_lock(&test_mutex);
        success_count++;
        pthread_mutex_unlock(&test_mutex);
    }

    printf("Worker %d finished\n", id);
    return NULL;
}

int main(void)
{
    pthread_t threads[THREADS];
    int ids[THREADS];

    printf("Starting...\n");

    for (int i = 0; i < THREADS; i++)
    {
        ids[i] = i + 1;

        if (pthread_create(&threads[i], NULL, worker, &ids[i]) != 0)
        {
            printf("pthread_create failed\n");
            return 1;
        }
    }

    for (int i = 0; i < THREADS; i++)
        pthread_join(threads[i], NULL);

    printf("All threads finished!\n");
    printf("Successful allocations: %d / %d\n",
        success_count, THREADS * ALLOCS);

    pthread_mutex_destroy(&allocator_mutex);
    pthread_mutex_destroy(&test_mutex);

    return 0;
}

