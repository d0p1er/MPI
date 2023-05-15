//
// Created by d0p1er on 14/05/23.
//

#include "mpi.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "../transport_equation.h"

#pragma once

extern const int ROOT_RANK_CONSISTENT;

void consistentSolution(int argc, char *argv[]);
