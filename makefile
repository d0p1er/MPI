main: main.c main.h\
	  Introduction/HelloWorld/hello_world.c Introduction/HelloWorld/hello_world.h \
	  Introduction/CalculateSum/calculate_sum.c Introduction/CalculateSum/calculate_sum.h\
	  Introduction/RoundTrip/round_trip.c Introduction/RoundTrip/round_trip.h \
	  TransportEquation/CalculateDelay/calculate_delay.c TransportEquation/CalculateDelay/calculate_delay.h \
	  TransportEquation/ConsistentSolution/consistent_solution.c TransportEquation/ConsistentSolution/consistent_solution.h \
	  TransportEquation/ParallelSolution/parallel_solution.c TransportEquation/ParallelSolution/parallel_solution.h \
	  TransportEquation/transport_equation.c TransportEquation/transport_equation.h \
	  Introduction/PthreadHello/pthread_hello.c Introduction/PthreadHello/pthread_hello.h \
	  Introduction/PthreadCalculateSum/pthread_calculate_sum.c Introduction/PthreadCalculateSum/pthread_calculate_sum.h \
	  Introduction/PthreadRoundTrip/pthread_round_trip.c Introduction/PthreadRoundTrip/pthread_round_trip.h
	mpicc -o main main.c \
			 Introduction/HelloWorld/hello_world.c \
			 Introduction/CalculateSum/calculate_sum.c \
			 Introduction/RoundTrip/round_trip.c \
			 TransportEquation/CalculateDelay/calculate_delay.c \
			 TransportEquation/ConsistentSolution/consistent_solution.c \
			 TransportEquation/ParallelSolution/parallel_solution.c \
			 TransportEquation/transport_equation.c \
			 Introduction/PthreadHello/pthread_hello.c \
			 Introduction/PthreadCalculateSum/pthread_calculate_sum.c \
			 Introduction/PthreadRoundTrip/pthread_round_trip.c \
			 -lm -pthread

run:
	mpirun -np $(NP) ./main $(IN)
