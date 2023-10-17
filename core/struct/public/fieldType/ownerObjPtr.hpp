#pragma once
#include "fieldType.hpp"

#include "dynamicArray.hpp"
class QObjDef;
class OwnerObjPtrField : public FieldType
{
public:
    explicit OwnerObjPtrField(const WeakPtr<QObjDef>& in_type) : type(in_type) {}
    ~OwnerObjPtrField() override = default;

    const WeakPtr<QObjDef> type;

    size_t getMemorySize() const override {
        return sizeof(DynamicArray<uint8_t>);
    };

    json::innerType toJson(void* in_addr) const  override;
    void fromJson(void* in_addr,const json::innerType& in_json) const override;
};

template<typename T>
concept TOwnerPtr = requires(T a) {
    requires std::same_as<T, OwnerPtr<typename T::element_type>>;
};

template<TOwnerPtr T>
OwnerPtr<FieldType> getFieldType();