#pragma once
#include "ptrBlock.hpp"
#include "macros.hpp"

template<typename TType>
class WeakPtr
{
public:
    using element_type = TType;

    WeakPtr() = default;
    explicit WeakPtr(const std::string& in_soft_Id) : soft_id(in_soft_Id) {}
    ~WeakPtr() {
        PtrBlock::removeRef(block);
        soft_id = "";
    };

    WeakPtr(const WeakPtr& other) {
        block = PtrBlock::addRef(other.block);
        if(block) soft_id = block->getId();
    };

    template<std::derived_from<TType> TOther>
    WeakPtr(const WeakPtr<TOther>& other) {
        block = PtrBlock::addRef(other.block);
        if(block) soft_id = block->getId();
    };
    GEN_COPY_ASSIGMENT_OPERATOR(WeakPtr)

    WeakPtr(WeakPtr&& other)  noexcept {
        if(this == &other) return;

        block = other.block;
        if(block) soft_id = block->getId();

        other.block = nullptr;
    };

    template<std::derived_from<TType> TOther>
    WeakPtr(WeakPtr<TOther>&& other)  noexcept {
        if(this == reinterpret_cast<WeakPtr<TType>*>(&other)) return;

        block = other.block;
        if(block) soft_id = block->getId();

        other.block = nullptr;
    };
    GEN_MOVE_ASSIGMENT_OPERATOR(WeakPtr)

    bool tryResolveSoftPtr() {
        if(!block) {
            auto resolved = PtrBlock::resolveSoftPtr(soft_id);
            if(resolved) {
                block = PtrBlock::addRef(resolved);
                return true;
            }
        }
        return false;

    }

    TType* getPtr() {
        if(!block) tryResolveSoftPtr();
        if(!block) return nullptr;

        return reinterpret_cast<TType*>(block->getPtr());
    };

    const TType* getPtr() const {
        if(!block) return nullptr;
        return reinterpret_cast<TType*>(block->getPtr());
    };

    std::string getId() const {
        if(block)
            return block->getId();
        return soft_id;
    }

    WeakPtr(PtrBlock* in_block) {
        block = PtrBlock::addRef(in_block);
        if(block) soft_id = block->getId();
    };

    template<typename TOther>
    WeakPtr<TOther> cast() {
        return  WeakPtr<TOther>(block);
    };


protected:
    PtrBlock* block {nullptr};
    std::string soft_id {};

    template<typename TOther>
    friend class WeakPtr;
};