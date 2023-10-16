#pragma once
#include <memory>

class PtrBlock
{
public:
    inline static PtrBlock* createBlock() {
        auto block = new PtrBlock();
        block->refCount = 1;
        return block;
    }

    inline static void removeRef(PtrBlock* in_block) {
        if(!in_block) return;

        in_block->refCount--;
        if(in_block->refCount <= 0)
            delete in_block;
    }

    inline static PtrBlock* addRef(PtrBlock* in_block) {
        if(in_block)
            in_block->refCount++;
        return in_block;
    }

    inline void allocateInstance(size_t in_memorySize) {
        if(ptr) deallocateInstance();
        ptr = new uint8_t[in_memorySize];
    }

    inline void deallocateInstance() {
        if(!ptr) return;
        delete[] (uint8_t*)ptr;
    }

    inline void* getPtr() {
        return ptr;
    }

protected:
    PtrBlock() = default;

protected:
    int refCount {0};
    void* ptr {nullptr};
};