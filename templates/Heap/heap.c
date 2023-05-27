/***

language: C.
***/

#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct myStruct {
    int x;
}myStruct;
//
//bool myCmp(myStruct a, myStruct b) {
//    return a.x > b.x;
//}

bool myCmp(int a, int b) {
    return a > b;
}

#define HeapDataType int
#include "heap.h"

int main(int argc, char const **argv) {
	//freopen("heap.in", "r", stdin);
	//freopen("heap.out", "w", stdout);

    int a[10] = { 2, 6, 4, 9, 1, 8, 5, 3, 7, 0 };
    Heap* heap = newHeap(&myCmp);
    for (int i = 0; i < 10; i++) {
        pushHeap(heap, a[i]);
    }
    while (!isEmptyHeap(heap)) {
        printf("%d ", getTopHeap(heap));
        popHeap(heap);
    }
    printf("\n");

    return 0;
}

