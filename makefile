EXECS=build/sieve_serial build/sieve_parallel build/sieve_parallel_improved
MPICC?=/opt/mpi/bin/mpicc
GCC?=gcc

all: ${EXECS}

build/sieve_serial: 
	${GCC} -o build/sieve_serial src/sieve_serial.c

build/sieve_parallel: 
	${MPICC} -o build/sieve_parallel src/sieve_parallel.c -lm

build/sieve_parallel_improved:
	${MPICC} -o build/sieve_parallel_improved src/sieve_parallel_improved.c -lm

clean:
	rm -f ${EXECS}
