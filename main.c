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
    if (strcmp(argv[1], "calc_sum") == 0)
        calculateSum(argc, argv);
    if (strcmp(argv[1], "round_trip") == 0)
        roundTrip(argc, argv);

    return 0;
}
