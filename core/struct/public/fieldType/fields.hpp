#pragma once
#include "fieldType/dynamicArrayField.hpp"
#include "fieldType/floatField.hpp"
#include "fieldType/intField.hpp"
#include "fieldType/qStructField.hpp"
#include "fieldType/stdStringField.hpp"
#include "fieldType/stdStringField.hpp"


template<TDynamicArrayConcept T>
OwnerPtr<FieldType> getFieldType() {
    using  element_type = typename T::element_type;
    return OwnerPtr<DynamicArrayField>::createInstance( std::move(getFieldType<element_type>()) );
}

template<std::derived_from<class QStruct> T>
OwnerPtr<FieldType> getFieldType() {
    return OwnerPtr<QStructField>::createInstance( T::staticStructDef );
}
