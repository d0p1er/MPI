//
// Created by d0p1er on 13/05/23.
//

#include "main.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
        printf("[ERROR], no arguments to start");

    if (strcmp(argv[1], "hello") == 0)
        helloWorld(argc, argv);
    if (strcmp(argv[1], "sum") == 0)
        calculateSum(argc, argv);
    if (strcmp(argv[1], "round_trip") == 0)
        roundTrip(argc, argv);
    if (strcmp(argv[1], "delay") == 0)
        calculateDelay(argc, argv);
    if (strcmp(argv[1], "sol_con") == 0)
        consistentSolution(argc, argv);
    if (strcmp(argv[1], "sol_par") == 0)
        parallelSolution(argc, argv);

    return 0;
}
