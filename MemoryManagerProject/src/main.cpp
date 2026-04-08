#include "MemoryPool.h"
#include "SmartPtr.h"
#include <iostream>

int main() {
    //测试内存池
    MemoryPool pool(sizeof(int), 10);
    

    int* a = (int*)pool.allocate();
    *a = 42;
    std::cout << "MemoryPool Value: " << *a << std::endl;

    pool.deallocate(a);

    //测试智能指针
    SmartPtr<int> p(new int(100));
    std::cout << "SmartPtr Value: " << *p << std::endl;

    return 0;

}