#ifndef SMARTPTR_H
#define SMARTPTR_H

template<typename T>
class SmartPtr {
public:
    explicit SmartPtr(T* ptr = nullptr) : ptr(ptr) {}

    ~SmartPtr() {
        delete ptr;
    }

    T& operator*() { return *ptr; }
    T* operator->() { return ptr; }

private:
    T* ptr;
};

#endif