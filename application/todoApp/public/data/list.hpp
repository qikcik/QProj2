#pragma once
#include "dynamicArray.tpp"
#include "qInsDef.hpp"
#include "fieldType.hpp"
#include "converter.hpp"
#include "structMacros.hpp"
#include "parser.hpp"
#include "entry.hpp"
#include "fieldType/fields.hpp"


GEN_QSTRUCT(List)
{
GEN_QSTRUCT_BODY()
public:
    std::string title {};
    DynamicArray<Entry> entries {};

};

GEN_QSTRUCT_STATIC_DEF(List, {
    GEN_INS_DEF_FIELD_ENTRY(List, title),
    GEN_INS_DEF_FIELD_ENTRY(List, entries)
})