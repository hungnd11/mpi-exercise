/*
 * ===================================================================================== 
 *       Filename:  sieve_parallel_improved.c
 *
 *    Description:  Implement Sieve of Eratosthenes parallel algorithm
 *					All even numbers are eliminated from the computation
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


int main(int argc, char *argv[])
{
	double elapsed_time; 		// total elapsed time of the program
	int id;						// process id
	int p;						// the number of processes
	
	MPI_Init(&argc, &argv);

	MPI_Barrier(MPI_COMM_WORLD);
	elapsed_time = -MPI_Wtime();

	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	MPI_Comm_size(MPI_COMM_WORLD, &p);

	if(argc != 2)
	{
		if(!id)
		{
			printf("Usage: sieve_parallel_improved <n>\n");
			MPI_Finalize();
			exit(1);
		}
	}

	int n = atoi(argv[1]);


	int low_value = 2 + BLOCK_LOW(id, p, n - 1);
	int high_value = 2 + BLOCK_HIGH(id, p, n - 1);
	int block_size = BLOCK_SIZE(id, p, n - 1);

	if(!(low_value % 2))
	{
		if(!(high_value % 2))
		{
			block_size = (int) floor((double) block_size / 2.0);
			high_value--;
		} else {
			block_size = block_size / 2;
		}
		low_value++;
	} else {
		if(!(high_value % 2))
		{
			block_size = block_size / 2;
			high_value--;
		} else {
			block_size = (int) ceil((double) block_size / 2.0);
		}
	}

	int temp = (n - 1) / p;

	if((2 + temp) < (int) sqrt((double) n))
	{
		if(!id)
		{
			printf("Too many processes!\n");
			printf("The number of processes should be greater or equal than sqrt(n)\n");
		}
		MPI_Finalize();
		exit(1);
	}

	char* marked = (char *) malloc(block_size * sizeof(char));
	if(marked == NULL)
	{
		printf("Not enough memory\n");
		MPI_Finalize();
		exit(1);
	}

	for(int i = 0; i < block_size; i++)
	{
		marked[i] = 0;
	}

	int first_index = 0;
	if(!id)
	{
		first_index = 0;
	}

	int k = 3;
	int prime_index = 0;
	int global_count = 1;

	do
	{
		if(k >= low_value)
		{
			first_index = (k - low_value) / 2 + k;
		} else if(k * k > low_value)
		{
			first_index = (k * k - low_value) / 2;
		} else {
			if(!(low_value % k))
			{
				first_index = 0;
			} else {
				first_index = 1;
				while((low_value + (2 * first_index)) % k)
					++first_index;
			}
		}
		
		for(int i = first_index; i < block_size; i += k)
		{
			marked[i] = 1;
		}

		if(!id)
		{
			while(marked[++prime_index]);
			k = 3 + prime_index * 2;
		}

		MPI_Bcast(&k, 1, MPI_INT, 0, MPI_COMM_WORLD);
	} while(k * k <= n + 1);

	int local_count = 0;
	for(int i = 0; i < block_size; i++)
	{
		if(!marked[i])
		{
			++local_count;
		}
	}
	
	MPI_Reduce(&local_count, &global_count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

	elapsed_time += MPI_Wtime();

	if(id == 0)
	{
		printf("%d primes are less than or equal to %d\n", (global_count + 1), n);
		printf("Total elapsed time: %10.6f\n", elapsed_time);	
	}

	free(marked);
	marked = 0;

	MPI_Finalize();
	return 0;
}