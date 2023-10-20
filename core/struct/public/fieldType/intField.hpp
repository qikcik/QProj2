#pragma once
#include "fieldType.hpp"

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
        int asInt = (int)*std::get<json::Value>(in_json).get<float>();
        *static_cast<int*>(in_addr) = asInt;
    }
};
