#pragma once
#include "fieldType/dynamicArrayField.hpp"
#include "fieldType/floatField.hpp"
#include "fieldType/intField.hpp"
#include "fieldType/qStructField.hpp"
#include "fieldType/stdStringField.hpp"
#include "fieldType/stdStringField.hpp"

#include "fieldType/ownerObjPtr.hpp"
#include "fieldType/weakObjPtr.hpp"
#include "fieldType/observableField.hpp"

template<TDynamicArrayConcept T>
OwnerPtr<FieldType> getFieldType() {
    using  element_type = typename T::element_type;
    return OwnerPtr<DynamicArrayField>::CreateWithInstance( std::move(getFieldType<element_type>()) );
}

template<std::derived_from<class QStruct> T>
OwnerPtr<FieldType> getFieldType() {
    return OwnerPtr<QStructField>::CreateWithInstance( T::staticDef );
}

template<TOwnerPtr T>
OwnerPtr<FieldType> getFieldType() {
    return OwnerPtr<OwnerObjPtrField>::CreateWithInstance( T::element_type::staticDef );
}

template<TWeakPtr T>
OwnerPtr<FieldType> getFieldType() {
    return OwnerPtr<WeakObjPtrField>::CreateWithInstance( T::element_type::staticDef );
}

template<TObservableConcept T>
OwnerPtr<FieldType> getFieldType() {
    using  element_type = typename T::element_type;
    return OwnerPtr<ObservableField>::CreateWithInstance( std::move(getFieldType<element_type>()), offsetof(T,listeners) );
}