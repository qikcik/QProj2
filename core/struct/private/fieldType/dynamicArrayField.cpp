#include "fieldType/dynamicArrayField.hpp"
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