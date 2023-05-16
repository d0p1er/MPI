//
// Created by d0p1er on 16/05/23.
//

#include "pthread_hello.h"

void* printHello(void* rank)
{
    printf("Hello world! Thread %d.\n", *(int*) rank);
    return NULL;
}


void pthreadHello(int argc, char* argv[])
{
    if (argc < 3)
    {
        printf("[ERROR], no arguments to calculate delay\n");
        return;
    }
    int n_threads = atoi(argv[2]);

    pthread_t threads[n_threads];
    int ranks[n_threads];

    for (int i = 0; i < n_threads; i++)
    {
        ranks[i] = i;
        pthread_create(&threads[i], NULL, printHello, &ranks[i]);
    }

    for  (int i = 0; i < n_threads; i++)
        pthread_join(threads[i], NULL);

    return;
}