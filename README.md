# mpi-exercise
My MPI long exercise

### How to compile? 
Install open-mpi with prefix "/opt/mpi".<br/>
Go to project directory and execute: make clean && make all <br/>
Specify build/host to run with hostfile.<br/>

### How to run
For example: Find the number of primes number not greater than 100 using 2 processes. <br/>
/opt/mpi/bin/mpirun -np 2 build/sieve_parallel 100 <br/>
/opt/mpi/bin/mpirun -np 2 build/sieve_parallel_improved 100 <br/>


### List of programs
sieve_serial: Implements sieve of Eratosthenes the serial way. <br/>
sieve_parallel: Implements sieve of Eratosthenes the parallel way. <br/>
sieve_parallel_improved: sieve_parallel with elimination of all even numbers. <br/>

