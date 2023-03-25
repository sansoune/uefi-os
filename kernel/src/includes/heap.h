#pragma once
#include "stdint.h"
#include "paging.h"
#include "pageframeAlloc.h"

typedef struct header_t header_t;
struct header_t{
    size_t size;
    bool free;
    header_t *head;
    header_t *tail;
};

void init_heap(void* heapAddress, size_t heapLength, PageTableManager manager);

void* malloc(size_t size);
void free(void* address);
void expandHeap(size_t length);