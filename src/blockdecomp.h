/*
 * ===================================================================================== 
 *       Filename:  block_decomp.h
 *
 *    Description:	Block Decomposition Macros
 *         Author:  hungnd11@github.com
 *   Organization:  HUST
 * =====================================================================================
 */

/* Parameters: 
 *   id: process rank
 *   p: number of processes
 *   n: number of elements
 *   index: array index of an element
 * Macros:
 *   BLOCK_LOW: the first index controlled by process
 *   BLOCK_HIGH: the last index controlled by process
 *   BLOCK_SIZE: the number of elements controlled by process 'id'
 *   BLOCK_OWNER: the rank of the process coltrolling that element of the array
 */
#define BLOCK_LOW(id, p, n) ((id) * (n) / (p))
#define BLOCK_HIGH(id, p, n) (BLOCK_LOW((id) + 1, p, n) - 1)
#define BLOCK_SIZE(id, p, n) (BLOCK_LOW((id) + 1, (p), (n)) - BLOCK_LOW((id), (p), (n)))
#define BLOCK_OWNER(index, p, n) (((p) * ((index) + 1) - 1) / (n))

#define MIN(a, b) ((a) < (b) ? (a) : (b))