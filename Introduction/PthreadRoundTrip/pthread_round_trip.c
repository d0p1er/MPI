//
// Created by d0p1er on 16/05/23.
//

#include "pthread_round_trip.h"

int n_threads;
int message = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* send(void* rank)
{
    pthread_mutex_lock(&mutex);
    int cur_msg = message;
    message++;
    pthread_mutex_unlock(&mutex);

    printf ("Thread is: %d. Current message is %d\n", *(int *)(rank), message);

    return NULL;
}

void pthreadRoundTrip(int argc, char* argv[])
{
    if (argc < 4)
    {
        printf("[ERROR], number of threads\n");
        return;
    }

    n_threads = atoi(argv[2]);
    message = atoi(argv[3]);

    pthread_t threads[n_threads];
    int ranks[n_threads];

    pthread_mutex_unlock(&mutex);

    for (int i = 0; i < n_threads; i++)
    {
        ranks[i] = i;
        pthread_create(&threads[i], NULL, send, &ranks[i]);
    }

    for  (int i = 0; i < n_threads; i++)
        pthread_join(threads[i], NULL);

    return;
}