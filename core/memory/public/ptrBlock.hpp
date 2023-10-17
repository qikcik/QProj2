#pragma once
#include <memory>
#include <unordered_map>
#include "uuid.h"

class PtrBlock
{
public:
    inline static PtrBlock* createBlock(const std::string& id) {
        auto block = new PtrBlock();
        block->refCount = 1;
        block->id = id;

        if(blocks.find(block->id) != blocks.end()) {
            //TODO NOTIFY ABOUT FALLBACK TO UUID
            std::random_device rd;
            auto seed_data = std::array<int, std::mt19937::state_size> {};
            std::generate(std::begin(seed_data), std::end(seed_data), std::ref(rd));
            std::seed_seq seq(std::begin(seed_data), std::end(seed_data));
            std::mt19937 generator(seq);
            uuids::uuid_random_generator gen{generator};
            block->id = uuids::to_string(gen());
        }

        blocks[block->id] = block;
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

    inline const std::string& getId() {
        return id;
    }

    static PtrBlock* resolveSoftPtr(const std::string& in_id) {
        auto it = blocks.find(in_id);
        if(it != blocks.end())
            return it->second;
        return nullptr;
    }

protected:
    PtrBlock() = default;

protected:
    int refCount {0};
    void* ptr {nullptr};
    std::string id;

    static std::unordered_map<std::string,PtrBlock*> blocks;
};