/*
language: C.

*/
#pragma once

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define HCAPACITY 1024
#ifndef HeapDataType
#define HeapDataType int
#endif // !HeapDataType

typedef struct Heap {
    HeapDataType* data;
    int size;
    int capacity;
    bool (*cmp)(HeapDataType, HeapDataType);
}Heap;

Heap* newHeap(bool (*cmp)(HeapDataType, HeapDataType)) {
    Heap* heap = (Heap*)malloc(sizeof(Heap));
    if (heap == NULL) exit(EOVERFLOW);
    heap->data = (HeapDataType*)malloc(HCAPACITY * sizeof(HeapDataType));
    heap->capacity = HCAPACITY;
    heap->size = 0;
    heap->cmp = cmp;
    return heap;
}

void destroyHeap(Heap* heap) {
    free(heap->data);
    free(heap);
}

bool pushHeap(Heap* heap, HeapDataType value) {
    if (heap->size >= heap->capacity) {
        return false;
    }
    heap->data[heap->size++] = value;
    int i = heap->size - 1;
    while (i > 0 && heap->cmp(heap->data[i], heap->data[(i - 1) / 2])) {
        HeapDataType tmp = heap->data[i];
        heap->data[i] = heap->data[(i - 1) / 2];
        heap->data[(i - 1) / 2] = tmp;
        i = (i - 1) / 2;
    }
    return true;
}

HeapDataType getTopHeap(Heap* heap) {
    if (heap->size <= 0) {
        // 返回一个无用的值
        HeapDataType tmp;
        memset(&tmp, 0, sizeof(HeapDataType));
        return tmp;
    }
    return heap->data[0];
}

bool popHeap(Heap* heap) {
    if (heap->size <= 0) {
        return false;
    }
    heap->size--;
    heap->data[0] = heap->data[heap->size];
    int i = 0;
    while (i * 2 + 1 < heap->size) {
        int left = i * 2 + 1, right = i * 2 + 2;
        int smallerChild = left;
        if (right < heap->size && heap->cmp(heap->data[right], heap->data[left])) {
            smallerChild = right;
        }
        if (heap->cmp(heap->data[smallerChild], heap->data[i])) {
            HeapDataType tmp = heap->data[smallerChild];
            heap->data[smallerChild] = heap->data[i];
            heap->data[i] = tmp;
            i = smallerChild;
        }
        else {
            break;
        }
    }
    return true;
}

bool isEmptyHeap(Heap* heap) {
    return heap->size == 0;
}



