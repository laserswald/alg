// alg.h
/*
 * Type generic algorithm tools. You will want this if you are dealing with
 * arrays of... well, anything.
 *
 * The array algorithms are inspired by and work just like bsearch and qsort
 * from the standard library.
 */
#ifndef ALGORITHMS_H

#define ALGORITHMS_H

#include <stdlib.h>

// Compare anything, with either memcmp or a deep comparison.
/*
 * Returns a positive number if a > b, a negative number if a < b, and 0 if equal.
 * Just like Grandpa Dennis used to make.
 */
int compare(void* a, void* b, const size_t size, int (*deep)(void*, void*));

// Get either the larger or smaller of two items, using generic comparison.
void* max(void* a, void* b, const size_t size, int (*cmp)(void*, void*));
void* min(void* a, void* b, const size_t size, int (*cmp)(void*, void*));

// Clamp to a range using compare().
/*
 * Returns lo if i is less than lo.
 * Returns hi if i is greater than hi.
 * Returns i otherwise.
 */
void* clamp(void* i, void* lo, void* hi, const size_t size, int (*cmp)(void*, void*));


// Swap the data at two pointers.
/*
 * This is a shallow swap, which means it won't deeply copy things within the pointers.
 *
 * This is also a slow, but safe, wrapper over memmove. If you need something faster, use
 * unsafe_swap, which uses memcpy. All algorithms below use unsafe_swap, because we know
 * that memory won't overlap in those cases.
 */
void swap(void* a, void* b, const size_t itemsize);
void unsafe_swap(void* a, void* b, const size_t itemsize);

//// We already have qsort and bsearch, this should help round out the algorithms.

// Given an array, remove all adjacent entries that compare the same.
/*
 * Returns the new length of the array.
 */
size_t unique(void *base, const size_t length, const size_t itemsize, int (*cmp)(void*, void*));

// Arrange the items in the array so they satisfy the heap property.
/*
 * After you use this function, the array can be treated like a tree, where
 * an element i's left child is located at i*2, and right child is located at
 * (i*2)+1.
 *
 * This arranges the array so that each parent compares larger than either of it's
 * children.
 */
void heapify(void *base, const size_t length, const size_t itemsize, int (*cmp)(void*, void*));

// Arrange the items in the array randomly.
/*
 * This algorithm is simply an implementation of the in-place Fisher-Yates
 * (aka Knuth) shuffle.
 *
 * You need to seed the random number generator before you use this
 * with srand().
 */
void shuffle(void *base, const size_t length, const size_t itemsize);

// Arrange the items in the array in the opposite direction.
void reverse(void *base, const size_t length, const size_t itemsize);

#endif /* end of include guard: ALGORITHMS_H */

