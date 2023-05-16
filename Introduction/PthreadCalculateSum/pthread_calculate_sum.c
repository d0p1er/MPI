//
// Created by d0p1er on 16/05/23.
//

#include "pthread_calculate_sum.h"

int n_threads = 0;
int N = 0;

void* calcSum(void* rank)
{
    double sum = 0.0;
    int steps = N / n_threads;
    int start = steps * (*(int*)(rank)) + 1;

    if (*(int*) (rank) + 1 == n_threads)
    {
        steps += N % n_threads;
    }

    for (int i = start, end = start + steps; i < end; i++)
    {
        sum += 1.0 / i;
    }

    double* out_sum = (double*) malloc(sizeof(double));
    *out_sum = sum;

    return out_sum;

}

void pthreadCalculateSum(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("[ERROR], no number of threads and N\n");
        return;
    }
    n_threads = atoi(argv[2]);
    N = atoi(argv[3]);

    pthread_t threads[n_threads];
    int ranks[n_threads];

    double total_sum = 0.0;

    for (int i = 0; i < n_threads; i++)
    {
        ranks[i] = i;
        pthread_create(&threads[i], NULL, &calcSum, &ranks[i]);
    }

    for  (int i = 0; i < n_threads; i++)
    {
        double* sum = NULL;
        pthread_join(threads[i], (void **) (&sum));
        total_sum += *sum;
        free(sum);
    }

    printf("Result sum = %lf\n", total_sum);

    return;
}