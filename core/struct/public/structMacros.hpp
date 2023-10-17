#pragma once

#define GEN_QSTRUCT(NAME) class NAME : public QStruct
#define GEN_QSTRUCT_BODY() public: static const OwnerPtr<QInsDef> staticDef; private:

#define GEN_QSTRUCT_STATIC_DEF(type,entries...) \
const OwnerPtr<QInsDef> type::staticDef = std::move(OwnerPtr<QInsDef>::CreateWithInstanceWithId( \
        TARGET_NAME ".QStructDef." #type,                                        \
        #type, \
        sizeof(type), \
        [](QIns* addr){ new (addr) type(); },                                 \
        [](QIns* addr){ reinterpret_cast<type*>(addr)->~type(); },\
        DynamicArray<Field> entries \
));

#define GEN_QOBJ(NAME) class NAME : public QObj
#define GEN_QOBJ_BODY(NAME) public: static const OwnerPtr<QObjDef> staticDef; private:
#define GEN_QOBJ_DEF_CONSTRUCTOR_AND_DESTRUCTOR(NAME) \
public:                                                 \
explicit NAME(const WeakPtr<QObjDef>& in_derivedObjDef) : QObj(in_derivedObjDef) {}; \
~NAME() override = default;                      \
private:

#define GEN_QOBJ_STATIC_DEF(type,entries...) \
const OwnerPtr<QObjDef> type::staticDef = std::move(OwnerPtr<QObjDef>::CreateWithInstanceWithId( \
        TARGET_NAME ".QObjDef." #type,                                      \
        #type, \
        sizeof(type), \
        [](QIns* addr){ new (addr) type(type::staticDef); },                                 \
        [](QIns* addr){ reinterpret_cast<type*>(addr)->~type(); },\
        DynamicArray<Field> entries \
));

#define GEN_INS_DEF_FIELD_ENTRY(type,name) Field{#name, offsetof(type, name), std::move(getFieldType<typeof(type::name)>())}
