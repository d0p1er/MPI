main: main.c main.h\
	  Introduction/HelloWorld/hello_world.o \
	  Introduction/CalculateSum/calculate_sum.o \
	  Introduction/RoundTrip/round_trip.o \
	  TransportEquation/CalculateDelay/calculate_delay.o \
	  TransportEquation/ConsistentSolution/consistent_solution.o \
	  TransportEquation/ParallelSolution/parallel_solution.o
	mpicc -o main main.c \
			 Introduction/HelloWorld/hello_world.o \
			 Introduction/CalculateSum/calculate_sum.o \
			 Introduction/RoundTrip/round_trip.o \
			 TransportEquation/CalculateDelay/calculate_delay.o \
			 TransportEquation/ParallelSolution/parallel_solution.o \
			 -lm

Introduction/HelloWorld/hello_world.o: Introduction/HelloWorld/hello_world.c Introduction/HelloWorld/hello_world.h
	mpicc -c -o Introduction/HelloWorld/hello_world.o Introduction/HelloWorld/hello_world.c

Introduction/CalculateSum/calculate_sum.o: Introduction/CalculateSum/calculate_sum.c Introduction/CalculateSum/calculate_sum.h
	mpicc -c -o Introduction/CalculateSum/calculate_sum.o Introduction/CalculateSum/calculate_sum.c

Introduction/RoundTrip/round_trip.o: Introduction/RoundTrip/round_trip.c Introduction/RoundTrip/round_trip.h
	mpicc -c -o Introduction/RoundTrip/round_trip.o Introduction/RoundTrip/round_trip.c

TransportEquation/CalculateDelay/calculate_delay.o: TransportEquation/CalculateDelay/calculate_delay.c TransportEquation/CalculateDelay/calculate_delay.h
	mpicc -c -o TransportEquation/CalculateDelay/calculate_delay.o TransportEquation/CalculateDelay/calculate_delay.c

TransportEquation/ConsistentSolution/consistent_solution.o: TransportEquation/ConsistentSolution/consistent_solution.c TransportEquation/ConsistentSolution/consistent_solution.h
	mpicc -c -o TransportEquation/ConsistentSolution/consistent_solution.o TransportEquation/ConsistentSolution/consistent_solution.c -lm

TransportEquation/ParallelSolution/parallel_solution.o: TransportEquation/ParallelSolution/parallel_solution.c TransportEquation/ParallelSolution/parallel_solution.h
	mpicc -c -o TransportEquation/ParallelSolution/parallel_solution.o TransportEquation/ParallelSolution/parallel_solution.c -lm

run:
	mpirun -np $(NP) ./main $(IN)




