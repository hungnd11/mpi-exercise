EXECS=build/sieve_serial build/sieve_parallel
MPICC?=mpicc
GCC?=gcc

all: ${EXECS}

build/sieve_serial: 
	${GCC} -o build/sieve_serial src/sieve_serial.c

build/sieve_parallel: 
	${MPICC} -o build/sieve_parallel src/sieve_parallel.c -lm

clean:
	rm -f ${EXECS}

run:
	./build/sieve_serial
	mpirun -np 2 ./build/sieve_parallel_initial
