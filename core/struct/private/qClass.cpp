#include "qInsDef.hpp"

const DynamicArray<Field>& QInsDef::getFields() const
{
    return fields;
}

Field* QInsDef::getField(const std::string& in_name) const
{
    for(auto& fieldIt : fields)
        if(fieldIt.name == in_name) return &fieldIt;
    return nullptr;
}
