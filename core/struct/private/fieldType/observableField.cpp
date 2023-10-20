#include "fieldType/observableField.hpp"

json::innerType ObservableField::toJson(void* in_addr) const
{
    return valueType.getPtr()->toJson(in_addr);
}

void ObservableField::fromJson(void* in_addr, const json::innerType& in_json) const
{
    return valueType.getPtr()->fromJson(in_addr,in_json);
}
