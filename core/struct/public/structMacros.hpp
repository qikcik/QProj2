#pragma once

#define GEN_QOBJ(NAME) class NAME : public QObj
#define GEN_QOBJ_BODY() public: static const OwnerPtr<QClass> staticStruct; private:

#define GEN_QSTRUCT_TYPE(type,entries...) \
const OwnerPtr<QClass> type::staticStruct = std::move(OwnerPtr<QClass>::createInstance( \
        #type, \
        sizeof(type), \
        [](QObj* addr){ new (addr) type(); },                                 \
        [](QObj* addr){ reinterpret_cast<type*>(addr)->~type(); },\
        DynamicArray<Field> entries \
));

#define GEN_QSTRUCT_FIELD_ENTRY(type,name) Field{#name, offsetof(type, name), std::move(getFieldType<typeof(type::name)>())}
