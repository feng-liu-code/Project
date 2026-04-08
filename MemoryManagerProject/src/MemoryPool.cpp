#include "MemoryPool.h"
#include <iostream>

MemoryPool::MemoryPool(size_t size, size_t count)
{
    size_t align = alignof(std::max_align_t);

    blockSize = std::max(size, sizeof(void*));
    blockSize = ((blockSize + align - 1) / align) * align;
    std::cout << "blockSize=" << blockSize << std::endl;

    blockCount = count;

    memory = new char[blockSize * blockCount];
    freeList = memory;

    for (size_t i = 0; i < blockCount - 1; ++i) {
        *(void**)(memory + i * blockSize) = memory + (i + 1) * blockSize;
    }
    *(void**)(memory + (blockCount - 1) * blockSize) = nullptr;
}

MemoryPool::~MemoryPool() {
    delete[] memory;
}

void* MemoryPool::allocate() {
    if(!freeList) return nullptr;

    void* block = freeList;
    freeList = *(void**)freeList;
    return block;
}

void MemoryPool::deallocate(void *ptr) {
    *(void**)ptr = freeList;
    freeList = ptr; 
}