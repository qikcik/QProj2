#pragma once
#include "macros.hpp"
#include "ptrBlock.hpp"
#include "weakPtr.hpp"
#include "weakFromThis.hpp"

template<typename TType>
class OwnerPtr
{
public:
    using element_type = TType;


    template <typename... TArgs>
    static OwnerPtr<TType> CreateWithInstanceWithId(const std::string& id,TArgs&&... args)  {
        OwnerPtr<TType> result{id};
        result.block->allocateInstance(sizeof(TType));
        new (result.block->getPtr()) TType(std::forward<TArgs>(args)...);

        auto weakFromThis = dynamic_cast<WeakFromThis*>((TType*)result.block->getPtr());
        if(weakFromThis)
            weakFromThis->setSelfWeak( WeakPtr<TType>(result.block).template cast<void>());

        return std::move(result);
    };

    template <typename... TArgs>
    static OwnerPtr<TType> CreateWithInstance(TArgs&&... args)  {
        OwnerPtr<TType> result{};
        result.block->allocateInstance(sizeof(TType));
        new (result.block->getPtr()) TType(std::forward<TArgs>(args)...);

        auto weakFromThis = dynamic_cast<WeakFromThis*>((TType*)result.block->getPtr());
        if(weakFromThis)
            weakFromThis->setSelfWeak( WeakPtr<TType>(result.block).template cast<void>());

        return std::move(result);
    };

    template <typename... TArgs>
    void createInstance(TArgs&&... args)  {
        block->allocateInstance(sizeof(TType));
        new (block->getPtr()) TType(std::forward<TArgs>(args)...);

        auto weakFromThis = dynamic_cast<WeakFromThis*>((TType*)block->getPtr());
        if(weakFromThis)
            weakFromThis->setSelfWeak( WeakPtr<TType>(block).template cast<void>());
    };

    //empty unique id - means auto-generated
    explicit OwnerPtr(const std::string& unique_id = "") : block(PtrBlock::createBlock(unique_id)) {}

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
    OwnerPtr<TOther> moveCast() {
        return OwnerPtr<TOther>(std::move(*this));
    }

    operator WeakPtr<TType>() const {
        return WeakPtr<TType>(block);
    }

    WeakPtr<TType> getWeak() const {
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

    std::string getId() const {
        return block->getId();
    }

protected:
    mutable PtrBlock* block;

    template<typename TOther>
    friend class OwnerPtr;
    friend class OwnerObjPtrField;
};