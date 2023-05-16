//
// Created by d0p1er on 16/05/23.
//
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#pragma once

void* send(void* rank);
void pthreadRoundTrip(int argc, char* argv[]);
