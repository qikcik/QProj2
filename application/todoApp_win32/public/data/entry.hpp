#pragma once
#include "dynamicArray.tpp"
#include "qClass.hpp"
#include "fieldType.hpp"
#include "converter.hpp"
#include "structMacros.hpp"
#include "parser.hpp"

GEN_QOBJ(Entry)
{
GEN_QOBJ_BODY()
public:
    std::string title {};
    std::string status {};

};

GEN_QSTRUCT_TYPE(Entry,{
    GEN_QSTRUCT_FIELD_ENTRY(Entry,title),
    GEN_QSTRUCT_FIELD_ENTRY(Entry,status)
})