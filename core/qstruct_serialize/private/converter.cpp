#include "converter.hpp"
#include "dynamicArray.tpp"


json::Object Converter::qstructToJson(QObj* in_addr, WeakPtr<QClass> in_class)
{
    QStructField field(in_class);
    return std::get<json::Object>(field.toJson(in_addr));
}


void Converter::jsonToQStruct(const json::Object& json, WeakPtr<QClass> in_class, QObj* in_addr)
{
    in_class.getPtr()->destructInstance(in_addr);
    QStructField field(in_class);
    field.fromJson(in_addr,json);
}