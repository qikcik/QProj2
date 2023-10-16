#pragma once
#include "memory"
#include "dynamicArray.tpp"
#include "ownerPtr.hpp"

#include <functional>
#include "field.hpp"

class QIns {};
class QStruct : public QIns {};

class QInsDef
{
public:
    QInsDef(
            std::string in_name,
            size_t in_size,
            const std::function<void(QIns* in_addr)>& in_constructInstance,
            const std::function<void(QIns* in_addr)>& in_destructInstance,
            DynamicArray<Field>&& in_fields
        ):
            name(std::move(in_name)),
            memorySize(in_size),
            constructInstance(in_constructInstance),
            destructInstance(in_destructInstance),
            fields(std::move(in_fields))
        {}

    virtual ~QInsDef() = default;

    const DynamicArray<Field>& getFields() const;
    Field* getField(const std::string& in_name) const;

    const std::string name;
    const size_t memorySize;

    const std::function<void(QIns* in_addr)> constructInstance;
    const std::function<void(QIns* in_addr)> destructInstance;



protected:
    DynamicArray<Field> fields;
};