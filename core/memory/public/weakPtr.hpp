#pragma once
#include "ptrBlock.hpp"
#include "macros.hpp"

template<typename TType>
class WeakPtr
{
public:
    WeakPtr() = default;
    ~WeakPtr() {
        PtrBlock::removeRef(block);
    };

    WeakPtr(const WeakPtr& other) {
        block = PtrBlock::addRef(other.block);
    };
    GEN_COPY_ASSIGMENT_OPERATOR(WeakPtr)

    WeakPtr(WeakPtr&& other)  noexcept {
        if(this == &other) return;

        block = other.block;
        other.block = nullptr;
    };
    GEN_MOVE_ASSIGMENT_OPERATOR(WeakPtr)

    TType* getPtr() {
        if(!block) return nullptr;
        return reinterpret_cast<TType*>(block->getPtr());
    };

    const TType* getPtr() const {
        if(!block) return nullptr;
        return reinterpret_cast<TType*>(block->getPtr());
    };

    explicit WeakPtr(PtrBlock* in_block) {
        block = PtrBlock::addRef(in_block);
    };

protected:
    PtrBlock* block {nullptr};
};