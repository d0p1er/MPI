//
// Created by d0p1er on 13/05/23.
//

#include "main.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
        printf("[ERROR], no arguments to start");

    if (strcmp(argv[1], "info") == 0)
    {
        printf("There are such commands:\n");
        printf("FIRST PART - INTRODUCTION:\n");
        printf("1) Hello world MPI: hello\n");
        printf("2) Sum MPI: sum\n");
        printf("3) Round_trip MPI: round_trip\n");
        printf("4) Hello world pthread: phello\n");
        printf("5) Sum pthread: psum\n");
        printf("6) Round_trip pthread: pround_trip\n\n");
        printf("SECOND PART - TRANSPORT EQUATION:\n");
        printf("1) Calculate delay: delay\n");
        printf("2) Consistent solution: sol_con\n");
        printf("3) Parallel solution: sol_par\n");
    }

    if (strcmp(argv[1], "hello") == 0)
        helloWorld(argc, argv);
    if (strcmp(argv[1], "sum") == 0)
        calculateSum(argc, argv);
    if (strcmp(argv[1], "round_trip") == 0)
        roundTrip(argc, argv);
    if (strcmp(argv[1], "phello") == 0)
        pthreadHello(argc, argv);
    if (strcmp(argv[1], "psum") == 0)
        pthreadCalculateSum(argc, argv);
    if (strcmp(argv[1], "pround_trip") == 0)
        pthreadRoundTrip(argc, argv);
    if (strcmp(argv[1], "delay") == 0)
        calculateDelay(argc, argv);
    if (strcmp(argv[1], "sol_con") == 0)
        consistentSolution(argc, argv);
    if (strcmp(argv[1], "sol_par") == 0)
        parallelSolution(argc, argv);

    return 0;
}
