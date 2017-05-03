#include <stdio.h>
#include <time.h>
#include <string.h>
#include <assert.h>

#include "alg.h"

// Compare two values.
int compare(void* a, void* b, const size_t size, int (*deep)(void*, void*)){
    if (deep != NULL) {
        return deep(a, b);
    } else {
        // This should probably have a more formal exit.
        assert(size != 0);
        return memcmp(a, b, size);
    }
}

void* max(void* a, void* b, const size_t size, int (*cmp)(void*, void*)){
    return (compare(a, b, size, cmp) > 0) ? a : b;
}

void* min(void* a, void* b, const size_t size, int (*cmp)(void*, void*)){
    return (compare(a, b, size, cmp) < 0) ? a : b;
}

void* clamp(void* i, void* lo, void* hi, const size_t size, int (*cmp)(void*, void*)){
    if (compare(i, lo, size, cmp) < 0)
        return lo;
    else if (compare(i, hi, size, cmp) > 0)
        return hi;
    else
        return i;
}

// This is much faster, but you need to make sure the memory doesn't overlap.
void unsafe_swap(void* a, void* b, const size_t itemsize) {
    char* buffer = malloc(itemsize);

    memcpy(buffer, a, itemsize);
    memcpy(a, b, itemsize);
    memcpy(b, buffer, itemsize);

    free(buffer);
}

// This is slower, but should be pretty reliable.
void swap(void* a, void* b, const size_t itemsize) {
    char* buffer = malloc(itemsize);

    memmove(buffer, a, itemsize);
    memmove(a, b, itemsize);
    memmove(b, buffer, itemsize);

    free(buffer);
}


/**
 * Filter out repititions from a sorted array, in place.
 *
 * Yeah, I could have named it `uniq` in reference to the command but
 * it's still less than 6 chars, which is fiiiiine
 */
size_t unique(void* array, const size_t length, const size_t itemsize, int (*cmp)(void*, void*)){

    // The new size of this array.
    size_t new_size = length;

    // start off at the beginning of the array
    size_t current = 0;
    void* currentp = array;

    // We are gonna iterate over the entire array here.
    while (current < new_size) {
        size_t next = current + 1;
        void *nextp = (char*) array + (itemsize * next);

        // Find the next item that's different from the current item
        while (compare(currentp, nextp, itemsize, cmp) == 0){
            nextp = (char*) nextp + itemsize;
            next++;
        }

        // Only move it if it isn't right next to the current
        if (next != current + 1){

            // We need to move it to the spot AFTER the first in this "run"
            currentp = (char*) currentp + itemsize;

            // We need to move all the data from nextp to the end of the array, so
            // how much is that?
            size_t rest = new_size - next;
            memmove(currentp, nextp, (rest * itemsize));

            // We then reduce the new size by how much we removed.
            new_size -= next - current;
        }

        current++;
    }

    return new_size;
}

// Recursive is easier for this one...
static
void heapify_rec(void* base, const size_t length, const size_t itemsize, int (*cmp)(void*, void*), size_t index){

    // Base cases.

    // This index is past the end of the array, I can't heapify this!
    if (index >= length) return;

    size_t left_ind = index * 2,
           right_ind = (index * 2) + 1;

    // If we have no children, left will be past the end of the array.
    if (left_ind >= length) return;

    void *left = (char*) base + (itemsize * left_ind),
         *right = (char*) base + (itemsize * right_ind);

    // If we have a root with only one child, it will always be the
    // left child. We only need to check and swap root and left.
    if (right_ind >= length) {
        if (compare(base, left, itemsize, cmp) < 0){
            unsafe_swap(base, left, itemsize);
        }
        return;
    }

    // If we are getting here, we have two children and therefore can have
    // grandchildren. Heapify both right and left children
    heapify_rec(left, itemsize, length, cmp, left_ind);
    heapify_rec(right, itemsize, length, cmp, right_ind);

    // Now both sides are heapy, we need to heapify this part.
    if (compare(base, left, itemsize, cmp) < 0 || compare(base, right, itemsize, cmp) < 0){
        void* larger = max(left, right, itemsize, cmp);
        unsafe_swap(base, larger, itemsize);
    }

}

// An easier way to call the above recursive function
void heapify(void* base, const size_t length, const size_t itemsize, int (*cmp)(void*, void*)){
    heapify_rec(base, itemsize, length, cmp, 0);
}

// Everyone do the Knuth shuffle!
void shuffle(void *base, const size_t length, const size_t itemsize){
    size_t shuffled = 0;
    while (shuffled < length) {
        // Get a random index from the section we haven't shuffled
        size_t rnd = rand() % (length - shuffled);

        // Swap that with the leftmost unshuffled index
        void *to = (char*) base + (itemsize * shuffled);
        void *from = (char*) base + (itemsize * rnd);
        unsafe_swap(to, from, itemsize);

        shuffled++;
    }
}

// n/2 reverse algorithm. Should be fastest?
void reverse(void *base, const size_t length, const size_t itemsize){
    for (size_t i = 0; i < (length/2); ++i){
        // front
        void *front = (char*) base + (itemsize * i);
        // back
        void *back = (char*) base + (itemsize * (length - (i+1)));

        unsafe_swap(front, back, itemsize);
    }
}

