#pragma once
#include "fieldType.hpp"

#include "dynamicArray.hpp"
#include "observable.hpp"

class ObservableField : public FieldType
{
public:
    explicit ObservableField(const OwnerPtr<FieldType>&& in_type) : valueType(std::move(in_type)) {}
    ~ObservableField() override = default;

    const OwnerPtr<FieldType> valueType;

    size_t getMemorySize() const override {
        return sizeof(std::function<void(void*)>)+valueType.getPtr()->getMemorySize();
    };

    json::innerType toJson(void* in_addr) const  override;
    void fromJson(void* in_addr,const json::innerType& in_json) const override;
};

template<typename T>
concept TObservableConcept = requires(T a) {
    requires std::same_as<T, Observable<typename T::element_type>>;
};


template<TObservableConcept T>
OwnerPtr<FieldType> getFieldType();