main: main.c main.h\
	  Introduction/HelloWorld/hello_world.o \
	  Introduction/CalculateSum/calculate_sum.o \
	  Introduction/RoundTrip/round_trip.o
	mpicc -o main main.c Introduction/HelloWorld/hello_world.o Introduction/CalculateSum/calculate_sum.o Introduction/RoundTrip/round_trip.o

Introduction/HelloWorld/hello_world.o: Introduction/HelloWorld/hello_world.c Introduction/HelloWorld/hello_world.h
	mpicc -c -o Introduction/HelloWorld/hello_world.o Introduction/HelloWorld/hello_world.c

Introduction/CalculateSum/calculate_sum.o: Introduction/CalculateSum/calculate_sum.c Introduction/CalculateSum/calculate_sum.h
	mpicc -c -o Introduction/CalculateSum/calculate_sum.o Introduction/CalculateSum/calculate_sum.c

Introduction/RoundTrip/round_trip.o: Introduction/RoundTrip/round_trip.c Introduction/RoundTrip/round_trip.h
	mpicc -c -o Introduction/RoundTrip/round_trip.o Introduction/RoundTrip/round_trip.c

run:
	mpirun -np 4 ./main $(IN)




