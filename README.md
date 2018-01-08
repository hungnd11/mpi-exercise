# mpi-exercise
My MPI long exercise

### How to compile? 
Install open-mpi with prefix "/opt/mpi".
Go to project directory and execute: make clean && make all
Specify build/host to run with hostfile.

### How to run
For example: Find the number of primes number not greater than 100 using 2 processes.
/opt/mpi/bin/mpirun -np 2 build/sieve_parallel 100
/opt/mpi/bin/mpirun -np 2 build/sieve_parallel_improved 100 


### List of programs
sieve_serial: Implements sieve of Eratosthenes the serial way.
sieve_parallel: Implements sieve of Eratosthenes the parallel way.
sieve_parallel_improved: sieve_parallel with elimination of all even numbers.

