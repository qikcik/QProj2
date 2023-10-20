#pragma once
#include "fieldType.hpp"

class QInsDef;
class QStructField : public FieldType
{
public:
    explicit QStructField(const WeakPtr<QInsDef>& in_type) : type(in_type) {}
    ~QStructField() override = default;

    const WeakPtr<QInsDef> type;
    size_t getMemorySize() const override;

    json::innerType toJson(void* in_addr) const  override;
    void fromJson(void* in_addr,const json::innerType& in_json) const override;
};


template<std::derived_from<class QStruct> T>
OwnerPtr<FieldType> getFieldType();
