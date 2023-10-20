#include "qInsDef.hpp"


Field* QInsDef::getField(const std::string& in_name) const
{
    for(auto& fieldIt : fields)
        if(fieldIt.name == in_name) return &fieldIt;
    return nullptr;
}

DynamicArray<Field*> QInsDef::getAllFields() const
{
    DynamicArray<Field*> result;
    result.reserve(fields.get_capacity());
    for(auto& it : fields)
        result.push_back(&it);
    return result;
}
