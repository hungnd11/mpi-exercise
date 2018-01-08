/*
 * ===================================================================================== 
 *       Filename:  block_decomp.h
 *
 *    Description:	Block Decomposition Macros
 *         Author:  hungnd11@github.com
 *   Organization:  HUST
 * =====================================================================================
 */

/** 
 * BLOCK_LOW
 * Returns the index at the start of a local array 
 * with regards to block decomposition of a global array
 *
 * param id (int) process rank
 * param p 	(int) total number of processes
 * param n 	(int) size of global array
 * return 	(int) offset at the start of local array
 */
#define BLOCK_LOW(id, p, n) ((id) * (n) / (p))
/**
 * BLOCK_HIGH
 * Returns the index immediately after the end of a local array 
 * with regards to block decomposition of a global array
 * 
 * param id (int) process rank
 * param p 	(int) total number of processes
 * param n 	(int) size of global array
 * return 	(int) offset at the end of local array
 */
#define BLOCK_HIGH(id, p, n) (BLOCK_LOW((id) + 1, (p), (n)) - 1)
/**
 * BLOCK_SIZE
 * Returns the size of a local array 
 * with regards to block deomposition of a global array
 * 
 * param id (int) process rank
 * param p 	(int) total number of processes
 * param n  (int) size of global array
 * return 	(int) size of the local array
 */
#define BLOCK_SIZE(id, p, n) (BLOCK_LOW((id) + 1, (p), (n)) - BLOCK_LOW((id), (p), (n)))
/**
 * BLOCK_OWNER
 * Returns the rank of the process that handles a certain local array
 * with regards to block decomposition of a global array
 *
 * param index 	(int) index in global array
 * param p 		(int) total number of processes
 * param n 		(int) size of global array
 * return 		(int) rank of process that hangles index
 */
#define BLOCK_OWNER(index, p, n) (((p) * ((index) + 1) - 1) / (n))
/**
 * MIN
 * Returns the minimum number between 2 numbers
 * 
 * param a 	(int) number 'a'
 * param b 	(int) number 'b'
 * return 	(int) the number smaller between a and b
 */
#define MIN(a, b) ((a) < (b) ? (a) : (b))