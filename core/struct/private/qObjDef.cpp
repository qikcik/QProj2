#include "qObjDef.hpp"
#include "structMacros.hpp"
#include "fieldType/fields.hpp"

const OwnerPtr<QObjDef> QObj::staticDef = std::move(OwnerPtr<QObjDef>::CreateWithInstanceWithId(
        "core.QObjDef",
        "QObjDef",
        sizeof(QObj),
        WeakPtr<QObjDef>(),
        [](QIns* addr){ new (addr) QObj(QObj::staticDef); },
        [](QIns* addr){ reinterpret_cast<QObj*>(addr)->~QObj(); },
        DynamicArray<Field>{
                GEN_INS_DEF_FIELD_ENTRY(QObj,selfPtr)
        }
));

DynamicArray<Field*> QObjDef::getAllFields() const
{
    DynamicArray<Field*> result;
    if(baseObjDef.getPtr())
        result = std::move(baseObjDef.getPtr()->getAllFields());

    result.reserve(result.get_length()+fields.get_length());
    for(auto& it : fields)
        result.push_back(&it);
    return result;
}

Field* QObjDef::getField(const std::string& in_name) const
{
    for(auto& fieldIt : fields)
        if(fieldIt.name == in_name) return &fieldIt;

    if(baseObjDef.getPtr())
        return baseObjDef.getPtr()->getField(in_name);

    return nullptr;
}
