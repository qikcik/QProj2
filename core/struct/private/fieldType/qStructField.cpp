#include "fieldType/qStructField.hpp"
#include "qInsDef.hpp"


size_t QStructField::getMemorySize() const {
    DEBUG_ENSURE(type.getPtr());
    return type.getPtr()->memorySize;
}

json::innerType QStructField::toJson(void* in_addr) const
{
    json::Object result {};

    for(const auto fieldIt : type.getPtr()->getAllFields())
    {
        auto field_addr = fieldIt->getValuePtr<void>((QIns*)in_addr);
        result.set(fieldIt->name,fieldIt->type.getPtr()->toJson(field_addr));
    }

    return result;
}

void QStructField::fromJson(void* in_addr, const json::innerType& in_json) const
{
    type.getPtr()->constructInstance(reinterpret_cast<QIns*>(in_addr));
    auto json = std::get<json::Object>(in_json);
    for( auto& entryIt : json.entries )
    {
        auto field = type.getPtr()->getField(entryIt.first);
        auto entryIt_addr = field->getValuePtr<void>(reinterpret_cast<QIns*>(in_addr));
        if(!field) continue; //TODO: PRINT WARNING
        field->type.getPtr()->fromJson(entryIt_addr,entryIt.second);
    }
};
