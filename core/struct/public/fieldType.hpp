#pragma once
#include <memory>
#include "weakPtr.hpp"
#include "ownerPtr.hpp"
#include "object.hpp"

class FieldType
{
public:
    virtual ~FieldType() = default;

    virtual size_t getMemorySize() const = 0;
    virtual json::innerType toJson(void* in_addr) const = 0;
    virtual void fromJson(void* in_addr,const json::innerType& in_json) const = 0;
};

template<typename T>
OwnerPtr<FieldType> getFieldType();

