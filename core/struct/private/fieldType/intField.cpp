#include "fieldType/intField.hpp"
#include "fieldType.hpp"

template<> OwnerPtr<FieldType> getFieldType<int>() { return OwnerPtr<IntField>::CreateWithInstance(); };
