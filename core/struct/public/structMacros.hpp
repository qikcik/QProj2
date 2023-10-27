#pragma once

#define GEN_QSTRUCT(NAME) class NAME : public QStruct
#define GEN_QSTRUCT_BODY(NAME) public: static const OwnerPtr<QInsDef> staticDef; private:

#define GEN_QSTRUCT_STATIC_DEF(type,entries...) \
const OwnerPtr<QInsDef> type::staticDef = std::move(OwnerPtr<QInsDef>::CreateWithInstanceWithId( \
        TARGET_NAME ".QStructDef." #type,                                        \
        #type, \
        sizeof(type), \
        [](QIns* addr){ new (addr) type(); },                                 \
        [](QIns* addr){ reinterpret_cast<type*>(addr)->~type(); },\
        DynamicArray<Field> entries \
));

#define GEN_QOBJ(NAME,BASE) class NAME : public BASE

#define GEN_QOBJ_BODY(NAME,BASE) public: static const OwnerPtr<QObjDef> staticDef; private:


#define GEN_QOBJ_DEF_CONSTRUCTOR_AND_DESTRUCTOR(NAME,BASE) \
public:                                                 \
explicit NAME(const WeakPtr<QObjDef>& in_derivedObjDef) : BASE(in_derivedObjDef) {};  \
~NAME() override = default;                      \
private:


#define BEGIN_GEN_QOBJ_STATIC_DEF(NAME,BASE) \
const OwnerPtr<QObjDef> NAME::staticDef = std::move(OwnerPtr<QObjDef>::CreateWithInstanceWithId( \
        TARGET_NAME ".QObjDef." #NAME,                                      \
        #NAME, \
        sizeof(NAME),                             \
        BASE::staticDef.getWeak(),                                          \
        [](QIns* addr){ new (addr) NAME(NAME::staticDef); },                                 \
        [](QIns* addr){ reinterpret_cast<NAME*>(addr)->~NAME(); },

#define END_GEN_QOBJ_STATIC_DEF() ));


#define GEN_INS_DEF_FIELD_ENTRY(type,name) Field{#name, offsetof(type, name), std::move(getFieldType<typeof(type::name)>())}
