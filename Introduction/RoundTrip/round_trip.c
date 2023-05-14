//
// Created by d0p1er on 14/05/23.
//

#include "round_trip.h"

const int ROOT_RANK_ROUND = 0;

void roundTrip(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("[ERROR], no arguments to calculate sum\n");
        return;
    }
    int val =  atoi(argv[2]);

    int result = val;
    int comm_size = 0, comm_rank = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &comm_rank);

    MPI_Status status;

    if (comm_rank != ROOT_RANK_ROUND)
        MPI_Recv(&result, 1, MPI_INT, comm_rank - 1, 0, MPI_COMM_WORLD, &status);

    result++;

    if (comm_rank == comm_size - 1)
    {
        MPI_Send(&result, 1, MPI_INT, ROOT_RANK_ROUND, 0, MPI_COMM_WORLD);
        printf("Send from %d to %d val: %d\n", comm_rank, 0, result);
    }
    else
    {
        MPI_Send(&result, 1, MPI_INT, comm_rank + 1, 0, MPI_COMM_WORLD);
        printf("Send from %d to %d val: %d\n", comm_rank, comm_rank + 1, result);
    }

    if (comm_rank == ROOT_RANK_ROUND)
    {
        MPI_Recv(&result, 1, MPI_INT, comm_size - 1, 0, MPI_COMM_WORLD, &status);
        printf("Start = %d End = %d\n", val, result);
    }

    MPI_Finalize();
}