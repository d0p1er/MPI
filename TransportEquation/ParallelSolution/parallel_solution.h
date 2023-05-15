//
// Created by d0p1er on 14/05/23.
//

#include "mpi.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "string.h"
#include "../transport_equation.h"

#pragma once

extern const int ROOT_RANK_PARALLEL;

void parallelSolution(int argc, char *argv[]);
double **initValues(int n_x, int n_t, int x_start, int len);
void computePart(double **part, size_t x_start, size_t K, size_t len, int comm_rank, int comm_size);
void savePart(double **part, size_t K, size_t M, size_t x_start, size_t len);
