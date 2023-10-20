#include "fieldType/floatField.hpp"
#include "fieldType.hpp"
#include "fieldType/ownerObjPtr.hpp"
#include "fieldType/weakObjPtr.hpp"
#include "fieldType/observableField.hpp"


template<> OwnerPtr<FieldType> getFieldType<float>() { return OwnerPtr<FloatField>::CreateWithInstance(); };