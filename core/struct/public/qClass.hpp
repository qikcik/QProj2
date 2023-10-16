#pragma once
#include "memory"
#include "dynamicArray.tpp"
#include "ownerPtr.hpp"

#include <functional>
#include "field.hpp"

class QObj {};

class QClass
{
public:
    QClass(
            std::string in_name,
            size_t in_size,
            const std::function<void(QObj* in_addr)>& in_constructInstance,
            const std::function<void(QObj* in_addr)>& in_destructInstance,
            DynamicArray<Field>&& in_fields
        ):
            name(std::move(in_name)),
            memorySize(in_size),
            constructInstance(in_constructInstance),
            destructInstance(in_destructInstance),
            fields(std::move(in_fields))
        {}

    virtual ~QClass() = default;

    const DynamicArray<Field>& getFields() const;
    Field* getField(const std::string& in_name) const;

    const std::string name;
    const size_t memorySize;

    const std::function<void(QObj* in_addr)> constructInstance;
    const std::function<void(QObj* in_addr)> destructInstance;



protected:
    DynamicArray<Field> fields;
};