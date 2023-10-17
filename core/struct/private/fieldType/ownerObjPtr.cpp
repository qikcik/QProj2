#include "fieldType/ownerObjPtr.hpp"
#include "qObjDef.hpp"
#include "fieldType/qStructField.hpp"

json::innerType OwnerObjPtrField::toJson(void* in_addr) const
{
    json::Object result {};

    auto asOwnerPtr = reinterpret_cast<OwnerPtr<QObj>*>(in_addr);
    auto asQObj = reinterpret_cast<QObj*>(asOwnerPtr->getPtr());
    result.set("objId",json::Value(asOwnerPtr->getId()));

    if(not asQObj)
    {
        result.set("objDef",json::Value(""));
        result.set("objId",json::Value(""));
        result.set("objIns",json::Value(""));
        return result;
    }


    result.set("objDef",json::Value(asQObj->objDef.getId()));

    QStructField field(asQObj->objDef);
    result.set("objIns",field.toJson(asQObj));

    return result;
}

void OwnerObjPtrField::fromJson(void* in_addr, const json::innerType& in_json) const
{
    auto json = std::get<json::Object>(in_json);

    auto& objDefStr = *json.get<json::Value>("objDef")->get<std::string>();
    auto& objIdStr = *json.get<json::Value>("objId")->get<std::string>();
    WeakPtr<QObjDef> objDef(objDefStr);

    DEBUG_ENSURE(objDef.getPtr())

    auto asOwnerPtr = reinterpret_cast<OwnerPtr<QObj>*>(in_addr);
    asOwnerPtr->~OwnerPtr<QObj>();
    new (asOwnerPtr) OwnerPtr<QObj>(objIdStr);
    asOwnerPtr->block->allocateInstance(objDef.getPtr()->memorySize);
    objDef.getPtr()->constructInstance(asOwnerPtr->getPtr());

    QStructField field(objDef);
    field.fromJson(asOwnerPtr->getPtr(), *json.get<json::Object>("objIns"));


}
