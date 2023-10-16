#pragma once
#include "macros.hpp"
#include "ptrBlock.hpp"
#include "weakPtr.hpp"

template<typename TType>
class OwnerPtr
{
public:
    template <typename... TArgs>
    static OwnerPtr<TType> createInstance(TArgs&&... args)  {
        OwnerPtr<TType> result {};
        result.block->allocateInstance(sizeof(TType));
        new (result.block->getPtr()) TType(std::forward<TArgs>(args)...);
        return std::move(result);
    };

    OwnerPtr() : block(PtrBlock::createBlock()) {}
    ~OwnerPtr() {
        if(block && block->getPtr()) {
            reinterpret_cast<TType*>(block->getPtr())->~TType();
            block->deallocateInstance();
        }
        PtrBlock::removeRef(block);
    };

    OwnerPtr(const OwnerPtr& other) = delete;
    OwnerPtr& operator=(OwnerPtr& other) = delete;

    OwnerPtr(const OwnerPtr&& other) noexcept {
        if(this == &other) return;

        block = other.block;
        other.block = nullptr;
    };

    // Move from derivered class
    template<typename TOther>
    requires std::derived_from<TOther,TType>
    OwnerPtr(OwnerPtr<TOther>&& other) {
        //if(this == &other) return;
        block = other.block;
        other.block = nullptr;
    };

    GEN_MOVE_ASSIGMENT_OPERATOR(OwnerPtr)

    template<typename TOther>
    requires std::derived_from<TOther,TType>
    OwnerPtr<TOther> cast() {
        return OwnerPtr<TOther>(std::move(*this));
    }


    operator WeakPtr<TType>() const {
        return WeakPtr<TType>(block);
    }

    TType* getPtr() {
        if(!block) return nullptr;
        return reinterpret_cast<TType*>(block->getPtr());
    };

    const TType* getPtr() const {
        if(!block) return nullptr;
        return reinterpret_cast<TType*>(block->getPtr());
    };

protected:
    mutable PtrBlock* block;

    template<typename TOther>
    friend class OwnerPtr;
};