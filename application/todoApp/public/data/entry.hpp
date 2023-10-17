#pragma once
#include "dynamicArray.tpp"
#include "qInsDef.hpp"
#include "fieldType.hpp"
#include "converter.hpp"
#include "structMacros.hpp"
#include "parser.hpp"

GEN_QSTRUCT(Entry)
{
GEN_QSTRUCT_BODY()
public:
    std::string title {};
    std::string status {};

};

GEN_QSTRUCT_STATIC_DEF(Entry, {
    GEN_INS_DEF_FIELD_ENTRY(Entry, title),
    GEN_INS_DEF_FIELD_ENTRY(Entry, status)
})