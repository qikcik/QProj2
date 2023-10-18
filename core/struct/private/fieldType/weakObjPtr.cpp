#include "fieldType/weakObjPtr.hpp"
#include "qObjDef.hpp"

//TODO: add checking!
json::innerType WeakObjPtrField::toJson(void* in_addr) const
{
    auto asWeakPtr = reinterpret_cast<WeakPtr<QObj>*>(in_addr);
    return json::Value(asWeakPtr->getId());
}

void WeakObjPtrField::fromJson(void* in_addr, const json::innerType& in_json) const
{
    auto objIdStr = std::get<json::Value>(in_json).get<std::string>();


    auto asWeakPtr = reinterpret_cast<WeakPtr<QObj>*>(in_addr);
    asWeakPtr->~WeakPtr<QObj>();
    new (asWeakPtr) WeakPtr<QObj>(*objIdStr);
}
