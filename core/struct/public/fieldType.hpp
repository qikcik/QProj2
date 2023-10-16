#pragma once
#include <memory>
#include "weakPtr.hpp"
#include "ownerPtr.hpp"
#include "object.hpp"

class FieldType
{
public:
    virtual ~FieldType() = default;

    virtual size_t getMemorySize() const = 0;
    virtual json::innerType toJson(void* in_addr) const = 0;
    virtual void fromJson(void* in_addr,const json::innerType& in_json) const = 0;
};


class FloatField : public FieldType
{
public:
    ~FloatField() override = default;

    size_t getMemorySize() const override {
        return sizeof(float);
    };

    json::innerType toJson(void* in_addr) const  override {
        auto& value = *reinterpret_cast<float*>(in_addr);
        return json::Value(value);
    }

    void fromJson(void* in_addr,const json::innerType& in_json) const override {
        auto asFloat = std::get<json::Value>(in_json).get<float>();
        *static_cast<float*>(in_addr) = *asFloat;
    }
};

class IntField : public FieldType
{
public:
    ~IntField() override = default;

    size_t getMemorySize() const override {
        return sizeof(int);
    };

    json::innerType toJson(void* in_addr) const  override {
        auto& value = *reinterpret_cast<int*>(in_addr);
        return json::Value((float)value);
    }

    void fromJson(void* in_addr,const json::innerType& in_json) const override {
        auto asInt = std::get<json::Value>(in_json).get<float>();
        *static_cast<int*>(in_addr) = *(int*)asInt;
    }
};

class StdStringField : public FieldType
{
public:
    ~StdStringField() override = default;

    size_t getMemorySize() const override {
        return sizeof(std::string);
    };

    json::innerType toJson(void* in_addr) const  override {
        auto& value = *reinterpret_cast<std::string*>(in_addr);
        return json::Value(value);
    }
    void fromJson(void* in_addr,const json::innerType& in_json) const override {
        auto asString = std::get<json::Value>(in_json).get<std::string>();
        new (in_addr) std::string(*asString);
    }
};

#include "dynamicArray.hpp"
class DynamicArrayField : public FieldType
{
public:
    explicit DynamicArrayField(const OwnerPtr<FieldType>&& in_type) : valueType(std::move(in_type)) {}
    ~DynamicArrayField() override = default;

    const OwnerPtr<FieldType> valueType;

    size_t getMemorySize() const override {
        return sizeof(DynamicArray<uint8_t>);
    };

    json::innerType toJson(void* in_addr) const  override;
    void fromJson(void* in_addr,const json::innerType& in_json) const override;
};

class QClass;
class QStructField : public FieldType
{
public:
    explicit QStructField(const WeakPtr<QClass>& in_type) : type(in_type) {}
    ~QStructField() override = default;

    const WeakPtr<QClass> type;
    size_t getMemorySize() const override;

    json::innerType toJson(void* in_addr) const  override;
    void fromJson(void* in_addr,const json::innerType& in_json) const override;
};

template<typename T>
OwnerPtr<FieldType> getFieldType();

template<std::derived_from<class QObj> T>
OwnerPtr<FieldType> getFieldType() {
    return OwnerPtr<QStructField>::createInstance( T::staticStruct );
}

template<typename T>
concept TDynamicArrayConcept = requires(T a) {
    requires std::same_as<T, DynamicArray<typename T::element_type>>;
};

template<TDynamicArrayConcept T>
OwnerPtr<FieldType> getFieldType() {
    using  element_type = typename T::element_type;
    return OwnerPtr<DynamicArrayField>::createInstance( std::move(getFieldType<element_type>()) );
}

