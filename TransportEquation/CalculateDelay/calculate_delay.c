//
// Created by d0p1er on 14/05/23.
//

#include "calculate_delay.h"

const int SENDER_RANK_DELAY = 0;
const int RECEIVER_RANK_DELAY = 1;

void calculateDelay(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("[ERROR], no arguments to calculate delay\n");
        return;
    }
    int i_n =  atoi(argv[2]);

    int result = 0;
    int comm_size = 0, comm_rank = 0;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &comm_rank);

    MPI_Status status;

    if (comm_rank == SENDER_RANK_DELAY)
    {
        for (size_t i = 0; i < i_n; i++)
        {
            MPI_Send(&result, 1, MPI_INT, RECEIVER_RANK_DELAY, 0, MPI_COMM_WORLD);
        }
    }
    else
    {
        double time_start = MPI_Wtime();
        for (size_t i = 0; i < i_n; i++)
        {
            MPI_Recv(&result, 1, MPI_INT, SENDER_RANK_DELAY, 0, MPI_COMM_WORLD, &status);
        }
        double time_end = MPI_Wtime();

        double delay = (time_end - time_start) * 1e6 / i_n;
        printf("Delay of one transaction: %f us\n", delay);
    }

    MPI_Finalize();
}
