#include <stdio.h>

#include "alg.h"

void printints(int *array, size_t length){
    for(int i = 0; i < length; i++){
        printf("%d ", array[i]);
    }
    puts("");
}

int intcmp(const void* a, const void* b){
    int alpha = *(const int*)a;
    int beta = *(const int*)b;
    return alpha - beta;
}


int main(int argc, char** argv){
    int items[] = {1, 2, 3, 4, 5};
    printf("%d\n", *(int*) max(items + 1, items + 2, sizeof(int), NULL));
    printf("%d\n", *(int*) min(items + 1, items + 2, sizeof(int), NULL));
    printints(items, 5);

    srand(time(NULL));
    shuffle(items, sizeof(int), 5);
    printints(items, 5);

    qsort(items, 5, sizeof(int), intcmp);
    printints(items, 5);

    reverse(items, sizeof(int), 5);
    printints(items, 5);

}
