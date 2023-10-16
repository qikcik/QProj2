#include "fieldType.hpp"
#include "qClass.hpp"

size_t QStructField::getMemorySize() const {
    DEBUG_ENSURE(type.getPtr());
    return type.getPtr()->memorySize;
}

json::innerType QStructField::toJson(void* in_addr) const
{
    json::Object result {};


    for(const auto& fieldIt : type.getPtr()->getFields())
    {
        auto field_addr = fieldIt.getValuePtr<void>((QObj*)in_addr);
        result.set(fieldIt.name,fieldIt.type.getPtr()->toJson(field_addr));
    }

    return result;
}

void QStructField::fromJson(void* in_addr, const json::innerType& in_json) const
{
    type.getPtr()->constructInstance(reinterpret_cast<QObj*>(in_addr));
    auto json = std::get<json::Object>(in_json);
    for( auto& entryIt : json.entries )
    {
        auto field = type.getPtr()->getField(entryIt.first);
        auto entryIt_addr = field->getValuePtr<void>(reinterpret_cast<QObj*>(in_addr));
        if(!field) continue; //TODO: PRINT WARNING
        field->type.getPtr()->fromJson(entryIt_addr,entryIt.second);
    }
};

#include "dynamicArrayUnsafeHelper.hpp"
json::innerType DynamicArrayField::toJson(void* in_addr) const
{

    DynamicArrayUnsafeHelper helper(in_addr,valueType.getPtr()->getMemorySize());

    json::Array arr {};
    for(size_t el_idx=0; el_idx != helper.get_length(); el_idx++)
    {
        void* el_addr = helper.get_elementPtr(el_idx);
        arr.values.emplace_back( valueType.getPtr()->toJson(el_addr) );
    }
    return arr;
}

void DynamicArrayField::fromJson(void* in_addr, const json::innerType& in_json) const
{
    auto jsonArray = std::get<json::Array>(in_json);
    DynamicArrayUnsafeHelper helper(in_addr,valueType.getPtr()->getMemorySize());
    helper.reserve_withoutFreeingOldMemory(jsonArray.values.size());
    int arrayIdx=0;
    for( auto& jsonIt : jsonArray.values)
    {
        auto* el_addr = helper.get_elementPtr(arrayIdx);
        valueType.getPtr()->fromJson(el_addr,jsonIt);
        arrayIdx++;
    }
    helper.set_length(jsonArray.values.size()); // TODO: improve in case of invalid entry!
}

template<> OwnerPtr<FieldType> getFieldType<float>() { return OwnerPtr<FloatField>::createInstance(); };
template<> OwnerPtr<FieldType> getFieldType<int>() { return OwnerPtr<IntField>::createInstance(); };

#include <string>
template<> OwnerPtr<FieldType> getFieldType<std::string>() { return OwnerPtr<StdStringField>::createInstance(); };
