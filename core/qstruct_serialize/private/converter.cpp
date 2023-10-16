#include "converter.hpp"
#include "dynamicArray.tpp"
#include "fieldType/fields.hpp"


json::Object Converter::qstructToJson(QIns* in_addr, WeakPtr<QInsDef> in_class)
{
    QStructField field(in_class);
    return std::get<json::Object>(field.toJson(in_addr));
}


void Converter::jsonToQStruct(const json::Object& json, WeakPtr<QInsDef> in_class, QIns* in_addr)
{
    in_class.getPtr()->destructInstance(in_addr);
    QStructField field(in_class);
    field.fromJson(in_addr,json);
}