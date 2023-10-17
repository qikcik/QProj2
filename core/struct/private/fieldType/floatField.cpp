#include "fieldType/floatField.hpp"
#include "fieldType.hpp"
#include "fieldType/ownerObjPtr.hpp"


template<> OwnerPtr<FieldType> getFieldType<float>() { return OwnerPtr<FloatField>::CreateWithInstance(); };
