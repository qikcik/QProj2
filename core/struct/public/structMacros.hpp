#pragma once

#define GEN_QSTRUCT(NAME) class NAME : public QStruct
#define GEN_QSTRUCT_BODY() public: static const OwnerPtr<QInsDef> staticStructDef; private:

#define GEN_QSTRUCT_STATIC_DEF(type,entries...) \
const OwnerPtr<QInsDef> type::staticStructDef = std::move(OwnerPtr<QInsDef>::createInstance( \
        #type, \
        sizeof(type), \
        [](QIns* addr){ new (addr) type(); },                                 \
        [](QIns* addr){ reinterpret_cast<type*>(addr)->~type(); },\
        DynamicArray<Field> entries \
));

#define GEN_QSTRUCT_FIELD_ENTRY(type,name) Field{#name, offsetof(type, name), std::move(getFieldType<typeof(type::name)>())}
