#pragma once
#include "fieldType.hpp"

#include "dynamicArray.hpp"
class QObjDef;
class WeakObjPtrField : public FieldType
{
public:
    explicit WeakObjPtrField(const WeakPtr<QObjDef>& in_type) : type(in_type) {}
    ~WeakObjPtrField() override = default;

    const WeakPtr<QObjDef> type;

    size_t getMemorySize() const override {
        return sizeof(DynamicArray<uint8_t>);
    };

    json::innerType toJson(void* in_addr) const  override;
    void fromJson(void* in_addr,const json::innerType& in_json) const override;
};

template<typename T>
concept TWeakPtr = requires(T a) {
    requires std::same_as<T, WeakPtr<typename T::element_type>>;
};

template<TWeakPtr T>
OwnerPtr<FieldType> getFieldType();