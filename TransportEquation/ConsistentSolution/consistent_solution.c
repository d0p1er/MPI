//
// Created by d0p1er on 14/05/23.
//
/* Solution of Transport Equation
 * du/dt - du/dx = t + x
 * u(0,x) = cos(PI * x) = phi(x)
 * u(t,0) = exp(-t) = psi(t)
 * x = (0; 1]
 * t = (0; 1]
 *
 * Stability if a * tau <= h
 * BEST if a * tau = h
 */

#include "consistent_solution.h"

const int ROOT_RANK_CONSISTENT = 0;

void consistentSolution(int argc, char *argv[])
{
    size_t K = T / tau;
    size_t M = X / h;

    int comm_size = 0, comm_rank = 0;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &comm_rank);

    size_t dist = M / comm_size;

    double **values = (double**) calloc(K, sizeof(double*));
    for (size_t i = 0; i < K; i++)
        values[i] = (double*) calloc(dist, sizeof(double));

    // init values
    for (size_t k = 0; k < K; k++)
        values[k][0] = psi(k * tau);
    for (size_t m = 0; m < dist; m++)
        values[0][m] = phi(m * h);

    double time_start = MPI_Wtime();

    if (comm_rank == ROOT_RANK_CONSISTENT) {
        for (size_t k = 0; k < K; k++)
        {
            for (size_t m = 0; m < dist; m++)
            {
                if (k && m)
                {
                    values[k][m] = tau * f((k - 1) * tau, m * h) +
                                   values[k - 1][m] -
                                   a * tau * (values[k - 1][m] - values[k - 1][m - 1]) / h;
                }
            }
        }
    }
    double time_end = MPI_Wtime();

    if (comm_rank == ROOT_RANK_CONSISTENT)
    {
        printf("time: %f\n", time_end - time_start);

        FILE* file_write = fopen("TransportEquation/ConsistentSolution/data/solution.txt", "w+");

        if (file_write == NULL){
            printf("[ERROR] Unable to open file\n");
            exit(EXIT_FAILURE);
        }

        for (size_t k = 0; k < K; k++)
        {
            for (size_t m = 0; m < dist; m++)
            {
                fprintf(file_write, "%f ", values[k][m]);
            }
            fprintf(file_write, "\n");
        }

        fclose(file_write);
    }

    MPI_Finalize();
}
