//
// Created by d0p1er on 13/05/23.
//

#include "calculate_sum.h"

const int ROOT_RANK_SUM = 0;

void calculateSum(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("[ERROR], no arguments to calculate sum\n");
        return;
    }
    int N =  atoi(argv[2]);

    double result = 0;
    int comm_size = 0, comm_rank = 0;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &comm_rank);

    int dist = N / comm_size;
    int remainder = N % comm_size;

    int n_start = 1 + dist * comm_rank;
    int n_end = 1 + dist * (comm_rank + 1);

    if (remainder != 0)
    {
        if (remainder <= comm_rank)
        {
            n_start += remainder;
            n_end += remainder;
        }
        else
        {
            n_start += comm_rank;
            n_end += comm_rank + 1;
        }
    }

    double sum = 0;
    for (int i = n_start; i < n_end; i++)
    {
        sum += 1.0 / i;
    }

    MPI_Reduce(&sum, &result, 1, MPI_DOUBLE, MPI_SUM, ROOT_RANK_SUM, MPI_COMM_WORLD);

    if (comm_rank == ROOT_RANK_SUM)
    {
        printf("Result sum = %f\n", result);
    }

    MPI_Finalize();
}