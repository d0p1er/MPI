//
// Created by d0p1er on 14/05/23.
//

#include "mpi.h"
#include "stdio.h"
#include "stdlib.h"

#pragma once

extern const int SENDER_RANK_DELAY;
extern const int RECEIVER_RANK_DELAY;

void calculateDelay(int argc, char *argv[]);
