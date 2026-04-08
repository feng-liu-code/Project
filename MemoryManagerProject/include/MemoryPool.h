#ifndef MEMORYPOOL_H
#define MEMORYPOOL_H

#include <cstddef>

class MemoryPool {
    public:
        MemoryPool(size_t blockSize, size_t blockCount);
        ~MemoryPool();

        void* allocate(); //分配
        void deallocate(void* ptr); //释放
    
        private:
            size_t blockSize; //块大小
            size_t blockCount; //块计数
            char* memory; //内存
            void* freeList; //空闲列表
};

#endif