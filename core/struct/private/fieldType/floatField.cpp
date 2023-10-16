#include "fieldType/floatField.hpp"
#include "fieldType.hpp"

template<> OwnerPtr<FieldType> getFieldType<float>() { return OwnerPtr<FloatField>::createInstance(); };