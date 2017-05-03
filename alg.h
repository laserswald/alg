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


#include <string.h>
#include <stdlib.h>
#include <assert.h>

// Compare anything.
//
// Note: if deep is NULL, it will just use memcmp. The More You Know.
//
// Note x2 Combo: If deep is NOT null, size can be 0. Also the more you know.
int compare(void* a, void* b, const size_t size, int (*deep)(void*, void*));

// Generic max and min using compare().
// Same rules apply to this as compare().
void* max(void* a, void* b, const size_t size, int (*cmp)(void*, void*));
void* min(void* a, void* b, const size_t size, int (*cmp)(void*, void*));

// Clamp to a range using compare().
void* clamp(void* i, void* lo, void* hi, const size_t size, int (*cmp)(void*, void*));

// Swap two places in memory. Super useful and should have been in the stdlib.
void swap(void* a, void* b, const size_t itemsize);

// We already have qsort and bsearch, let's implement other stuff we might need!

// Remove repititions, just like the Unix utility.
//
// Returns the new length of the array.
size_t unique(void *base, const size_t length, const size_t itemsize, int (*cmp)(void*, void*));

// Turn this array into a heap.
void heapify(void *base, const size_t length, const size_t itemsize, int (*cmp)(void*, void*));

// In-place Fisher-Yates (aka Knuth) shuffle.
void shuffle(void *base, const size_t length, const size_t itemsize);

// In-place reversal.
void reverse(void *base, const size_t length, const size_t itemsize);

#endif /* end of include guard: ALGORITHMS_H */

