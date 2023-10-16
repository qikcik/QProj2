#pragma once
#include "object.hpp"
#include "qClass.hpp"
#include "parser.hpp"
#include "dynamicInfo.hpp"
#include <concepts>

class Converter
{
public:
    explicit Converter(const DynamicInfo& in_dynamicInfo = {}) : dynamicInfo(in_dynamicInfo) {};

    json::Object qstructToJson(QObj* in_addr, WeakPtr<QClass> in_class);
    void jsonToQStruct(const json::Object& json, WeakPtr<QClass> in_class, QObj* in_addr);


protected:

    //void jsonArrayToQstruct(json::Array& arrayJson,const FieldType::DynamicArray& dynamicArray, void* addr);
    const DynamicInfo& dynamicInfo;
};

/*
template<std::derived_from<QObj> TObj>
json::Object Converter::qstructToJson(TObj& obj)
{
    QStructType type = obj.staticType;
    return qstructToJson(&obj,type);
}


template<std::derived_from<QObj> TObj>
void Converter::jsonToQStruct(TObj& obj,const std::string& source)
{
    QStructType type = TStruct::staticType;
    type.deInitInstance(&obj);
    type.initInstance(&obj);


    json::Parser parser {};
    auto ParserRes = parser.parse(source);
    if (auto* json = std::get_if<json::Object>(&ParserRes); json )
    {
        jsonToQStruct_inner(*json,type,&obj);
    }
}
*/