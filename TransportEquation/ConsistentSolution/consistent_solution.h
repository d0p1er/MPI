//
// Created by d0p1er on 14/05/23.
//

#include "mpi.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"

#pragma once

extern const int ROOT_RANK_CONSISTENT;

double f(double t, double x);
double phi(double x);
double psi(double t);

void consistentSolution(int argc, char *argv[]);
