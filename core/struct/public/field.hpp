#pragma once
#include <string>
#include <utility>
#include "weakPtr.hpp"
#include "fieldType.hpp"

class QObj;
class Field
{
public:
    const std::string name {};
    const size_t offset {};
    const OwnerPtr<FieldType> type {};


    template<typename T>
    T* getValuePtr(QObj* objPtr) const
    {
        auto* bytePtr = reinterpret_cast<uint8_t*>(objPtr);
        auto memberPtr = reinterpret_cast<T*>(bytePtr + offset);
        return memberPtr;
    }
};