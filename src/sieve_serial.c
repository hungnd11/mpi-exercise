/*
 * ===================================================================================== 
 *       Filename:  sieve_serial.c
 *
 *    Description:  Implement Sieve of Eratosthenes serial algorithm
 *
 *        Version:  0.1
 *       Compiler:  gcc
 *
 *         Author:  hungnd11
 *   Organization:  HUST
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>


long
run_sieve(long n, bool print_results)
{
	/* Create a boolean array is_prime[0..n] and initialize all entries in it to true.
	 * Eventually, is_prime[i] is true if i is a prime number and false otherwise.
	 */
	bool* is_prime = (bool*) malloc(sizeof(bool) * (n + 1));
	is_prime[0] = false;
	is_prime[1] = false;

	for(int i = 2; i < n + 1; i++)
	{
		is_prime[i] = true;
	}

	int n_primes = 0;

	for(int p = 2; p * p < n + 1; p++)
	{
		// if is_prime[p] is not changed, it is a prime number
		if(is_prime[p] == true)
		{
			// all multiples of p are NOT prime numbers
			for(int i = p * 2; i < n + 1; i += p)
			{
				is_prime[i] = false;
			}
		}
	}

	// count the number of prime numbers not greater than n
	// and print results if print_results is set to true
	for(int i = 2; i < n + 1; i++)
	{
		if(is_prime[i])
		{
			n_primes++;
			if(print_results)
			{
				printf("\t%d\t", i);
			}
		}
	}

	return n_primes;
}


double 
time_of_sieve(long size)
{
	clock_t tic = clock();
	long count = run_sieve(size, false);
	printf("%ld primes are less than or equal to %ld\n", count, size);
	clock_t toc = clock();

	return (double) (toc - tic) / CLOCKS_PER_SEC;
}


/* Measure the average time of sieve in a number of runs
 *   n_runs: the number of runs
 *   size: size of sieve
 *   return: the average time measured in 'n_runs' runs
 */
double
avg_time(int size, int n_runs)
{
	if (n_runs != 0)
	{
		double total_time = 0.0;
		
		for(int i = 0; i < n_runs; i++)
		{
			total_time += time_of_sieve(size);
		}
		
		return total_time / n_runs;
	} else {
		return -1.0;
	}

}


int
main(int argc, char const *argv[])
{
	if(argc != 2){
		fprintf(stderr, "%s\n", "Usage: Specified the number you would like to perform Sieve of Eratosthenes.");
		return -1;
	}

	long n = atoi(argv[1]);
	
	printf("\nEllapsed time %f\n", time_of_sieve(n));

	return 0;
}