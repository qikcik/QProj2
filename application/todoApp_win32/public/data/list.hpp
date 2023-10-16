#pragma once
#include "dynamicArray.tpp"
#include "qClass.hpp"
#include "fieldType.hpp"
#include "converter.hpp"
#include "structMacros.hpp"
#include "parser.hpp"
#include "entry.hpp"

GEN_QOBJ(List)
{
GEN_QOBJ_BODY()
public:
    std::string title {};
    DynamicArray<Entry> entries {};

};

GEN_QSTRUCT_TYPE(List,{
    GEN_QSTRUCT_FIELD_ENTRY(List,title),
    GEN_QSTRUCT_FIELD_ENTRY(List,entries)
})