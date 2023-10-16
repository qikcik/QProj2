#include "qClass.hpp"

const DynamicArray<Field>& QClass::getFields() const
{
    return fields;
}

Field* QClass::getField(const std::string& in_name) const
{
    for(auto& fieldIt : fields)
        if(fieldIt.name == in_name) return &fieldIt;
    return nullptr;
}
