#include "../includes/heap.h"

void* heapStart;
void* heapEnd;
header_t* lastHdr;
PageTableManager manageer;

void init_heap(void* heapAddress, size_t heapLength) {
    void* pos = heapAddress;
    // manageer = manager;
    for (size_t i = 0; i < heapLength; i++)
    {
        MapMemory(pos, RequestPage(), g_Pagetablemanager);
        pos = (void*)((size_t)pos + 0x1000);
    }

    size_t heaplen = heapLength * 0x1000;

    heapStart = heapAddress;
    heapEnd = (void*)((size_t)heapStart + heaplen);
    header_t* startSeg = (header_t*)heapAddress;
    startSeg->size = heaplen - sizeof(header_t);  
    startSeg->head = NULL;
    startSeg->tail = NULL;
    startSeg->free = true;
    lastHdr = startSeg;
}

void CombineForward(header_t* self) {
    if(self->head == NULL) return;
    if(!self->head->free) return;

    if(self->head == lastHdr) lastHdr == self;

    if(self->head->head != NULL) {
        self->head->head->tail = self;
    }

    self->size = self->size + self->head->size + sizeof(header_t);
}

void CombineBackward(header_t* self) {
    if(self->tail != NULL && self->tail->free) CombineForward(self->tail);
}

void expandHeap(size_t length) {
    if(length % 0x1000) {
        length -= length % 0x1000;
        length += 0x1000;
    }

    size_t pageCount = length / 0x1000;
    header_t* newSegHdr = (header_t*)heapEnd;

    for (size_t i = 0; i < pageCount; i++)
    {
        MapMemory(heapEnd, RequestPage(), g_Pagetablemanager);
        heapEnd = (void*)((size_t)heapEnd + 0x1000);
    }

    newSegHdr->free = true;
    newSegHdr->tail = lastHdr;
    lastHdr->head = newSegHdr;
    lastHdr = newSegHdr;
    newSegHdr->head = NULL;
    newSegHdr->size = length - sizeof(header_t);
    CombineBackward(newSegHdr);
    
}


header_t* Split(header_t* self, size_t SplitLength) {
    if(SplitLength < 0x10) return NULL;
    int64_t SplitSegLength = self->size - SplitLength - (sizeof(header_t));
    if(SplitSegLength < 0x10) return NULL;

    header_t* newSplitHdr = (header_t*) ((size_t)self + SplitLength + sizeof(header_t));
    self->head->tail = newSplitHdr;
    newSplitHdr->head = self->head;
    self->head = newSplitHdr;
    newSplitHdr->tail = self;
    newSplitHdr->size = SplitSegLength;
    newSplitHdr->free = self->free;
    self->size = SplitLength;

    if(lastHdr == self) lastHdr = newSplitHdr;
    return newSplitHdr;
}

void* malloc(size_t size) {
    if(size % 0x10 > 0) {
        size -= (size % 0x10);
        size += 0x10;
    } 

    if(size == 0) return NULL;

    header_t* currentSeg = (header_t*)heapStart;
    while (true)
    {
        if(currentSeg->free) {
            if(currentSeg->size > size) {
                Split(currentSeg, size);
                currentSeg->free = false;
                return (void*)((uint64_t)currentSeg + sizeof(header_t));
            }
            if(currentSeg->size == size) {
                currentSeg->free = false;
                return (void*)((uint64_t)currentSeg + sizeof(header_t));
            }
        }
        if(currentSeg->head == NULL) break;
        currentSeg = currentSeg->head;
    }
    expandHeap(size);
    return malloc(size);
    
}

void free(void* address) {
    header_t* segment = (header_t*)address - 1;
    segment->free = true;
    CombineForward(segment);
    CombineBackward(segment);
}

