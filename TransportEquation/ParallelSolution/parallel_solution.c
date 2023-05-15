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

#include "parallel_solution.h"

const int ROOT_RANK_PARALLEL = 0;


void parallelSolution(int argc, char *argv[])
{
    size_t K = T / tau;
    size_t M = X / h;

    int comm_size = 0, comm_rank = 0;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &comm_rank);

    MPI_Barrier(MPI_COMM_WORLD);
    double time_start = MPI_Wtime();

    size_t dist = M / comm_size;
    size_t remainder = M % comm_size;
    if (remainder != 0) {
        M = (dist + 1) * comm_size;
        dist++;
    }
    size_t x_start = dist * comm_rank;
    size_t x_end = dist * (comm_rank + 1);

    size_t len = x_end - x_start;

    double **values_part = initValues(len, K, x_start, len);

    computePart(values_part, x_start, K, len, comm_rank, comm_size);
    MPI_Barrier(MPI_COMM_WORLD);
    double time_end = MPI_Wtime();



    if (comm_rank == ROOT_RANK_PARALLEL)
        printf("time: %f\n", time_end - time_start);

    savePart(values_part, K, M, x_start, len);

    MPI_Finalize();
}

double **initValues(int n_x, int K, int x_start, int len)
{
    double **res = (double **) calloc(K, sizeof(double *));
    for (int t = 0; t < K; t++)
        res[t] = (double *) calloc(n_x, sizeof(double));

    if (x_start == 0)
        for (int t = 0; t < K; t++)
            res[t][0] = psi(tau * t);

    for (int x = 0; x < len; x++)
        res[0][x] = phi(h * (x + x_start));

    return res;
}

void computePart(double **part, size_t x_start, size_t K, size_t len, int comm_rank, int comm_size)
{
    if (x_start == 0)
    {
        for (int k = 0; k < K; k++)
        {
            for (int m = 0; m < len; m++)
            {
                if (k && m)
                {
                    part[k][m] = tau * f((k - 1) * tau, m * h) +
                                 part[k - 1][m] -
                                 a * tau * (part[k - 1][m] - part[k - 1][m - 1]) / h;
                }
            }
            if (comm_rank + 1 != comm_size)
                MPI_Send(&part[k][len - 1], 1, MPI_DOUBLE, comm_rank + 1, 0, MPI_COMM_WORLD);
        }
    }
    else
    {
        double *prev = (double *) calloc(K, sizeof(double));
        for (int k = 0; k < K; k++)
        {
            MPI_Status status;
            MPI_Recv(prev + k, 1, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

            for (int m = 0; m < len; m++) {
                if (k)
                {
                    if (m == 0)
                        part[k][m] = tau * f((k - 1) * tau, m * h) +
                                     part[k - 1][m] -
                                     a * tau * (part[k - 1][m] - prev[k - 1]) / h;
                    else
                        part[k][m] = tau * f((k - 1) * tau, m * h) +
                                     part[k - 1][m] -
                                     a * tau * (part[k - 1][m] - part[k - 1][m - 1]) / h;
                }
            }
            if (comm_rank + 1 != comm_size)
                MPI_Send(&part[k][len - 1], 1, MPI_DOUBLE, comm_rank + 1, 0, MPI_COMM_WORLD);
        }

        free(prev);
    }
}

void savePart(double **part, size_t K, size_t M, size_t x_start, size_t len)
{
    char *file = "TransportEquation/ParallelSolution/data/solution.txt";
    MPI_File_delete(file, MPI_INFO_NULL);
    MPI_File handle;
    MPI_File_open(MPI_COMM_WORLD, file, MPI_MODE_RDWR | MPI_MODE_CREATE, MPI_INFO_NULL, &handle);

    for (int k = 0; k < K; k++)
    {
        int offset = 2 * 10 * (M * k + x_start);
        char* line = (char *) calloc(2 * 10 * len, 1);
        for (int m = 0; m < len; m++)
        {
            char num[25] = {' '};
            num[20] = 0;
            sprintf(num, "%.10lf", part[k][m]);
            for (int i = 0; i < 25; i++)
            {
                char c = num[i];
                if (c == 0)
                    num[i] = ' ';
            }
            int last_in_line = (m + x_start == M - 1);
            num[17] = ' ';
            num[19] = last_in_line ? '\n' : ' ';
            memcpy(line + m * 20, num, 20);
        }
        MPI_Status status;
        MPI_File_write_at(handle, offset, line, 2 * 10 * len, MPI_CHAR, &status);
        free(line);
    }
    MPI_File_close(&handle);
}