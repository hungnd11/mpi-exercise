/*
 * ===================================================================================== 
 *       Filename:  sieve_parallel_initial.c
 *
 *    Description:  Implement Sieve of Eratosthenes parallel algorithm
 *
 *        Version:  0.1
 *       Compiler:  mpicc
 *
 *         Author:  hungnd11@github.com
 *   Organization:  HUST
 * =====================================================================================
 */

#include <mpi.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "blockdecomp.h"

/* Return the index of the first element in the block
 * param: prime_: the given prime number
 * param: low_value_: the lowest value of the block
 * return: the index of the first element in the block
 */
int
get_first_elem(int prime_, int low_value_)
{
	int first_;
	
	if(prime_ * prime_ > low_value_)
		first_ = prime_ * prime_ - low_value_;
	else 
	{
		if(!(low_value_ % prime_))
			first_ = 0;
		else 
			first_ = prime_ - (low_value_ % prime_);
	}

	return first_;
}

int 
main(int argc, char *argv[])
{
	int 		count;  			// local prime count
	double 	elapsed_time; // parallel execution time 
	int 		first; 				// index of the first multiple
	int 		global_count; // global prime count 
	int 		high_value; 	// highest value on this process
	int 		i;
	int 		id; 					// process ID number
	int 		index; 				// index of current prime 
	int 		low_value; 		// lowest value on this process
	char 		*marked; 			// portion of 2,..., 'n'
	int 		n; 						// sieving from 2,..., 'n'
	int 		p; 						// number of processes
	int 		proc0_size; 	// size of process 0's subarray
	int 		prime; 				// current prime
	int 		size; 				// elements in the marked

	MPI_Init(&argc, &argv);

	// start the timer
	MPI_Barrier(MPI_COMM_WORLD);
	elapsed_time = -MPI_Wtime();

	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	MPI_Comm_size(MPI_COMM_WORLD, &p);

	// if the process does not have enough arguments
	// and the process has not been given id yet
	if(argc != 2)
	{
		if(!id) 
		{
			printf("Command line: %s <m>\n", argv[0]);
			printf("You must provide the upper bound to find prime numbers.\n");
		}
		MPI_Finalize();
		exit(1);
	}

	n = atoi(argv[1]);

	/* figure out this process's share of the array, as well as
	   the integers represented by the first and last array elements.
	 */
	low_value = 2 + BLOCK_LOW(id, p, n - 1);
	high_value = 2 + BLOCK_HIGH(id, p, n - 1);
	size = BLOCK_SIZE(id, p, n - 1);

	/* rail out if all the primes used for sieving are not all held by process 0 */ 
	proc0_size = (n - 1) / p;

	if((2 + proc0_size) < (int) sqrt((double) n))
	{
		if(!id) printf("Too many processes.\n");		
		MPI_Finalize();
		exit(1);
	}

	/* allocate this process's share of the array */
	marked = (char *) malloc(size * sizeof(char));

	/* if we cannot allocate enough memory*/
	if(marked == NULL)
	{
		printf("Cannot allocate enough memory.\n"); 
		MPI_Finalize();
		exit(1);
	}

	/* initialize the marked array */
	for(i = 0; i < size; i++)
	{
		marked[i] = 0;
	}
	
	if(!id) 
		index = 0;
	
	prime = 2;
	do 
	{
		// determine the first element
		first = get_first_elem(prime, low_value);
		// mark all multiples of prime in range [first, size - 1]
		for(i = first; i < size; i += prime)
		{
			marked[i] = 1;
		}
		if(!id)
		{
			while(marked[++index]);
			prime = index + 2;
		}
		MPI_Bcast(&prime, 1, MPI_INT, 0, MPI_COMM_WORLD);
	} while(prime * prime <= n);

	count = 0; 
	for(i = 0; i < size; i++)
	{
		if(!marked[i]) count++;
	}

	MPI_Reduce(&count, &global_count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

	// stop the timer
	elapsed_time += MPI_Wtime();

	// print the results
	if(!id) 
	{
		printf("%d primes are less than or equal to %d\n", global_count, n);
		printf("Total elapsed time: %10.6f\n", elapsed_time);
	}

	MPI_Finalize();
	
	return 0;
}
